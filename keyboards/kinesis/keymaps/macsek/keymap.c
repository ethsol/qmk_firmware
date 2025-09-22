// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum/caps_word.h"  // Caps Word functionality
#include "print.h"  // Always include for dynamic debug

// Dynamic debug flag - toggled via custom keycode
static bool debug_enabled = false;

enum custom_layers {
    QWERTY,        // Base qwerty
    COLEMAKDH,     // Colemak-DH layout eredeti
    COLEMAKDH_HUN, // Colemak-DH layout magyar (csak ZY csere)
    KEYPAD
};

// LED pin definitions
#define KEYPAD_LED_PIN C3
#define CAPS_LOCK_LED_PIN C1
#define NUM_LOCK_LED_PIN C5
#define SCROLL_LOCK_LED_PIN C4


// Változó az előző layer tárolására
uint8_t previous_layer = QWERTY;
uint8_t previous_colemak_layer = COLEMAKDH_HUN;

/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Caps   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | INS  | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/



// void dance_1_finished(tap_dance_state_t *state, void *user_data) {
//     if (state->count == 1) {
//         tap_code(KC_1);  // Tap-ra az 1-et küldi
//     } else {
//         tap_code(KC_F1); // Dupla tap-ra az F1-et küldi
//     }
// }

// void dance_1_reset(tap_dance_state_t *state, void *user_data) {
//     if (state->pressed) {
//         tap_code(KC_F1);  // Hold-ra az F1-et küldi
//     }
// }


void dance_1_f1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F1);  // Hold-ra az F1-et küldi
    } else if (state->count == 1) {
        tap_code(KC_1);   // Tap-ra az 1-et küldi
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    // Nincs szükség külön reset logikára ebben az esetben
}

// Tap Dance functions for each enum item



void dance_2_f2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F2);  // Hold-ra az F2-t küldi
    } else if (state->count == 1) {
        tap_code(KC_2);   // Tap-ra a 2-t küldi
    }
}

void dance_3_f3_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F3);  // Hold-ra az F3-t küldi
    } else if (state->count == 1) {
        tap_code(KC_3);   // Tap-ra a 3-t küldi
    }
}

void dance_4_f4_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F4);  // Hold-ra az F4-t küldi
    } else if (state->count == 1) {
        tap_code(KC_4);   // Tap-ra a 4-t küldi
    }
}

void dance_5_f5_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F5);  // Hold-ra az F5-t küldi
    } else if (state->count == 1) {
        tap_code(KC_5);   // Tap-ra az 5-t küldi
    }
}

void dance_6_f6_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F6);  // Hold-ra az F6-t küldi
    } else if (state->count == 1) {
        tap_code(KC_6);   // Tap-ra a 6-ot küldi
    }
}

void dance_7_f7_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F7);  // Hold-ra az F7-t küldi
    } else if (state->count == 1) {
        tap_code(KC_7);   // Tap-ra a 7-t küldi
    }
}

void dance_8_f8_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F8);  // Hold-ra az F8-t küldi
    } else if (state->count == 1) {
        tap_code(KC_8);   // Tap-ra a 8-ot küldi
    }
}

void dance_9_f9_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F9);  // Hold-ra az F9-t küldi
    } else if (state->count == 1) {
        tap_code(KC_9);   // Tap-ra a 9-ot küldi
    }
}

void dance_0_f10_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F10); // Hold-ra az F10-et küldi
    } else if (state->count == 1) {
        tap_code(KC_GRV);   // Tap-ra a 0-át küldi
    }
}

void dance_0_f11_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F11); // Hold-ra az F11-et küldi
    } else if (state->count == 1) {
        tap_code(KC_0);   // Tap-ra a 0-át küldi
    }
}

void dance_m_f12_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code(KC_F12); // Hold-ra az F12-t küldi
    } else if (state->count == 1) {
        tap_code(KC_MINS);    // Tap-ra az M-et küldi
    }
}


