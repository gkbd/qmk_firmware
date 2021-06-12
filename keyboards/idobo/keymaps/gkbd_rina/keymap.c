/* Copyright 2021 Giorgi Chavchanidze
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

#define MIN_PROXIMITY 8000

uint16_t predecessor_key = KC_NO;
uint16_t left_adaptive_key = KC_NO;
uint16_t right_adaptive_key = KC_NO;

static uint16_t vowel_proximity;

enum custom_keycodes {
    AN = SAFE_RANGE,
    IR,
};

bool promote_consonants(void) {
	return predecessor_key == KC_E && timer_elapsed(vowel_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == AN) {
		
        if (record->event.pressed) {

			keycode = promote_consonants()?KC_N:KC_A;
			register_code(keycode);
			right_adaptive_key = keycode;

		}
		else {
			unregister_code(right_adaptive_key);
		}
	}
    else if (keycode == IR) {
		
        if (record->event.pressed) {

			keycode = promote_consonants()?KC_R:KC_I;
			register_code(keycode);
			left_adaptive_key = keycode;

		}
		else {
			unregister_code(left_adaptive_key);
		}
	}

	if (IS_KEY(keycode) && record->event.pressed) {
		if(keycode == KC_E || keycode == KC_A || keycode == KC_O || keycode == KC_I || keycode == KC_U) {
			predecessor_key = KC_E;
			vowel_proximity = timer_read();
		}
		else {
			predecessor_key = keycode;
		}
	}

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x15(/* Base */
			KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LBRC, KC_WAKE, KC_RBRC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
			KC_TAB, KC_K, KC_N, KC_M, KC_P, KC_G, KC_BSLS, KC_APP, KC_SLSH, KC_W, KC_R, KC_BSPC, KC_COMM, KC_DOT, KC_MINS,
			KC_ENT, KC_D, KC_S, KC_SPC, KC_T, KC_C, KC_GRV, KC_LGUI, KC_SCLN, KC_U, KC_O, KC_E, KC_L, KC_H, KC_QUOT,
			KC_PGUP, KC_Q, KC_J, KC_I, KC_B, KC_V, MO(1), KC_RALT, MO(1), KC_A, KC_Y, KC_F, KC_X, KC_Z, KC_HOME,
			KC_PGDN, KC_CAPS, KC_PSCR, KC_INS, KC_DEL, IR, KC_LSFT, KC_RCTL, KC_RSFT, AN, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END
		),
	[1] = LAYOUT_ortho_5x15(/* Function keys */
			RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_SLCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_TRNS, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PAUS,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
		)
};
