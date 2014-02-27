#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

// BLinks the following led
#define LED_DDR    DDRB
#define LED_PORT   PORTB
#define LED_PIN    PB5

int main (void)
{
    wdt_disable();
    cli();
    // Setting pin 5 of port B as output
    LED_DDR |= _BV(LED_PIN);
    sei();

    while (1) {
        // Led is on
        LED_PORT |= _BV(LED_PIN);
        _delay_ms(1000);

        // Led is off
        LED_PORT &= ~_BV(LED_PIN);
        _delay_ms(1000);
    }
}
