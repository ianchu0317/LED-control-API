from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from schemas import LedSpeedLevel, GetNextEffect
from controllers import get_speed_value, set_next_effect, set_speed


api = FastAPI()

# Permitir CORS desde el origen http://127.0.0.1 (frontend)
api.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # O usa ["*"] para permitir todos los orígenes
    allow_credentials=True,
    allow_methods=["*"],  # Permitir todos los métodos HTTP
    allow_headers=["*"],  # Permitir todos los headers
)


@api.get("/api/leds/get-speed")
def get_speed():
    current_level = get_speed_value()
    return {"level": current_level}


@api.post("/api/leds/change-effect")
def change_effect(next_effect: GetNextEffect):
    set_next_effect()
    return {"message": "success"}


@api.post("/api/leds/change-speed")
def change_speed(speed: LedSpeedLevel):
    set_speed(speed.level)
    current_level = get_speed_value()
    # Devolver velocidad actual JSON
    return {"level": current_level}

