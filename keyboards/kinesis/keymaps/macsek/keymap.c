// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum/caps_word.h"  // Caps Word functionality
#include "print.h"  // Always include for dynamic debug

// Dynamic debug flag - toggled via custom keycode
static bool debug_enabled = false;

enum custom_layers {
    QWERTY,        // Base qwerty
    COLEMAKDH,     // Colemak-DH layout original
    COLEMAKDH_HUN, // Colemak-DH layout Hungarian (only ZY swap)
    KEYPAD
};

// LED pin definitions
#define KEYPAD_LED_PIN C3
#define CAPS_LOCK_LED_PIN C1
#define NUM_LOCK_LED_PIN C5
#define SCROLL_LOCK_LED_PIN C4


// Variable to store the previous layer
uint8_t previous_layer = QWERTY;
uint8_t previous_colemak_layer = COLEMAKDH_HUN;

// Tap Dance state tracking for number keys
typedef struct {
    bool is_press_action;
    uint8_t state;
} td_tap_t;

enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_TAP_HOLD
};

// State tracking variables for each number key
static td_tap_t td_state_1 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_2 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_3 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_4 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_5 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_6 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_7 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_8 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_9 = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_state_g = {.is_press_action = true, .state = TD_NONE};  // For grave/F10
static td_tap_t td_state_0 = {.is_press_action = true, .state = TD_NONE};  // For 0/F11
static td_tap_t td_state_m = {.is_press_action = true, .state = TD_NONE};  // For minus/F12

// Helper function to determine tap dance state
uint8_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (!state->pressed) return TD_DOUBLE_TAP;
        else return TD_TAP_HOLD;
    } else {
        return state->count; // For 3+ taps, return count directly
    }
}

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
void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    // No special reset logic needed
}
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
    td_state_1.state = cur_dance(state);
    switch (td_state_1.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_1);
            break;
        case TD_SINGLE_HOLD:
            // Simple hold (no tap before) → number repeat
            register_code(KC_1);
            break;
        case TD_TAP_HOLD:
            // Tap&hold → F-key repeat
            register_code(KC_F1);
            break;
        default:
            // For 2+ taps (double tap, triple tap, etc.)
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_1);
            }
            break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_1.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_1);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F1);
            break;
    }
    td_state_1.state = TD_NONE;
}

// Tap Dance functions for each enum item



void dance_2_f2_finished(tap_dance_state_t *state, void *user_data) {
    td_state_2.state = cur_dance(state);
    switch (td_state_2.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_2);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_2);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F2);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_2);
            }
            break;
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_2.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_2);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F2);
            break;
    }
    td_state_2.state = TD_NONE;
}

void dance_3_f3_finished(tap_dance_state_t *state, void *user_data) {
    td_state_3.state = cur_dance(state);
    switch (td_state_3.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_3);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_3);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F3);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_3);
            }
            break;
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_3.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_3);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F3);
            break;
    }
    td_state_3.state = TD_NONE;
}

void dance_4_f4_finished(tap_dance_state_t *state, void *user_data) {
    td_state_4.state = cur_dance(state);
    switch (td_state_4.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_4);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_4);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F4);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_4);
            }
            break;
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_4.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_4);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F4);
            break;
    }
    td_state_4.state = TD_NONE;
}

void dance_5_f5_finished(tap_dance_state_t *state, void *user_data) {
    td_state_5.state = cur_dance(state);
    switch (td_state_5.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_5);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_5);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F5);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_5);
            }
            break;
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_5.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_5);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F5);
            break;
    }
    td_state_5.state = TD_NONE;
}

void dance_6_f6_finished(tap_dance_state_t *state, void *user_data) {
    td_state_6.state = cur_dance(state);
    switch (td_state_6.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_6);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_6);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F6);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_6);
            }
            break;
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_6.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_6);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F6);
            break;
    }
    td_state_6.state = TD_NONE;
}

void dance_7_f7_finished(tap_dance_state_t *state, void *user_data) {
    td_state_7.state = cur_dance(state);
    switch (td_state_7.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_7);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_7);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F7);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_7);
            }
            break;
    }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_7.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_7);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F7);
            break;
    }
    td_state_7.state = TD_NONE;
}

