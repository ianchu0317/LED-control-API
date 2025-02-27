from pydantic import BaseModel

class LedSpeedLevel(BaseModel):
    level: int
