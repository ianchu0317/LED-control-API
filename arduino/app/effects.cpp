#include "effects.h"

/* *** DEFINIR PINES *** */
#define NUM_LEDS 6
const byte led_1 = 11;
const byte led_2 = 10;
const byte led_3 = 9;
const byte led_4 = 6;
const byte led_5 = 5;
const byte led_6 = 3;
const byte leds[NUM_LEDS] = { led_1, led_2, led_3, led_4, led_5, led_6 };



/* *** VARIABLES ****/
//  variables para manejar efectos
// variables modificables
int effects_counter = 0;
int effect_vel = 50;  // ms (debounce time)
// variables del programa
int total_effects = 3;
unsigned long last_activation_time = 0;  // para debounce tracking
bool is_turn_off = false;                // si esta apagado todo

//  variables para intercalateLED
int intercalate_i = 0;  // contador para funcion intercalateLed
int intercalate_step = 1;
int intercalate_vel = 30;  // ms (velocidad debounce)  MODIFICABLE
int previous_intercalate_i = 0;

//  variables para fade
int fade_step = 15;  // cambio de intensidad
int fade_count = 0;

// variables para intercalateIn y intercalateOut
int activation_counter = 0;  // contador para leds activados
bool reverse = false;
byte activation_state = HIGH;



/* *** CONFIGURACIONES *** */
// configurar salidas de led
void setupLeds() {
  byte led;
  for (int i = 0; i <= 5; i++) {
    led = leds[i];
    pinMode(led, OUTPUT);
  }
}


// cambiar efecto actual
void switchEffect() {
  switch (effects_counter) {
    case 0:
      turnOff();
      break;
    case 1:
      intercalateLed();
      break;
    case 2:
      fadeLeds();
      break;
    case 3:
      intercalateInOut();
      break;
  }
}



/* *** FUNCIONES *** */
// apagar todos los LEDs si no están apagados
void turnOff() {
  if (!is_turn_off) {
    setLedsIntensity(0);
    is_turn_off = true;
  }
}


// configurar todos los LED dada una intensidad
void setLedsIntensity(int intensity) {
  byte led;
  for (int i = 0; i <= 5; i++) {
    led = leds[i];
    analogWrite(led, intensity);
  }
}



/* *** EFECTOS *** */
// regular la intensidad progresivamente con pwm
void fadeLeds() {
  if (millis() - last_activation_time > effect_vel) {
    last_activation_time = millis();

    setLedsIntensity(fade_count);
    fade_count = fade_count + fade_step;

    if (fade_count == 255 || fade_count == 0) {
      fade_step = -fade_step;
    }
  }
}


// alternar el encendido y apagado de los LEDs
void intercalateLed() {
  if (millis() - last_activation_time > intercalate_vel) {
    last_activation_time = millis();

    byte led = leds[intercalate_i];

    // apagar todos los leds antes de encender actual
    setLedsIntensity(0);
    // encender LED actual
    digitalWrite(led, HIGH);

    intercalate_i = intercalate_i + intercalate_step;

    if (intercalate_i == NUM_LEDS - 1 || intercalate_i == 0) {
      intercalate_step = -intercalate_step;
    }
  }
}


/*
  Alterna los encendidos de los LEDs
  A diferencia del anterior también los apaga
  Los LEDs prendidos se mantienen prendidos por un momento
*/
void intercalateInOut() {
  if (!reverse) {
    turnOnLedsSequentially();
  } else {
    turnOffLedsSequentially();
  }
}


// Enciende y apaga de led 1 a 6
void turnOnLedsSequentially() {
  if (millis() - last_activation_time > effect_vel) {
    last_activation_time = millis();

    // cambiar estado de luces progresivamente
    int currentLed = leds[activation_counter];
    digitalWrite(currentLed, activation_state);

    // seguir index de contador
    if (activation_counter == 5) {
      if (activation_state == LOW) {
        // hard reset
        reverse = true;
        activation_state = HIGH;
      } else {
        // resetear por primera vez
        activation_counter = 0;
        activation_state = LOW;
      }
    } else {
      activation_counter = activation_counter + 1;
    }
  }
}


// reversa de turnOnLedsSequentially
void turnOffLedsSequentially() {
  if (millis() - last_activation_time > effect_vel) {
    last_activation_time = millis();  // actualizar tiempo

    // cambiar estado de luces progresivamente
    int currentLed = leds[activation_counter];
    digitalWrite(currentLed, activation_state);

    // seguir index de contador
    if (activation_counter == 0) {
      if (activation_state == LOW) {
        reverse = false;
        activation_state = HIGH;
      } else {
        activation_counter = 5;
        activation_state = LOW;
      }
    } else {
      activation_counter = activation_counter - 1;
    }
  }
}