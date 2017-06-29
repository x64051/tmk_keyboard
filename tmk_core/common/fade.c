#include "fade.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

// TODO move to fade.h
// FIXME make timer, pins variable
#define PWM_TABLE_SIZE (232 - 8)
/* #define PWM_MAX 65535 */

const uint16_t pwmtable[PWM_TABLE_SIZE] PROGMEM = {

    /* 1,1,1,1,1,1,1,1, */
    1,1,1,1,1,2,2,2,
    2,2,2,2,2,3,3,3,
    3,3,3,4,4,4,4,5,

    5,5,5,6,6,6,7,7,
    7,8,8,8,9,9,10,10,
    11,12,12,13,13,14,15,16,
    16,17,18,19,20,21,22,23,

    25,26,27,28,30,31,33,35,
    36,38,40,42,44,47,49,52,
    54,57,60,63,66,69,73,76,
    80,84,89,93,98,103,108,113,

    119,125,131,138,144,152,159,167,
    176,185,194,204,214,224,236,247,
    256,256,256,256,256,256,256,256,
    256,256,256,256,256,256,512,512,

    512,512,512,512,512,512,512,768,
    768,768,768,768,768,1024,1024,1024,
    1024,1280,1280,1280,1280,1536,1536,1536,
    1792,1792,1792,2048,2048,2304,2304,2560,

    2560,2816,2816,3072,3072,3328,3584,3584,
    3840,4096,4352,4608,4608,4864,5120,5376,
    5888,6144,6400,6656,7168,7424,7680,8192,
    8704,8960,9472,9984,10496,11008,11520,12288,

    12800,13312,14080,14848,15616,16384,17152,17920,
    18944,19968,20992,22016,23040,24320,25344,26624,
    28160,29440,30976,32512,34048,35840,37632,39424,
    41472,43520,45824,48128,50432,52992,55552,58368,

    61440,64512,65535,65535,65535,65535,65535,30976,

};

volatile int pwm_phase;
volatile uint8_t fade_led_key_pressed = 0;

void fade_led_init(void)
{

    pwm_phase = 0;
    fade_led_key_pressed   = false;
    
    cli();
    
    // init pwm
    DDRB = 1 << PB5;
    TCCR1A = 1 << COM1A1 | 1 << WGM00 | 1 << WGM01 | 1 << WGM02; 
    /* TCCR1A = 1 << COM1A1 | 1 << WGM01 | 1 << WGM00 | 1 << WGM02; */
    TCCR1B = 1 << CS00;
    OCR1A = 0;
    /* OCR1A = PWM_MAX; // INIT cycle */

    // init timer 3
  
    TCCR3A = 0; // normal, kein pwm
    TCCR3B =  1 << CS30; // keinen prescaler
    TIMSK3 = 1 << TOIE3; // interrupt bei overflow
    TCNT3 = 0; 
   
    sei();
}

ISR(TIMER3_OVF_vect)
{
    static int d = 0;
    if(fade_led_key_pressed){
        pwm_phase = 0;
        OCR1A     = 0x00;
    }else{
        if(d==32){
            OCR1A = pgm_read_word(pwmtable + pwm_phase);
            /* uint16_t tmp = pgm_read_word(pwmtable + pwm_phase); */
            /* OCR1AL = tmp & 0x00ff; OCR1AH = tmp >> 8; */
            if(pwm_phase < PWM_TABLE_SIZE - 1)
                pwm_phase++;
        }else{
            d++;
        }
    }    

}


