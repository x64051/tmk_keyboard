#include "action_code.h"
#include "action_macro.h"
#include "action_util.h"
#include "action_layer.h"
#include "progmem.h"
#include "keymap_common.h" 
#include <avr/wdt.h>

// TODO volatile extern bool fade_invert;

// Die verschiedenen Layer. TRNS: transparent, mache das, was auf dem unteren Layer ist
// TODO bootmagic:
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = KEYMAP_XT(  // DEFAULT LAYER. VOLU= lautstärke hoch, MPLY= Play/Pause 
            VOLU,  ESC,   GRV,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,  EQL, BSPC,      FN5,         SLCK,
            MPRV, RGUI,  LGUI,    Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P, LBRC, RBRC,  ENT, HOME, CAPS, PGUP,  BRK, 
            MPLY, RCTL,   LCTL,    A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN, QUOT, BSLS,        END,   UP, PGDN, PENT,
            MNXT,  FN1,   FN3,  FN0,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH,  FN4,  TAB, LEFT, DOWN, RGHT,
            VOLD,  APP,  LALT,                          SPC,                                     RALT,        INS,        DEL
    ),

    // Wenn 1 Aktiviert ist, ist der Nummernblock doch ein Nummernblock
    [1] = KEYMAP_XT(
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,     NLCK,          FN5,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, P7,   P8,   P9,   PMNS,
            TRNS, TRNS,  LCTL, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       P4,   P5,   P6,   PPLS,
            TRNS, TRNS,  LSFT, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, RSFT, TRNS, P1,   P2,   P3,
            TRNS, TRNS,  TRNS,                         TRNS,                                     TRNS,       P0,    PDOT
    ),

    [2] = KEYMAP_XT( // FN LAYER: Pfeiltasten auf HJKL, F-Tasten auf 1-10 und den Tasten daneben
            TRNS, TRNS,  TRNS,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12, TRNS,     TRNS,         TRNS,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  TAB, TRNS, TRNS,  ESC, TRNS, TRNS, TRNS, TRNS, TRNS, PSLS,
            MUTE, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, LEFT, DOWN,   UP, RGHT,  DEL, TRNS, TRNS,       TRNS, TRNS, TRNS, PAST,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, CAPS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PSCR, TRNS, TRNS, TRNS,
            TRNS, TRNS,  TRNS,                         TRNS,                                     TRNS,       TRNS,       TRNS
    ),

    [3] = KEYMAP_XT( // Maussteuerung. nett.
             FN6,  FN7,  TRNS,  F13,  F14,  F15,  F16,  F17,  F18,  F19,  F20,  F21,  F22,  F23,  F24, TRNS,     TRNS,         TRNS,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, WH_L, WH_D, WH_U, WH_R, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
            TRNS, TRNS,  BTN1, BTN3, BTN2, TRNS, TRNS, TRNS, MS_L, MS_D, MS_U, MS_R, TRNS, TRNS, TRNS,       TRNS, FN11, TRNS, TRNS,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  FN8,  FN9, FN10,
            TRNS, MS_ACCEL2,  TRNS,                          BTN1,                                     TRNS,       TRNS, TRNS
    ),

    [4] = KEYMAP_ISO(
            ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,             PSCR,SLCK,BRK,
            GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
            TAB,    Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,    DEL, END, PGDN,    P7,  P8,  P9,
            CAPS,      A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,   ENT,                       P4,  P5,  P6,  PPLS,
            LSFT, ESC,    Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH, RSFT,            UP,           P1,  P2,  P3,
            LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,       LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 
    [0] = KEYMAP_XT(
            VOLU,  ESC,   GRV,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,  EQL, BSPC,      FN5,         SLCK,
            MPRV, RGUI,  LGUI,    Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P, LBRC, RBRC,  ENT, HOME, CAPS, PGDN,  BRK, 
            MPLY, RCTL,   FN2,    A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN, QUOT, BSLS,        END,   UP, PGUP, PENT,
            MNXT,  FN1,   FN3,  FN0,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH,  FN4,  TAB, LEFT, DOWN, RGHT,
            VOLD,  APP,  LALT,                          SPC,                                     CAPS,        INS,        DEL
    ),

    [1] = KEYMAP_XT(
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,     TRNS,         TRNS,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, TRNS,
            TRNS, TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
            TRNS, TRNS,  TRNS,                         TRNS,                                     TRNS,       TRNS,       TRNS
    ),
    */


};

enum function_actions {
    FUNCTION_LSHIFT_LPAREN, // left shift kurz drücken: (
    FUNCTION_RSHIFT_RPAREN, // )
    FUNCTION_REBOOT, // pro micro rebooten
    FUNCTION_BOOTLOADER_JMP, // erklärt sich von selbst
    FUNCTION_LAYER_1_2_TOGGLE, // erklärt sich von selbst
};

/* const PROGMEM uint16_t fn_actions[] = { */
const action_t PROGMEM fn_actions[] = {
    /* FN0 */ ACTION_LAYER_TAP_KEY(2, KC_ESC),
    /* FN1 */ ACTION_LAYER_MOMENTARY(3), 
    /* FN2 */ ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC), // nicht genutzt zurzeit...
    /* FN3 */ ACTION_FUNCTION_TAP(FUNCTION_LSHIFT_LPAREN),
    /* FN4 */ ACTION_FUNCTION_TAP(FUNCTION_RSHIFT_RPAREN),
    /* FN5 */ ACTION_LAYER_TOGGLE(1),
    /* /1* FN5 *1/ TODO ACTION_FUNCTION(FUNCTION_LAYER_1_2_TOGGLE), */

    /* FN6 */ ACTION_FUNCTION_TAP(FUNCTION_BOOTLOADER_JMP),
    /* FN7 */ ACTION_FUNCTION_TAP(FUNCTION_REBOOT),
};

// Hiermit kann der reboot oder bootloader-modus mit einer Tastenkombination
// ausgelöst werden. Sonst müsste man, zumindest beim pro micro, immer zwei Pins
// verbinden
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
// code, der beim drücken der FN-Taste ausgeführt wird
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
            /* TODO
        case FUNCTION_LAYER_1_2_TOGGLE:
            {
                action_t action = ACTION_LAYER_TOGGLE(1);
            }
            layer_state ^= (1<<1); 
            send_keyboard_report();
            fade_invert = layer_state & (1<<1);
            if(layer_state & (1 << 2))
            break;
            */
    }


}

