#include "effects.h"
#include "button_receiver.h"

void setup() {
  setupLeds();
  setupButton();

  // salida Serial para debug
  Serial.begin(9600);
}

void loop() {
  checkButtonPress();
  switchEffect();
  //delay(50);
}
