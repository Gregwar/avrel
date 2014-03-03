#ifndef _LEDS_H
#define _LEDS_H

// Init al the leds
void setupLeds();

// Gets the number of available leds
int nbLeds();

// Turns on/off a led
void ledOn(int led);
void ledOff(int led);

#endif
