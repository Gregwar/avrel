#include <avr/io.h>
#include "leds.h"

// Blinks the following leds one by one
#define LED_DDR    DDRB
#define LED_PORT   PORTB
int leds[] = {PB1, PB2, PB3, PB4};
#define NB_LEDS ((sizeof(leds))/sizeof(int))
    
// Initializing all leds
void setupLeds()
{
    int led;

    // Setting pin 5 of port B as output
    for (led=0; led<NB_LEDS; led++) {
        LED_DDR |= _BV(leds[led]);
    }
}

// Getting the number of leds
int nbLeds()
{
    return NB_LEDS;
}

// Turning on a led
void ledOn(int led)
{
    LED_PORT |= _BV(leds[led]);
}

// Turning off a led
void ledOff(int led)
{
    LED_PORT &= ~_BV(leds[led]);
}
