import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# Set pin numbers
pinNumber = 25
GPIO.setup(pinNumber, GPIO.OUT)

def pulse():
	GPIO.output(pinNumber, GPIO.HIGH)
	sleep(0.1)
	GPIO.output(pinNumber, GPIO.LOW)
	print("Pulse sent!")

for i in range(4):
	pulse()
	sleep(2)

print("Cleanup GPIO..")
GPIO.cleanup()