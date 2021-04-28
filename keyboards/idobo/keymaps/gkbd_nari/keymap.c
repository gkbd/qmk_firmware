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

uint16_t predecessor_key = KC_NO;
uint16_t left_adaptive_key = KC_NO;
uint16_t right_adaptive_key = KC_NO;

enum custom_keycodes {
    AN = SAFE_RANGE,
    IR,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == AN) {
		
        if (record->event.pressed) {

			if (predecessor_key == KC_DOT) {
				keycode = KC_SPC;
			}
			else if (predecessor_key == KC_E) {
				keycode = KC_N;
			}
			else {
				keycode = KC_A;
			}
				
			register_code(keycode);
			left_adaptive_key = keycode;
		}
		else {
			unregister_code(left_adaptive_key);
		}
	}
    else if (keycode == IR) {
		
        if (record->event.pressed) {

			if (predecessor_key == KC_COMM) {
				keycode = KC_SPC;
			}
			else if (predecessor_key == KC_E) {
				keycode = KC_R;
			}
			else {
				keycode = KC_I;
			}
				
			register_code(keycode);
			right_adaptive_key = keycode;
		}
		else {
			unregister_code(right_adaptive_key);
		}
	}

	if (KC_A <= (keycode) && (keycode) <= KC_SLASH && record->event.pressed) {
		if(keycode == KC_A || keycode == KC_O || keycode == KC_I || keycode == KC_U) {
			predecessor_key = KC_E;
		}
		else {
			predecessor_key = keycode;
		}
	}

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x15(/* Base */
			KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_BSLS, KC_SLSH, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
			KC_TAB, KC_X, KC_Y, KC_U, KC_N, KC_B, KC_QUOT, KC_SCLN, KC_M, KC_R, KC_P, KC_F, KC_Q, KC_LBRC, KC_RBRC,
			KC_CAPS, KC_C, KC_O, KC_E, AN, KC_H, KC_SLCK, KC_PAUS, KC_L, IR, KC_T, KC_S, KC_D, KC_ENT, KC_GRV,
			KC_PGUP, KC_Z, KC_V, KC_W, KC_A, KC_COMM, KC_LGUI, KC_RALT, KC_DOT, KC_I, KC_G, KC_K, KC_J, KC_UP, KC_APP,
			KC_PGDN, KC_PSCR, KC_INS, KC_DEL, MO(1), KC_BSPC, OSM(MOD_LSFT), KC_RCTL, KC_SPC, MO(1), KC_HOME, KC_END, KC_LEFT, KC_DOWN, KC_RGHT
		),
	[1] = LAYOUT_ortho_5x15(/* Function keys */
			RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_F11, KC_TRNS, KC_TRNS, KC_F12, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
		)
};
