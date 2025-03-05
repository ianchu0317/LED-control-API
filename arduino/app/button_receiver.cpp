#include "effects.h"

/* *** VARIABLES *** */
// DEFINICIONES DE PINES
// Botón cambio de efectos
const byte pinEffectButton = 2;  // entrada del botón
const byte fuente = 13;          // pin para usar como fuente 5v boton 
// Botones de velocidades
const byte pinSpeedUpButton = 4;
const byte pinSpeedDownButton = 7;

const bool DEBUG_MODE = false;

// Variables para controlamiento del botón de efectos
int effect_button_val;
int last_effect_button_val = 0;
bool effect_button_pressed = false;
unsigned long last_effect_button_press = 0;
int effect_button_debounce = 200;   // ms para evitar ruido

// Variables para botones de velocidades
int vel_button_val;
int last_vel_button_val = 0;
int vel_button_debounce = 20;       // ms
unsigned long last_vel_button_press = 0;

#define MAX_SPEED_LEVEL 9
#define MIN_SPEED_LEVEL 1
int current_level = 5;


/* *** CONFIGURACIONES *** */
// Configurar botones
void setupButtons() {
  // Botón de cambio de efectos
  pinMode(pinEffectButton, INPUT);
  // salida de fuente para boton físico (PULL DOWN)
  pinMode(fuente, OUTPUT);
  digitalWrite(fuente, HIGH);

  // Botones de velocidades
  pinMode(pinSpeedUpButton, INPUT);
  pinMode(pinSpeedDownButton, INPUT);
}



/* *** FUNCIONES *** */
// Auxiliares
void speedUpEffects(){
  if (current_level < MAX_SPEED_LEVEL){
    fade_vel = fade_vel - 5;
    intercalate_vel = intercalate_vel - 10;
    intercalate_in_out_vel = intercalate_in_out_vel - 5;
    current_level = current_level + 1;
  }
}


void speedDownEffects(){
  if (current_level > MIN_SPEED_LEVEL){
    fade_vel = fade_vel + 5;
    intercalate_vel = intercalate_vel + 10;
    intercalate_in_out_vel = intercalate_in_out_vel + 5;
    current_level = current_level - 1;
  }
}

void checkVelButtonByPin(byte pin);   // declarar funcion antes de usar


// CHEQUEOS DE BOTON 
// chequear estado del botón de efectos
void checkEffectButtonPress() {

  effect_button_val = digitalRead(pinEffectButton);

  if (effect_button_val && !last_effect_button_val) {
    // chequear debounce
    if (millis() - last_effect_button_press > effect_button_debounce) {
      last_effect_button_press = millis();
      effect_button_pressed = true;
    }
  }

  last_effect_button_val = effect_button_val;

  // cambiar efecto
  if (effect_button_pressed) {
    effects_counter += 1;
    effect_button_pressed = false;
    is_turn_off = false;
  }

  // resetear efecto si ya se pasaron todos
  if (effects_counter > total_effects) {
    effects_counter = 0;
  }
}


// Chequear aumento y disminución de velocidad
void checkVelButtons(){
  checkVelButtonByPin(pinSpeedUpButton);
  checkVelButtonByPin(pinSpeedDownButton);
}


// Chequear estado de botón de velocidad según pin
void checkVelButtonByPin(byte pin){
  vel_button_val = digitalRead(pin);

  if (vel_button_val && !last_vel_button_val){
    
    if (millis() - last_vel_button_press > vel_button_debounce){
      last_vel_button_press = millis();    
      // Aumentar o disminuir velocidades
      if (pin == pinSpeedUpButton){
        speedUpEffects();
      } else {
        speedDownEffects();
      }

      // Debug Velocity
      if (DEBUG_MODE){
        Serial.print("Current level: ");
        Serial.println(current_level);
        Serial.print("Intercalate vel (ms): ");
        Serial.println(intercalate_vel);
        Serial.print("Fade vel (ms): ");
        Serial.println(fade_vel);
        Serial.print("In Out vel: ");
        Serial.println(intercalate_in_out_vel);
        Serial.println();
      }
    }
  }

  last_vel_button_val = vel_button_val;
}
