from pydantic import BaseModel


class LedSpeedLevel(BaseModel):
    level: int


class GetNextEffect(BaseModel):
    effect: str
