#include "effects.h"

/* *** VARIABLES *** */
// DEFINICIONES DE PINES
const byte pinButton = 2;  // entrada del botón
const byte fuente = 13;    // pin para usar como fuente 3.3V

// Variables para manipular controlamiento del botón  
int button_val;
int last_button_val = 0;
bool button_pressed = false;
int last_button_press = 0;
int button_debounce = 50;   // ms



/* *** CONFIGURACIONES *** */
// configurar botón
void setupButton() {
  pinMode(pinButton, INPUT);

  // salida de fuente para boton en pulldown
  pinMode(fuente, OUTPUT);
  digitalWrite(fuente, HIGH);
}



/* *** FUNCIONES *** */
// chequear estado del botón
void checkButtonPress() {

  button_val = digitalRead(pinButton);

  if (button_val && !last_button_val) {
    // chequear debounce
    if (millis() - last_button_press > button_debounce) {
      last_button_press = millis();
      button_pressed = true;
    }
  }

  last_button_val = button_val;

  // cambiar efecto
  if (button_pressed) {
    effects_counter += 1;
    button_pressed = false;
    is_turn_off = false;
  }

  // resetear efecto si ya se pasaron todos
  if (effects_counter > total_effects) {
    effects_counter = 0;
  }
}