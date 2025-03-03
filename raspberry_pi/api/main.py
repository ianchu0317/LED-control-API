from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from schemas import LedSpeedLevel, GetNextEffect
from controllers import set_next_effect, set_speed


api = FastAPI()

# Permitir CORS desde el origen http://127.0.0.1 (frontend)
api.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # O usa ["*"] para permitir todos los orígenes
    allow_credentials=True,
    allow_methods=["*"],  # Permitir todos los métodos HTTP
    allow_headers=["*"],  # Permitir todos los headers
)


@api.post("/api/led/change_effect")
def change_effect(next_effect: GetNextEffect):
    print("CHANGING EFFECT")
    set_next_effect()
    return {"message": "success"}


@api.post("/api/led/change_speed")
def change_speed(speed: LedSpeedLevel):
    print("GOT INPUT SPEED: ", speed.level)
    current_level = set_speed(speed.level)
    # Devolver velocidad actual JSON
    return {'velocidad': current_level}