// Tap Dance CAPS bekapcsolo logika
void dance_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_CAPS);    // Hosszan lenyomva Caps Lock
    } else if (state->count == 1) {
        caps_word_on();            // Egyszeri koppintásra Caps Word mód
    } else if (state->count == 2) {
        tap_code(KC_ESC);          // Dupla koppintásra ESC
    }
}

// Tap Dance CAPS kikapcsolo logika
void dance_caps_reset(tap_dance_state_t *state, void *user_data) {
    if (! state->pressed) {
        unregister_code(KC_CAPS);  // Caps Lock felengedése, ha hosszan nyomva volt
    } /* else {
        caps_word_off();           // Caps Word mód kikapcsolása
    } */
}

// Tap Dance callback a bal Alt gombhoz
void dance_lalt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_LALT);  // Ha tartjuk, Alt gombot küldi
    } else if (state->count == 1) {
        tap_code16(S(KC_8));     // 1 Tap: '('
    } else if (state->count == 2) {
        tap_code16(RALT(KC_F));  // 2 Tap: '['
    } else if (state->count == 3) {
        tap_code16(RALT(KC_B));  // 3 Tap: '{'
    }
}

// Tap Dance reset callback a bal Alt gombhoz
void dance_lalt_reset(tap_dance_state_t *state, void *user_data) {
    if (! state->pressed) {
        unregister_code(KC_LALT);  // Felengedéskor engedi el az Alt-ot, ha nyomva volt
    }
}

// Tap Dance callback a jobb AltGr gombhoz
void dance_ralt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_RALT);  // Ha tartjuk, AltGr gombot küldi
    } else if (state->count == 1) {
        tap_code16(S(KC_9));     // 1 Tap: ')'
    } else if (state->count == 2) {
        tap_code16(RALT(KC_G));  // 2 Tap: ']'
    } else if (state->count == 3) {
        tap_code16(RALT(KC_N));  // 3 Tap: '}'
    }
}

// Tap Dance reset callback a jobb AltGr gombhoz
void dance_ralt_reset(tap_dance_state_t *state, void *user_data) {
    if (! state->pressed) {
        unregister_code(KC_RALT);  // Felengedéskor engedi el az AltGr-ot, ha nyomva volt
    }
}

// https://docs.qmk.fm/features/tap_dance
// Tap Dance declarations
enum {
    TD_CAPS_ESC,
    TD_1_F1,
    TD_2_F2,
    TD_3_F3,
    TD_4_F4,
    TD_5_F5,
    TD_6_F6,
    TD_7_F7,
    TD_8_F8,
    TD_9_F9,
    TD_0_F10,
    TD_0_F11,
    TD_M_F12,
    TD_LALT,  // Bal Alt nyito zarojelekhez
    TD_RALT,  // AltGr zaro zarojelekhez
};

// Custom keycodes for layer switching
enum custom_keycodes {
    TO_KEYPAD = SAFE_RANGE,
    FROM_KEYPAD,
    TOGGLE_LAYOUT,
    TO_QWERTY,
    TO_COLEMAKDH,
    TO_COLEMAKDH_HUN,
    DEBUG_TOGGLE,  // Debug mode toggle
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // [TD_CAPS_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_CAPS, KC_ESC),   // Tap once for Caps Lock, twice for Escape
    [TD_CAPS_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_finished, dance_caps_reset), // Tap once for Caps Word, twice for Escape, hold for Caps Lock

    [TD_1_F1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_f1_finished, NULL),
    [TD_2_F2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_f2_finished, NULL),
    [TD_3_F3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_f3_finished, NULL),
    [TD_4_F4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_4_f4_finished, NULL),
    [TD_5_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_f5_finished, NULL),
    [TD_6_F6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_6_f6_finished, NULL),
    [TD_7_F7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_7_f7_finished, NULL),
    [TD_8_F8] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_8_f8_finished, NULL),
    [TD_9_F9] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_9_f9_finished, NULL),
    [TD_0_F10] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_f10_finished, NULL),
    [TD_0_F11] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_f11_finished, NULL),
    [TD_M_F12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_m_f12_finished, NULL),

    [TD_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lalt_finished, dance_lalt_reset),
    [TD_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ralt_finished, dance_ralt_reset),
};

