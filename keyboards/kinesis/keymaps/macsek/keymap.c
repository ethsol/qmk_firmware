// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum/caps_word.h"

#define QWERTY 0 // Base qwerty
#define KEYPAD 1

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

#define ALT_OPEN TD(TD_LALT)
#define ALT_CLSE TD(TD_RALT)


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
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,         KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_SCRL,  KC_PAUS,  TO(KEYPAD),XXXXXXX,
    TD(TD_0_F10), TD(TD_1_F1),  TD(TD_2_F2),  TD(TD_3_F3),  TD(TD_4_F4),  TD(TD_5_F5),                                                                   TD(TD_6_F6),  TD(TD_7_F7),  TD(TD_8_F8),  TD(TD_9_F9),  TD(TD_0_F11), TD(TD_M_F12),
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                                                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSLS,
    CAPS_ESC, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                                                                      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                                                      KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
              KC_EQL,   KC_INS,   KC_LEFT,  KC_RGHT,                                                                                       KC_UP,    KC_DOWN,  KC_LBRC,  KC_RBRC,
                                                      KC_LCTL,  /*KC_LALT*/ALT_OPEN,                                               KC_RGUI,  /*KC_RALT*/ALT_CLSE,
                                                                KC_HOME,                                               KC_PGUP,
                                            KC_BSPC,  KC_DEL,   KC_END,                                                KC_PGDN,  KC_ENTER, KC_SPC
  ),

   [KEYPAD] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, TO(QWERTY), QK_BOOT,
    CK_TOGG, CK_ON,   CK_OFF,  CK_UP,   CK_DOWN, CK_RST,                                                                  _______, KC_NUM,  KC_PEQL, KC_PSLS, KC_PAST,  _______,
    _______, _______, _______, _______, _______, _______,                                                                 _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS,  _______,
    _______, _______, _______, _______, _______, _______,                                                                 _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,  _______,
    _______, _______, _______, _______, _______, _______,                                                                 _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,  _______,
             _______, _______, _______, _______,                                                                                   _______, _______, KC_PDOT, KC_PENT,
                                                 _______, _______,                                               KC_APP,  KC_RCTL,
                                                          _______,                                               _______,
                                        _______, _______, _______,                                               _______, _______, KC_KP_0
  )


};