void dance_8_f8_finished(tap_dance_state_t *state, void *user_data) {
    td_state_8.state = cur_dance(state);
    switch (td_state_8.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_8);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_8);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F8);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_8);
            }
            break;
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_8.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_8);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F8);
            break;
    }
    td_state_8.state = TD_NONE;
}

void dance_9_f9_finished(tap_dance_state_t *state, void *user_data) {
    td_state_9.state = cur_dance(state);
    switch (td_state_9.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_9);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_9);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F9);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_9);
            }
            break;
    }
}

void dance_9_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_9.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_9);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F9);
            break;
    }
    td_state_9.state = TD_NONE;
}

void dance_g_f10_finished(tap_dance_state_t *state, void *user_data) {
    td_state_g.state = cur_dance(state);
    switch (td_state_g.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_GRV);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_GRV);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F10);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_GRV);
            }
            break;
    }
}

void dance_g_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_g.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_GRV);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F10);
            break;
    }
    td_state_g.state = TD_NONE;
}

void dance_0_f11_finished(tap_dance_state_t *state, void *user_data) {
    td_state_0.state = cur_dance(state);
    switch (td_state_0.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_0);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_0);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F11);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_0);
            }
            break;
    }
}

void dance_0_f11_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_0.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_0);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F11);
            break;
    }
    td_state_0.state = TD_NONE;
}

void dance_m_f12_finished(tap_dance_state_t *state, void *user_data) {
    td_state_m.state = cur_dance(state);
    switch (td_state_m.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MINS);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_MINS);
            break;
        case TD_TAP_HOLD:
            register_code(KC_F12);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code(KC_MINS);
            }
            break;
    }
}

void dance_m_f12_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state_m.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_MINS);
            break;
        case TD_TAP_HOLD:
            unregister_code(KC_F12);
            break;
    }
    td_state_m.state = TD_NONE;
}


// Tap Dance CAPS activation logic
void dance_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_CAPS);    // Long press for Caps Lock
    } else if (state->count == 1) {
        caps_word_on();            // Single tap for Caps Word mode
    } else if (state->count == 2) {
        tap_code(KC_ESC);          // Double tap for ESC
    }
}

// Tap Dance CAPS deactivation logic
void dance_caps_reset(tap_dance_state_t *state, void *user_data) {
    if (! state->pressed) {
        unregister_code(KC_CAPS);  // Release Caps Lock if it was held
    } /* else {
        caps_word_off();           // Deactivate Caps Word mode
    } */
}

// Tap Dance callback for left Alt key
void dance_lalt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_LALT);  // If held, sends Alt key
    } else if (state->count == 1) {
        tap_code16(S(KC_8));     // 1 Tap: '('
    } else if (state->count == 2) {
        tap_code16(RALT(KC_F));  // 2 Tap: '['
    } else if (state->count == 3) {
        tap_code16(RALT(KC_B));  // 3 Tap: '{'
    }
}

// Tap Dance reset callback for left Alt key
void dance_lalt_reset(tap_dance_state_t *state, void *user_data) {
    if (! state->pressed) {
        unregister_code(KC_LALT);  // Release Alt on key release if it was held
    }
}

// Tap Dance callback for right AltGr key
void dance_ralt_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_RALT);  // If held, sends AltGr key
    } else if (state->count == 1) {
        tap_code16(S(KC_9));     // 1 Tap: ')'
    } else if (state->count == 2) {
        tap_code16(RALT(KC_G));  // 2 Tap: ']'
    } else if (state->count == 3) {
        tap_code16(RALT(KC_N));  // 3 Tap: '}'
    }
}

// Tap Dance reset callback for right AltGr key
void dance_ralt_reset(tap_dance_state_t *state, void *user_data) {
    if (! state->pressed) {
        unregister_code(KC_RALT);  // Release AltGr on key release if it was held
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
    TD_LALT,  // Left Alt for opening brackets
    TD_RALT,  // AltGr for closing brackets
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

    [TD_1_F1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_1_f1_finished, dance_1_reset),
    [TD_2_F2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_f2_finished, dance_2_reset),
    [TD_3_F3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_f3_finished, dance_3_reset),
    [TD_4_F4] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_4_f4_finished, dance_4_reset),
    [TD_5_F5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_f5_finished, dance_5_reset),
    [TD_6_F6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_6_f6_finished, dance_6_reset),
    [TD_7_F7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_7_f7_finished, dance_7_reset),
    [TD_8_F8] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_8_f8_finished, dance_8_reset),
    [TD_9_F9] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_9_f9_finished, dance_9_reset),
    [TD_0_F10] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_g_f10_finished, dance_g_reset),
    [TD_0_F11] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_f11_finished, dance_0_f11_reset),
    [TD_M_F12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_m_f12_finished, dance_m_f12_reset),

    [TD_LALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lalt_finished, dance_lalt_reset),
    [TD_RALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ralt_finished, dance_ralt_reset),
};

