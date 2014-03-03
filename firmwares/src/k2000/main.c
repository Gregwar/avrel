#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include "leds.h"

int main (void)
{
    int led;

    wdt_disable();
    cli();
    setupLeds();
    sei();

    while (1) {
        for (led=0; led<nbLeds(); led++) {
            // Turning led ON
            ledOn(led);
            _delay_ms(1000);

            // Turning led OFF
            ledOff(led);
        }
    }
}
