#include "effects.h"
#include "button_receiver.h"

void setup() {
  setupButtons();
  setupLeds();

  // salida Serial para debug
  if (DEBUG_MODE){
    Serial.begin(9600);
  }
}

void loop() {
  checkEffectButtonPress();
  checkVelButtons();
  switchEffect();
  //delay(50);
}