#define CAPS_ESC TD(TD_CAPS_ESC)
#define ENT_KEYP LT(KEYPAD, KC_ENT)  // Switched back to LT, because layer order is now correct

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
                    // Signal: 1x blink SCROLL LED
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
                    // Signal: 1x blink NUM LED
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
                    // Signal: 3x fast blink CAPS LED
                    for (int i = 0; i < 3; i++) {
                        writePinLow(SCROLL_LOCK_LED_PIN); wait_ms(100);
                        writePinHigh(SCROLL_LOCK_LED_PIN); wait_ms(100);
                    }
                } else {
                    uprintf("Debug mode DISABLED\n");
                    // Signal: 1x long blink CAPS LED
                    writePinLow(SCROLL_LOCK_LED_PIN); wait_ms(500); writePinHigh(SCROLL_LOCK_LED_PIN);
                }
            }
            return false;

        case RALT(S(KC_J)): // AltGr+Shift+J = Í (capital Í) - in all cases
            if (record->event.pressed) {
                tap_code16(RALT(KC_I)); // Always sends capital Í
            }
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

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
    KC_LCTL,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                                                                      KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_EQL,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LSFT,  /*KC_LALT*/ALT_OPEN,                                               KC_RGUI,  /*KC_RALT*/ALT_CLSE,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  /*KC_ENTER*/ENT_KEYP, KC_SPC
  ),

  [COLEMAKDH_HUN] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TO_KEYPAD,TOGGLE_LAYOUT,
    TD(TD_0_F10), TD(TD_1_F1),  TD(TD_2_F2),  TD(TD_3_F3),  TD(TD_4_F4),  TD(TD_5_F5),                                                                   TD(TD_6_F6),  TD(TD_7_F7),  TD(TD_8_F8),  TD(TD_9_F9),  TD(TD_0_F11), TD(TD_M_F12),
    KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,                                                                      KC_J,     KC_L,     KC_U,     KC_Z,     KC_SCLN,  KC_BSLS,
    CAPS_ESC, KC_A,     KC_R,     KC_S,     KC_T,     KC_G,                                                                      KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,
    KC_LCTL,  KC_Y,     KC_X,     KC_C,     KC_D,     KC_V,                                                                      KC_K,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_EQL,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LSFT,  /*KC_LALT*/ALT_OPEN,                                               KC_RGUI,  /*KC_RALT*/ALT_CLSE,
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
    // STARTUP SIGNAL: 3x blink all LEDs
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
        // Only write if the layer actually changed
        static uint8_t last_layer = 255;
        uint8_t current_layer = get_highest_layer(state);
        if (current_layer != last_layer) {
            uprintf("Layer changed: %d -> %d (state: %08lX)\n", last_layer, current_layer, state);
            last_layer = current_layer;
        }
    }
    // KEYPAD LED handling
    if (layer_state_cmp(state, KEYPAD)) {  // If KEYPAD layer is active
        writePinLow(KEYPAD_LED_PIN); // Turn on KEYPAD_LED
    } else { // If KEYPAD layer is not active
        writePinHigh(KEYPAD_LED_PIN); // Turn off KEYPAD_LED
    }    // Check for Caps Word state and toggle Caps Lock LED (blinking feedback)
    if (is_caps_word_on()) {
        // Caps Word is active, toggle Caps Lock LED
        if (timer_elapsed(caps_lock_led_timer) > 100) { // 100ms
            caps_lock_led_timer = timer_read();
            caps_lock_led_state = !caps_lock_led_state;
            if (caps_lock_led_state) {
                writePinLow(CAPS_LOCK_LED_PIN); // Turn on CAPS_LOCK_LED for 30ms
                // timer_set(caps_lock_led_timer, 30); // Set timer for 30ms
                // Use timer_read function instead
                caps_lock_led_timer = timer_read() + 30;
            } else {
                writePinHigh(CAPS_LOCK_LED_PIN); // Turn off CAPS_LOCK_LED for 70ms
                // timer_set(caps_lock_led_timer, 70); // Set timer for 70ms
                // Use timer_read function instead
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

// Per-key tapping term configuration
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Number keys with faster reaction time (for fast typing)
        case TD(TD_1_F1):
        case TD(TD_2_F2):
        case TD(TD_3_F3):
        case TD(TD_4_F4):
        case TD(TD_5_F5):
        case TD(TD_6_F6):
        case TD(TD_7_F7):
        case TD(TD_8_F8):
        case TD(TD_9_F9):
        case TD(TD_0_F10):
        case TD(TD_0_F11):
            return 250;  // Slower to make tap&hold easier to trigger

        // CAPS/ESC with normal reaction time
        case TD(TD_CAPS_ESC):
            return 200;  // Slightly slower to avoid accidental caps word

        // Alt keys with slower reaction time (due to complex functions)
        case TD(TD_LALT):
        case TD(TD_RALT):
            return 250;  // Slower for bracket functions

        // All others use default
        default:
            return TAPPING_TERM;
    }
}

// Per-key quick tap term configuration
// If you press the SAME key again within this time, it will always be tap (not hold)
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // For number keys, rapid successive presses = tap (for fast typing: 111, 222 etc.)
        case TD(TD_1_F1):
        case TD(TD_2_F2):
        case TD(TD_3_F3):
        case TD(TD_4_F4):
        case TD(TD_5_F5):
        case TD(TD_6_F6):
        case TD(TD_7_F7):
        case TD(TD_8_F8):
        case TD(TD_9_F9):
        case TD(TD_0_F10):
        case TD(TD_0_F11):
        case TD(TD_M_F12):
        case KC_ENT:
            return 200;  // Same key within 200ms = always tap

        // No quick tap for all other keys
        default:
            return 0;  // 0 = disabled
    }
}

