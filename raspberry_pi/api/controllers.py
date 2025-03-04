import RPi.GPIO as GPIO
from time import sleep


GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)


####    Variables Globales
# Establecer pines
pin_effect_button = 25
pin_speed_up_button = 24
pin_speed_down_button = 23

press_debounce_t = 0.01   # 10 ms

# Velocidad en ms (tiempo de debounce)
current_level = 5
MAX_SPEED_LEVEL = 9
MIN_SPEED_LEVEL = 1
IS_SPEED_UP = False
change_speed_debounce_t = 0.1  # 100 ms 


####    CONFIGURACIONES
GPIO.setup(pin_effect_button, GPIO.OUT)
GPIO.setup(pin_speed_up_button, GPIO.OUT)
GPIO.setup(pin_speed_down_button, GPIO.OUT)


#### FUNCIONES
## AUXILIAR
# Enviar pulsos
def send_pulse(pin):
    GPIO.output(pin, GPIO.HIGH)
    sleep(press_debounce_t)
    GPIO.output(pin, GPIO.LOW)
    # print("Pulse sent!")


# Calcular si el nivel es mayor
def check_speed_up(speed_level: int):
    global IS_SPEED_UP
    if speed_level > current_level:
        IS_SPEED_UP = True
    else:
        IS_SPEED_UP = False


# Calcular pasos de niveles
def calculate_steps(speed_level: int) -> int:
    if IS_SPEED_UP:
        steps = speed_level - current_level
    else:
        steps = current_level - speed_level
    return steps



## RESPUESTA DEL ROUTING
# Obtener velocidad actual
def get_speed_value() -> int:
    return current_level


# Función para cambiar al siguiente efecto
def set_next_effect():
    send_pulse(pin_effect_button)


# Función de cambio de velocidad
def set_speed(speed_level: int):
    global current_level

    check_speed_up(speed_level)
    
    print("steps: ", calculate_steps(speed_level))
    
    for _ in range(calculate_steps(speed_level)):
        if IS_SPEED_UP:
            send_pulse(pin_speed_up_button)
        else:
            send_pulse(pin_speed_down_button)
        sleep(change_speed_debounce_t)     # COORDINAR CON DEBOUNCE DE ARDUINO

    current_level = speed_level
    #print(current_level)
    #return current_level



if __name__ == '__main__':
    send_pulse(pin_speed_up_button)
    print("Cleanup GPIO..")
    GPIO.cleanup()
