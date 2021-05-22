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

#define MIN_PROXIMITY 800

uint16_t predecessor_key = KC_NO;
uint16_t adaptive_key = KC_NO;

static uint16_t vowel_proximity;

enum custom_keycodes {
    EN = SAFE_RANGE,
};

bool promote_consonants(void) {
	return predecessor_key == KC_E && timer_elapsed(vowel_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == EN) {
		
        if (record->event.pressed) {

			keycode = promote_consonants()?KC_N:KC_E;	
			register_code(keycode);
			adaptive_key = keycode;

		}
		else {
			unregister_code(adaptive_key);
		}
	}

	if (KC_A <= (keycode) && (keycode) <= KC_SLASH && record->event.pressed) {
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
			KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_BSLS, KC_SLSH, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_GRV,
			KC_TAB, KC_COMM, KC_DOT, KC_U, KC_G, KC_Y, KC_LBRC, KC_RBRC, KC_W, KC_M, KC_P, KC_B, KC_MINS, KC_SCLN, KC_PSCR,
			KC_CAPS, KC_H, KC_R, KC_A, KC_O, KC_L, KC_SLCK, KC_PAUS, KC_C, KC_T, KC_I, KC_S, KC_D, KC_ENT, KC_HOME,
			KC_PGUP, KC_J, KC_QUOT, KC_F, KC_E, KC_X, KC_LGUI, KC_RALT, KC_V, KC_N, KC_K, KC_Q, KC_Z, KC_UP, KC_END,
			KC_PGDN, KC_WAKE, MO(1), KC_INS, KC_DEL, EN, OSM(MOD_LSFT), KC_RCTL, KC_SPC, KC_BSPC, KC_APP, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
		),
	[1] = LAYOUT_ortho_5x15(/* Function keys */
			RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_F11, KC_TRNS, KC_TRNS, KC_F12, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO
		)
};
