// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ENT,
        C(KC_A), C(KC_DEL), C(KC_S),
        C(KC_END),  S(KC_TAB), C(KC_HOME)
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(C(S(A(KC_V))), C(S(KC_V))) },
};
#endif
