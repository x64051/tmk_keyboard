/*
Copyright 2016 Ethan Apodaca <papodaca@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "led.h"

#define CAPS_LED_DDR  DDRD
#define CAPS_LED_PIN  PD5
#define CAPS_LED_PORT PORTD


#define NUM_LED_DDR  DDRB
#define NUM_LED_PIN  PB5
#define NUM_LED_PORT PORTB


void led_set(uint8_t usb_led) {

    CAPS_LED_DDR |= (1<<CAPS_LED_PIN);
#ifndef FADE_KEY_LED_ENABLE
    NUM_LED_DDR  |= (1<<NUM_LED_PIN);
#endif

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) // output high TODO init only once
        CAPS_LED_PORT &= ~(1<<CAPS_LED_PIN);
    else 
        CAPS_LED_PORT |= (1<<CAPS_LED_PIN);

#ifndef FADE_KEY_LED_ENABLE
    if (usb_led & (1<<USB_LED_NUM_LOCK))
        NUM_LED_PORT &= ~(1<<NUM_LED_PIN);
    else
        NUM_LED_PORT |= (1<<NUM_LED_PIN);
#endif

}
