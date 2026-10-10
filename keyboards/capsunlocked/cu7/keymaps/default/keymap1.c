/*
Copyright 2021 CapsUnlocked

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
#include QMK_KEYBOARD_H

enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
        MO(1),
    KC_BSPC,KC_UP,KC_DEL,
    KC_LEFT,KC_DOWN,KC_RGHT
  ),
  [1] = LAYOUT(
            KC_TRNS,
      RGB_TOG,RGB_VAI,RGB_MOD,
      RGB_SAI,RGB_VAD,RGB_RMOD
  ),
};

// Volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (clockwise) {
        if (layer_state_is(1)) {
            tap_code16(KC_DOWN);
        } else {
            tap_code16(KC_RIGHT);
        }
    } else {
        if (layer_state_is(1)) {
            tap_code16(KC_UP);
        } else {
           tap_code16(KC_LEFT);
        }
    }

  return true;
};

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};


void on_dance_0(tap_dance_state_t *state, void *user_data);
uint8_t dance_0_dance_step(tap_dance_state_t *state);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
    }
    if(state->count > 3) {
        tap_code16(KC_ENT);
    }
}

uint8_t dance_0_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_0_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ENT); break;
        case DOUBLE_TAP: register_code16(KC_ENT); break;
        case DOUBLE_HOLD: layer_move(1); layer_off(0); rgblight_disable(); wait_ms(200); rgblight_enable(); wait_ms(200);rgblight_disable(); wait_ms(200); rgblight_enable();  wait_ms(200); rgblight_disable(); wait_ms(200); rgblight_enable(); break;
        case SINGLE_HOLD: tap_code16(KC_ESCAPE); break;
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ENT); break;
        case DOUBLE_TAP: unregister_code16(KC_ENT); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state.step = 0;
}

void on_dance_1(tap_dance_state_t *state, void *user_data);
uint8_t dance_1_dance_step(tap_dance_state_t *state);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
   /*  if(state->count == 3) {
        tap_code16(RGB_M_P);
        tap_code16(RGB_M_P);
        tap_code16(RGB_M_P);
    }
    if(state->count > 3) {
        tap_code16(RGB_M_P);
    } */
}

uint8_t dance_1_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_1_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD:  reset_keyboard(); break;
        case SINGLE_HOLD:  break;
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: break;
    }
    dance_state.step = 0;
}

void on_dance_2(tap_dance_state_t *state, void *user_data);
uint8_t dance_2_dance_step(tap_dance_state_t *state);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
   /*  if(state->count == 3) {
        tap_code16(RGB_HUI);
        tap_code16(RGB_HUI);
        tap_code16(RGB_HUI);
    }
    if(state->count > 3) {
        tap_code16(RGB_HUI);
    } */
}


uint8_t dance_2_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_2_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: layer_move(0); layer_off(1); rgblight_disable(); wait_ms(200); rgblight_enable(); wait_ms(200);rgblight_disable(); wait_ms(200); rgblight_enable(); break;
        case SINGLE_HOLD: register_code16(KC_LSFT); break;
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: break;
        case SINGLE_HOLD: unregister_code16(KC_LSFT); break;
    }
    dance_state.step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
};
