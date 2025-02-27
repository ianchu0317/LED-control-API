#include "effects.h"

/* *** VARIABLES *** */
// DEFINICIONES DE PINES
// Botón cambio de efectos
const byte pinEffectButton = 2;  // entrada del botón
const byte fuente = 13;    // pin para usar como fuente 5V boton 
// Botones de velocidades


// Variables para manipular controlamiento del botón  
int effect_button_val;
int last_effect_button_val = 0;
bool effect_button_pressed = false;
int last_effect_button_press = 0;
int effect_button_debounce = 200;   // ms para evitar ruido



/* *** CONFIGURACIONES *** */
// configurar botón
void setupButton() {
  pinMode(pinEffectButton, INPUT);

  // salida de fuente para boton en pulldown
  pinMode(fuente, OUTPUT);
  digitalWrite(fuente, HIGH);
}



/* *** FUNCIONES *** */
// chequear estado del botón
void checkButtonPress() {

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