// Caps Word customization - support for Hungarian accented characters
bool caps_word_press_user(uint16_t keycode) {
    if (debug_enabled) {
        uprintf("Caps Word keycode: 0x%04X\n", keycode);
    }

    switch (keycode) {
        // KC_UNDS doesn't exist on Hungarian keyboard as a base key
        // The underscore is KC_MINS with Shift modifier
        // Since Caps Word needs to continue on underscore, handle
        case KC_SLSH:  // On Hungarian keyboard, underscore key (Shift + -), left of right_shift
            // Not at all. -/_ are the same button, let shift decide. add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        // Dedicated keys for Hungarian accented characters (Hungarian QWERTZ layout)
        case KC_QUOT:       // á/Á (á is at ' position)
        case KC_SCLN:       // é/É (é is at ; position)
        case KC_EQL:        // ó/Ó (ó is at = position)
        case KC_0:          // ö/Ö (ö is at 0 position)
        case KC_LBRC:       // ő/Ő (ő is at [ position)
        case KC_RBRC:       // ú/Ú (ú is at ] position)
        case KC_MINS:       // ü/Ü (ü is at - position)
        case KC_BSLS:       // ű/Ű (ű is at \ position)
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Special handling for í/Í characters
        case RALT(KC_J):    // AltGr+J = í (lowercase í) - needs to be converted to capital Í in Caps Word
            // send AltGr+I instead of AltGr+J (capital Í)
            tap_code16(RALT(KC_I));
            return true; // Caps Word remains active

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_9:
        case KC_BSPC:
        case KC_DEL:
        case KC_LSFT:
        case KC_RSFT:
        case KC_ENT:
        case KC_RALT:       // Right Alt (AltGr on Hungarian layout)
        case RALT(KC_I):    // AltGr+I = Í (capital Í) - in all cases
            return true;    // Caps Word remains active, no shift needed

        default:
            if (debug_enabled) {
                uprintf("Caps Word deactivated by keycode: 0x%04X\n", keycode);
            }
            return false;  // Deactivate Caps Word.
    }
}

// Caps Word state change detection (debug only, LED handling in layer_state_set_user)
void caps_word_set_user(bool active) {
    if (debug_enabled) {
        uprintf("Caps Word %s\n", active ? "ACTIVATED" : "DEACTIVATED");
    }
    // LED handling happens in layer_state_set_user function (blinking feedback)
}
