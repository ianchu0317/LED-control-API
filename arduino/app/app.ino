#include "effects.h"
#include "button_receiver.h"

void setup() {
  setupButtons();
  setupLeds();

  // salida Serial para debug
  Serial.begin(9600);
}

void loop() {
  checkEffectButtonPress();
  checkVelButtons();
  switchEffect();
  //delay(50);
}
