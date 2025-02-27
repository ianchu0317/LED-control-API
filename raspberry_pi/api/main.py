from fastapi import FastAPI
from schemas import LedSpeedLevel
from controllers import next_effect, set_speed

api = FastAPI()


# Request POST *SIN* BODY
@api.post("/api/led/change_effect")
def change_effect():
    return next_effect()


@api.post("/api/led/change_speed")
def change_speed(speed: LedSpeedLevel):
    return set_speed(speed.level)