#define CAPS_ESC TD(TD_CAPS_ESC)
#define ENT_KEYP LT(KEYPAD, KC_ENT)  // Visszaváltva LT-re, mert a layer sorrend már helyes

#define ALT_OPEN TD(TD_LALT)
#define ALT_CLSE TD(TD_RALT)

// Custom keycode handling function
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef DEBUG
        // LED villogás minden gombnyomásra - hogy lássuk meghívódik-e a függvény
        if (record->event.pressed) {
            writePinLow(CAPS_LOCK_LED_PIN);
            wait_ms(50);
            writePinHigh(CAPS_LOCK_LED_PIN);
        }
    #endif

    switch (keycode) {
        case TO_KEYPAD:
            if (record->event.pressed) {
                // Tároljuk az aktuális layert mielőtt a KEYPAD-ra váltunk
                previous_layer = get_highest_layer(layer_state);
                layer_move(KEYPAD);
                #ifdef DEBUG
                    uprintf("TO_KEYPAD pressed, storing layer %d, switching to KEYPAD\n", previous_layer);
                    // Jelzés: 2x villogás NUM LED
                    writePinLow(NUM_LOCK_LED_PIN); wait_ms(100); writePinHigh(NUM_LOCK_LED_PIN);
                    wait_ms(100);
                    writePinLow(NUM_LOCK_LED_PIN); wait_ms(100); writePinHigh(NUM_LOCK_LED_PIN);
                #endif
            }
            return false;

        case FROM_KEYPAD:
            if (record->event.pressed) {
                // Visszaváltunk az előzőleg tárolt layerre
                layer_move(previous_layer);
                #ifdef DEBUG
                    // Jelzés: 1x hosszú villogás SCROLL LED
                    writePinLow(SCROLL_LOCK_LED_PIN); wait_ms(300); writePinHigh(SCROLL_LOCK_LED_PIN);
                #endif
            }
            return false;

        case TOGGLE_LAYOUT:
            if (record->event.pressed) {
                // Váltás QWERTY és COLEMAKDH_HUN között
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer == COLEMAKDH_HUN || current_layer == COLEMAKDH) {
                    previous_colemak_layer = current_layer; // Tároljuk az aktuális ColemakDH layert
                    layer_move(QWERTY);
                } else if (current_layer == QWERTY) {
                    layer_move(previous_colemak_layer);
                }
                #ifdef DEBUG
                    // Jelzés: 3x gyors villogás KEYPAD LED
                    for(int i = 0; i < 3; i++) {
                        writePinLow(KEYPAD_LED_PIN); wait_ms(50); writePinHigh(KEYPAD_LED_PIN); wait_ms(50);
                    }
                #endif
            }
            return false;

        case TO_QWERTY:
            if (record->event.pressed) {
                layer_move(QWERTY);
                #ifdef DEBUG
                    // Jelzás: 1x villogás CAPS LED
                    writePinLow(CAPS_LOCK_LED_PIN); wait_ms(200); writePinHigh(CAPS_LOCK_LED_PIN);
                #endif
            }
            return false;

        case TO_COLEMAKDH:
            if (record->event.pressed) {
                #ifdef DEBUG
                    uprintf("TO_COLEMAKDH pressed, switching to layer %d\n", COLEMAKDH);
                    layer_move(COLEMAKDH);
                    uprintf("Current layer after switch: %d\n", get_highest_layer(layer_state));
                    // Jelzés: 1x villogás SCROLL LED
                    writePinLow(SCROLL_LOCK_LED_PIN); wait_ms(200); writePinHigh(SCROLL_LOCK_LED_PIN);
                #else
                    layer_move(COLEMAKDH);
                #endif
            }
            return false;

        case TO_COLEMAKDH_HUN:
            if (record->event.pressed) {
                #ifdef DEBUG
                    uprintf("TO_COLEMAKDH_HUN pressed, switching to layer %d\n", COLEMAKDH_HUN);
                    layer_move(COLEMAKDH_HUN);
                    uprintf("Current layer after switch: %d\n", get_highest_layer(layer_state));
                    // Jelzés: 1x villogás NUM LED
                    writePinLow(NUM_LOCK_LED_PIN); wait_ms(200); writePinHigh(NUM_LOCK_LED_PIN);
                #else
                    layer_move(COLEMAKDH_HUN);
                #endif
            }
            return false;

        case DEBUG_TOGGLE:
            if (record->event.pressed) {
                debug_enabled = !debug_enabled;
                debug_enable = debug_enabled;  // QMK global debug flag
                if (debug_enabled) {
                    uprintf("Debug mode ENABLED\n");
                    // Jelzés: 3x gyors villogás CAPS LED
                    for (int i = 0; i < 3; i++) {
                        writePinLow(SCROLL_LOCK_LED_PIN); wait_ms(100);
                        writePinHigh(SCROLL_LOCK_LED_PIN); wait_ms(100);
                    }
                } else {
                    uprintf("Debug mode DISABLED\n");
                    // Jelzés: 1x hosszú villogás CAPS LED
                    writePinLow(SCROLL_LOCK_LED_PIN); wait_ms(500); writePinHigh(SCROLL_LOCK_LED_PIN);
                }
            }
            return false;
    }
    return true;
}const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Stock layout: [QWERTY] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TO(KEYPAD),XXXXXXX,
    KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                                                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_GRV,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  KC_LALT,                                               KC_RGUI,  KC_RCTL,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  KC_ENTER, KC_SPC
  ),
 */

  [QWERTY] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TO_KEYPAD,TOGGLE_LAYOUT,
    TD(TD_0_F10), TD(TD_1_F1),  TD(TD_2_F2),  TD(TD_3_F3),  TD(TD_4_F4),  TD(TD_5_F5),                                           TD(TD_6_F6),  TD(TD_7_F7),  TD(TD_8_F8),  TD(TD_9_F9),  TD(TD_0_F11), TD(TD_M_F12),
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    CAPS_ESC, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_EQL,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  /*KC_LALT*/ALT_OPEN,                                               KC_RGUI,  /*KC_RALT*/ALT_CLSE,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  /*KC_ENTER*/ENT_KEYP, KC_SPC
  ),

  [COLEMAKDH] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TO_KEYPAD,TOGGLE_LAYOUT,
    TD(TD_0_F10), TD(TD_1_F1),  TD(TD_2_F2),  TD(TD_3_F3),  TD(TD_4_F4),  TD(TD_5_F5),                                                                   TD(TD_6_F6),  TD(TD_7_F7),  TD(TD_8_F8),  TD(TD_9_F9),  TD(TD_0_F11), TD(TD_M_F12),
    KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                                                                      KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_BSLS,
    CAPS_ESC, KC_A,     KC_R,     KC_S,     KC_T,     KC_G,                                                                      KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                                                                      KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_EQL,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  /*KC_LALT*/ALT_OPEN,                                               KC_RGUI,  /*KC_RALT*/ALT_CLSE,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  /*KC_ENTER*/ENT_KEYP, KC_SPC
  ),

  [COLEMAKDH_HUN] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TO_KEYPAD,TOGGLE_LAYOUT,
    TD(TD_0_F10), TD(TD_1_F1),  TD(TD_2_F2),  TD(TD_3_F3),  TD(TD_4_F4),  TD(TD_5_F5),                                                                   TD(TD_6_F6),  TD(TD_7_F7),  TD(TD_8_F8),  TD(TD_9_F9),  TD(TD_0_F11), TD(TD_M_F12),
    KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                                                                      KC_J,     KC_L,     KC_U,     KC_Z,     KC_SCLN,  KC_BSLS,
    CAPS_ESC, KC_A,     KC_R,     KC_S,     KC_T,     KC_G,                                                                      KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,
    KC_LSFT,  KC_Y,     KC_X,     KC_C,     KC_D,     KC_V,                                                                      KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_EQL,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  /*KC_LALT*/ALT_OPEN,                                               KC_RGUI,  /*KC_RALT*/ALT_CLSE,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  /*KC_ENTER*/ENT_KEYP, KC_SPC
  ),

  [KEYPAD] = LAYOUT(
    KC_ESC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS, FROM_KEYPAD, QK_BOOT,
    KC_NO,   TO_QWERTY, TO_COLEMAKDH, TO_COLEMAKDH_HUN, KC_NO,    KC_NO,                                                         DEBUG_TOGGLE,   KC_NUM,  KC_PEQL, KC_PSLS, KC_PAST,  KC_NO,
    KC_TAB,  KC_NO,    KC_NO,    MS_UP,   MS_BTN1, MS_WHLU,                                                                      MS_BTN2, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS,  KC_NO,
    CAPS_ESC,MS_BTN2, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN3,                                                                        MS_BTN1, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,  KC_NO,
    KC_LSFT, KC_NO,    KC_NO,    MS_WHLL, MS_WHLR, MS_WHLD,                                                                      MS_BTN3, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,  KC_RSFT,
            KC_NO,    KC_INS,  KC_LEFT, KC_RGHT,                                                                                          KC_UP,   KC_DOWN, KC_PDOT, KC_PENT,
                                                KC_LCTL,  /*KC_LALT*/ALT_OPEN,                                         KC_APP,  KC_RCTL,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  KC_ENT, KC_KP_0
    )

};

