from fastapi import FastAPI
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware


api = FastAPI()

class LedSpeedLevel(BaseModel):
    level: int

class EffectNext(BaseModel):
    effect: str

# Permitir CORS desde el origen http://127.0.0.1 (frontend)
api.add_middleware(
    CORSMiddleware,
    allow_origins=["http://127.0.0.1"],  # O usa ["*"] para permitir todos los orígenes
    allow_credentials=True,
    allow_methods=["*"],  # Permitir todos los métodos HTTP
    allow_headers=["*"],  # Permitir todos los headers
)


# Request POST *SIN* BODY
@api.post("/api/led/change_effect")
def change_effect(next_effect: EffectNext):
    print("CHANGING EFFECT")
    return {"message": "success"}


@api.post("/api/led/change_speed")
def change_speed(speed: LedSpeedLevel):
    print("GOT INPUT SPEED: ", speed.level)
    return {'velocidad': speed.level}

