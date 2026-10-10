/* Copyright 2020 Snipeye
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_us_international.h"
#include <process_tap_dance.h>

enum tap_dance_codes
{
  UNO
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

#define DEFAULTU "admin"
#define DEFAULT1 "VMwar3!!"
#define DEFAULT2 "VMwar3123_"
#define UID "nw85887"
#define PWD "Extinct-Fool-Armrest"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
           TD(UNO)
          )
};

void on_uno(tap_dance_state_t *state, void *user_data);
uint8_t uno_step(tap_dance_state_t *state);
void uno_finished(tap_dance_state_t *state, void *user_data);
void uno_reset(tap_dance_state_t *state, void *user_data);

void on_uno(tap_dance_state_t *state, void *user_data) {}

td_state_t uno_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


void uno_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = uno_step(state);
    switch (dance_state.step) {
        case TD_SINGLE_TAP: SEND_STRING(DEFAULT1); break;
        case TD_SINGLE_HOLD: SEND_STRING(DEFAULTU);register_code16(KC_TAB);SEND_STRING(DEFAULT1); break;
        case TD_DOUBLE_TAP: SEND_STRING(DEFAULT2); break;
        case TD_DOUBLE_HOLD:  SEND_STRING(DEFAULTU);register_code16(KC_TAB); SEND_STRING
        (DEFAULT2); break;
        // case TD_TRIPLE_TAP: SEND_STRING(UID); break;
        case TD_TRIPLE_HOLD:  SEND_STRING(UID);register_code16(KC_TAB); SEND_STRING(PWD);break;
        default: break;
    }
}

void uno_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(15);
    switch (dance_state.step) {
        case TD_SINGLE_TAP: break;
        case TD_DOUBLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_SINGLE_HOLD: unregister_code16(KC_TAB); break;
        case TD_DOUBLE_HOLD: unregister_code16(KC_TAB); break;
        case TD_TRIPLE_HOLD: unregister_code16(KC_TAB); break;
        default: break;
    }
    dance_state.step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [UNO] = ACTION_TAP_DANCE_FN_ADVANCED(on_uno, uno_finished, uno_reset),
};
