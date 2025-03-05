#ifndef BUTTON_RECEIVER_H
#define BUTTON_RECEIVER_H

#include "Arduino.h"

/* *** VARIABLES GLOBALES *** */
const bool DEBUG_MODE;

/* *** CONFIGURACIONES *** */
void setupButtons();

/* *** FUNCIONES *** */
void checkEffectButtonPress();
void checkVelButtonByPin(byte pin);
void checkVelButtons();

#endif