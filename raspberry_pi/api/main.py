from fastapi import FastAPI
from schemas import LedSpeed
from controllers import next_effect

api = FastAPI()


# Request POST *SIN* BODY
@api.post("/api/led/change_effect")
def change_effect():
    return next_effect()


@api.post("/api/led/change_speed")
def change_speed(speed: LedSpeed):
    pass