void matrix_init_user(void) {
    setPinOutput(KEYPAD_LED_PIN);       // Set pin as output for KEYPAD_LED
    setPinOutput(CAPS_LOCK_LED_PIN);    // Set pin as output for CAPS_LOCK_LED
    setPinOutput(NUM_LOCK_LED_PIN);     // Set pin as output for NUM_LOCK_LED
    setPinOutput(SCROLL_LOCK_LED_PIN);  // Set pin as output for SCROLL_LOCK_LED

    writePinHigh(KEYPAD_LED_PIN);       // Set pin as output for KEYPAD_LED
    writePinHigh(CAPS_LOCK_LED_PIN);    // Set pin as output for CAPS_LOCK_LED
    writePinHigh(NUM_LOCK_LED_PIN);     // Set pin as output for NUM_LOCK_LED
    writePinHigh(SCROLL_LOCK_LED_PIN);  // Set pin as output for SCROLL_LOCK_LED

#ifdef DEBUG
    // KEZDES JELZES: 3x villogás minden LED-del
    for (int i = 0; i < 3; i++) {
        writePinLow(CAPS_LOCK_LED_PIN);
        writePinLow(NUM_LOCK_LED_PIN);
        writePinLow(SCROLL_LOCK_LED_PIN);
        writePinLow(KEYPAD_LED_PIN);
        wait_ms(200);
        writePinHigh(CAPS_LOCK_LED_PIN);
        writePinHigh(NUM_LOCK_LED_PIN);
        writePinHigh(SCROLL_LOCK_LED_PIN);
        writePinHigh(KEYPAD_LED_PIN);
        wait_ms(200);
    }
#endif
#ifdef LED_BLINK_AT_STARTUP
    #define BLINK_DELAY_MS 100
    for (int i = 0; i < 10; i++) {
        writePinLow(CAPS_LOCK_LED_PIN);
        wait_ms(BLINK_DELAY_MS);
        writePinHigh(CAPS_LOCK_LED_PIN);
        wait_ms(BLINK_DELAY_MS);
    }
    for (int i = 0; i < 10; i++) {
        writePinLow(NUM_LOCK_LED_PIN);
        wait_ms(BLINK_DELAY_MS);
        writePinHigh(NUM_LOCK_LED_PIN);
        wait_ms(BLINK_DELAY_MS);
    }
    for (int i = 0; i < 10; i++) {
        writePinLow(SCROLL_LOCK_LED_PIN);
        wait_ms(BLINK_DELAY_MS);
        writePinHigh(SCROLL_LOCK_LED_PIN);
        wait_ms(BLINK_DELAY_MS);
    }
    for (int i = 0; i < 10; i++) {
        writePinLow(KEYPAD_LED_PIN); // Turn off KEYPAD_LED
        wait_ms(BLINK_DELAY_MS);
        writePinHigh(KEYPAD_LED_PIN); // Turn on KEYPAD_LED
        wait_ms(BLINK_DELAY_MS);
    }
#endif

#define FUTOFENY
#ifdef FUTOFENY
    #define FUTOFENY_LED(pin) {writePinLow(pin); wait_ms(100); writePinHigh(pin);}
    for(int i = 0; i < 2; i++){
        FUTOFENY_LED(CAPS_LOCK_LED_PIN)
        FUTOFENY_LED(NUM_LOCK_LED_PIN)
        FUTOFENY_LED(SCROLL_LOCK_LED_PIN)
        FUTOFENY_LED(KEYPAD_LED_PIN)
        FUTOFENY_LED(KEYPAD_LED_PIN)
        FUTOFENY_LED(SCROLL_LOCK_LED_PIN)
        FUTOFENY_LED(NUM_LOCK_LED_PIN)
        FUTOFENY_LED(CAPS_LOCK_LED_PIN)}
#endif

    // writePinHigh(KEYPAD_LED_PIN); // Ensure the LED is off at startup
    // writePinHigh(CAPS_LOCK_LED_PIN); // Ensure the LED is off at startup
}
// Timer variables
uint16_t caps_lock_led_timer = 0;
bool caps_lock_led_state = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (debug_enabled) {
        // Csak akkor írunk, ha ténylegesen változott a layer
        static uint8_t last_layer = 255;
        uint8_t current_layer = get_highest_layer(state);
        if (current_layer != last_layer) {
            uprintf("Layer changed: %d -> %d (state: %08lX)\n", last_layer, current_layer, state);
            last_layer = current_layer;
        }
    }
    // KEYPAD LED kezelése
    if (layer_state_cmp(state, KEYPAD)) {  // If KEYPAD layer is active
        writePinLow(KEYPAD_LED_PIN); // Turn on KEYPAD_LED
    } else { // If KEYPAD layer is not active
        writePinHigh(KEYPAD_LED_PIN); // Turn off KEYPAD_LED
    }    // Check for Caps Word state and toggle Caps Lock LED
    if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
        // Caps Word is active, toggle Caps Lock LED
        if (timer_elapsed(caps_lock_led_timer) > 100) { // 100ms
            caps_lock_led_timer = timer_read();
            caps_lock_led_state = !caps_lock_led_state;
            if (caps_lock_led_state) {
                writePinLow(CAPS_LOCK_LED_PIN); // Turn on CAPS_LOCK_LED for 30ms
                // timer_set(caps_lock_led_timer, 30); // Set timer for 30ms
                // Helyette használjuk a timer_read függvényt
                caps_lock_led_timer = timer_read() + 30;
            } else {
                writePinHigh(CAPS_LOCK_LED_PIN); // Turn off CAPS_LOCK_LED for 70ms
                // timer_set(caps_lock_led_timer, 70); // Set timer for 70ms
                // Helyette használjuk a timer_read függvényt
                caps_lock_led_timer = timer_read() + 70;
            }
        }
    } else {
        // Caps Word is not active, turn off Caps Lock LED
        writePinHigh(CAPS_LOCK_LED_PIN);
    }

    return state;
}
void matrix_scan_user(void) {
    // Call the layer state set function to ensure LED state is updated continuously
    layer_state_t current_layer = layer_state;
    layer_state_set_user(current_layer);
}
