
#ifndef FADE_H
#define FADE_H

#include <stdint.h>
#include <stdbool.h>

extern volatile bool fade_led_key_pressed;
void fade_led_init(void);

/* #define VALUE_PHASE_0() (fade_invert ? 255 : 0) */
#define VALUE_PHASE_0() (255)

#endif
