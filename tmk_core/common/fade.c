#include "fade.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

// TODO move to fade.h
// FIXME make timer, pins variable

volatile bool fade_led_key_pressed = 0;

void fade_led_init(void)
{

    fade_led_key_pressed   = false;
    
    cli();
    
    // init pwm on port PB5
    DDRB = 1 << PB5;
    TCCR1A = 1 << COM1A1 | 1 << WGM00 | 1 << WGM02;
    TCCR1B = 1 << WGM02 | 1 << CS00;
    OCR1A = 0xFF;


    // init timer 3
  
    TCCR3A = 0; // normal, kein pwm
    TCCR3B =  1 << CS30; // keinen prescaler
    TIMSK3 = 1 << TOIE3; // interrupt bei overflow
    TCNT3 = 0; 
   
    sei();
}

ISR(TIMER3_OVF_vect)
{
    if(fade_led_key_pressed)
        OCR1A = 0xFF;
    else if(OCR1A > 0x00)
        OCR1A--;
}


