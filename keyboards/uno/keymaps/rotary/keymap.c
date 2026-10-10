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

enum uno_keycode
{
  UNO = SAFE_RANGE
};

static uint16_t pressTimer = 0xFFFF;
#define CUSTOM_LONGPRESS 1000
#define DEFAULT1 "nw85887"
#define CUSTOM_LONGERPRESS 3000
#define CUSTOM_STRING "Extinct-Fool-Armrest"
#define CUSTOM_LONGESTPRESS 5000

enum encoder_names {
	_ENCODER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
            UNO
          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
    case UNO:
        if (record->event.pressed) {
            pressTimer = timer_read();
        } else {
            uint16_t timeElapsed = timer_elapsed(pressTimer);

            if (timeElapsed < CUSTOM_LONGPRESS){
                tap_code16(KC_ENT);
            } else if (timeElapsed < CUSTOM_LONGERPRESS) {
                SEND_STRING(DEFAULT1); tap_code16(KC_TAB);
            } else if (timeElapsed < CUSTOM_LONGESTPRESS) {
                SEND_STRING(CUSTOM_STRING);
            } else {
                reset_keyboard();
            }
        break;
        }
    }
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _ENCODER) { /* First encoder */
        if (clockwise) {
            tap_code16(S(C(KC_Z)));
        } else {
            tap_code16(A(G(KC_V)));
        }
		return false;
    }
	return true;
}
