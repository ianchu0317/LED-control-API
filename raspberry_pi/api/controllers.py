import RPi.GPIO as GPIO
from time import sleep


GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)


####    Variables Globales
# Establecer pines
pin_effect_button = 25
pin_speed_up_button = 24
pin_speed_down_button = 23

debounce_t = 0.001   # 0.02s = 20 ms


####    CONFIGURACIONES
GPIO.setup(pin_effect_button, GPIO.OUT)
GPIO.setup(pin_speed_up_button, GPIO.OUT)
GPIO.setup(pin_speed_down_button, GPIO.OUT)


#### FUNCIONES
def send_pulse(pin):
    GPIO.output(pin, GPIO.HIGH)
    sleep(debounce_t)
    GPIO.output(pin, GPIO.LOW)
    print("Pulse sent!")


def next_effect():
    pass

def set_speed():
    return


if __name__ == '__main__':
    send_pulse(pin_speed_up_button)
    print("Cleanup GPIO..")
    GPIO.cleanup()
