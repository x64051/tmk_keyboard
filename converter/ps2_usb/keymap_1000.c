#include "action_code.h"
#include "action_macro.h"
#include "action_util.h"
#include "progmem.h"
#include "keymap_common.h" 
#include <avr/wdt.h>


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    KEYMAP_ISO(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10,     F11, F12,          PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    LGUI, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC, RBRC,         DEL, END, PGDN,    P7,  P8,  P9,
    LCTL, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN, QUOT, BSLS,ENT,                      P4,  P5,  P6,  PPLS,
    FN3,FN0,Z, X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          FN4,           UP,         P1,  P2,  P3,
    FN1,TRNS,LALT,        SPC,               RALT,   TRNS,   TRNS,   LCTL,      LEFT,DOWN,RGHT,   P0,     PDOT,PENT
    ),

    KEYMAP_ISO(
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS,
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,     TRNS, TRNS, TRNS, TRNS, \
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS,     TRNS, TRNS, TRNS,       \
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LEFT, DOWN, UP,   RGHT, TRNS, TRNS, TRNS, TRNS,                       TRNS, TRNS, TRNS, TRNS, \
TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,                  TRNS,           TRNS, TRNS, TRNS,       \
    TRNS, TRNS, TRNS,           TRNS,                  TRNS, TRNS, TRNS, TRNS,          TRNS, TRNS, TRNS,      TRNS, TRNS, TRNS        \
    ),

    KEYMAP_ISO(
     TRNS,  FN6,  FN7, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS,
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,     TRNS, TRNS, TRNS, TRNS, \
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS,     TRNS, TRNS, TRNS,       \
     TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, MS_L, MS_D, MS_U, MS_R, TRNS, TRNS, TRNS, TRNS,                       TRNS, TRNS, TRNS, TRNS, \
TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,                  TRNS,           TRNS, TRNS, TRNS,       \
    TRNS, TRNS, TRNS,           TRNS,                  TRNS, TRNS, TRNS, TRNS,          TRNS, TRNS, TRNS,      TRNS, TRNS, TRNS        \
    ),

};                                                                                                       


enum function_actions {
    FUNCTION_LSHIFT_LPAREN,
    FUNCTION_RSHIFT_RPAREN,
    FUNCTION_REBOOT,
    FUNCTION_BOOTLOADER_JMP,
};

/* const PROGMEM uint16_t fn_actions[] = { */
const action_t PROGMEM fn_actions[] = {
    /* FN0 */ ACTION_LAYER_TAP_KEY(1, KC_ESC),
    /* FN1 */ ACTION_LAYER_TAP_KEY(2, KC_TAB),  // XXX NOT USED
    /* /1* FN1 *1/ ACTION_LAYER_MOMENTARY(2),  // XXX NOT USED */
    /* FN2 */ ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC), // XXX also not used
    /* FN3 */ ACTION_FUNCTION_TAP(FUNCTION_LSHIFT_LPAREN),
    /* FN4 */ ACTION_FUNCTION_TAP(FUNCTION_RSHIFT_RPAREN),
    /* FN5 */ ACTION_LAYER_TOGGLE(1),

    /* FN6 */ ACTION_FUNCTION_TAP(FUNCTION_BOOTLOADER_JMP),
    /* FN7 */ ACTION_FUNCTION_TAP(FUNCTION_REBOOT),
};

void promicro_bootloader_jmp(bool program) { // if not: reboot
    uint16_t *const bootKeyPtr = (uint16_t *)0x0800;
    // Value used by Caterina bootloader use to determine whether to run the
    // sketch or the bootloader programmer.
    uint16_t bootKey = program ? 0x7777 : 0;
    *bootKeyPtr = bootKey;
    // setup watchdog timeout
    wdt_enable(WDTO_60MS);
    while(1) {} // wait for watchdog timer to trigger
}



#define IF_EVENT_PRESSED (!event->event.pressed) 

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt){

    switch(id){

        case FUNCTION_BOOTLOADER_JMP: 
            if (! IF_EVENT_PRESSED) break;
            xprintf("enter bootloader...\r\n");
            promicro_bootloader_jmp(true);
            break;

        case FUNCTION_REBOOT:
            if (! IF_EVENT_PRESSED) break;
            xprintf("rebooting...\r\n");
            promicro_bootloader_jmp(false);
            break;

        case FUNCTION_LSHIFT_LPAREN:
            // Shift parentheses example: LShft + tap '('
            // http://stevelosh.com/blog/2012/10/a-modern-space-cadet/#shift-parentheses
            // http://geekhack.org/index.php?topic=41989.msg1304899#msg1304899
            if (event->event.pressed) {
                if (event->tap.count > 0 && !event->tap.interrupted) {
                    if (event->tap.interrupted) {
                        /* dprint("tap interrupted\n"); */
                        register_mods(MOD_BIT(KC_LSHIFT));
                    }
                } else {
                    register_mods(MOD_BIT(KC_LSHIFT));
                }
            } else {
                if (event->tap.count > 0 && !(event->tap.interrupted)) {
                    add_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    register_code(KC_9);
                    unregister_code(KC_9);
                    del_weak_mods(MOD_BIT(KC_LSHIFT));
                    send_keyboard_report();
                    event->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_LSHIFT));
                }
            }

            break;

        case FUNCTION_RSHIFT_RPAREN:
            if (event->event.pressed) {
                if (event->tap.count > 0 && !event->tap.interrupted) {
                    if (event->tap.interrupted) {
                        /* dprint("tap interrupted\n"); */
                        register_mods(MOD_BIT(KC_RSHIFT));
                    }
                } else {
                    register_mods(MOD_BIT(KC_RSHIFT));
                }
            } else {
                if (event->tap.count > 0 && !(event->tap.interrupted)) {
                    add_weak_mods(MOD_BIT(KC_RSHIFT));
                    send_keyboard_report();
                    register_code(KC_0);
                    unregister_code(KC_0);
                    del_weak_mods(MOD_BIT(KC_RSHIFT));
                    send_keyboard_report();
                    event->tap.count = 0;  // ad hoc: cancel tap
                } else {
                    unregister_mods(MOD_BIT(KC_RSHIFT));
                }
            }

            break;

    }


}
