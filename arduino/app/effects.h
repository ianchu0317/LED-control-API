#ifndef EFFECTS_H
#define EFFECTS_H

#include "Arduino.h"

/* *** VARIABLES GLOBALES *** */
extern int effects_counter;
extern int fade_vel;
extern int intercalate_vel;
extern int intercalate_in_out_vel;
extern bool is_turn_off;
extern int total_effects;

/* *** FUNCIONES *** */
// Configuraciones
void setupLeds();
// Auxiliares
void switchEffect();
void turnOff();
void setLedsIntensity(int intensity);
void turnOnLedsSequentially();
void turnOffLedsSequentially();
// Efectos
void intercalateLed();
void fadeLeds();
void intercalateInOut();


#endif