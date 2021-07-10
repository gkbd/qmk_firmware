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

#define HORNY(code) (KC_A <= (code) && (code) <= KC_Z && code != KC_T && code != KC_S && code != KC_C && code != KC_P && code != KC_G && code != KC_W && code != KC_X)

uint16_t predecessor_key = KC_NO;
uint16_t adaptive_key = KC_NO;

static uint16_t horn_proximity;

enum custom_keycodes {
    HN = SAFE_RANGE,
};

bool horny(void) {
	return predecessor_key == KC_A && timer_elapsed(horn_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == HN) {
		
        if (record->event.pressed) {

			keycode = horny()?KC_N:KC_H;	
			register_code(keycode);
			adaptive_key = keycode;

		}
		else {
			unregister_code(adaptive_key);
		}
	}

	if (!IS_MOD(keycode) && record->event.pressed) {
		if(HORNY(keycode) || keycode == RSFT_T(KC_H)) {
			predecessor_key = KC_A;
			horn_proximity = timer_read();
		}
		else {
			predecessor_key = keycode;
		}
	}

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x15(/* Base */
			KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LBRC, KC_APP, KC_RBRC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
			KC_QUOT, KC_J, KC_X, KC_U, KC_F, KC_W, KC_LCBR, KC_PSCR, KC_RCBR, KC_G, KC_M, KC_P, KC_N, KC_Q, KC_MINS,
			KC_ESC, KC_R, KC_O, KC_E, HN, KC_L, KC_LPRN, MO(1), KC_RPRN, KC_C, KC_T, KC_I, KC_S, KC_D, KC_ENT,
			KC_TAB, KC_SCLN, KC_Z, KC_Y, KC_COMM, KC_DOT, KC_SLSH, KC_LGUI, KC_BSLS, KC_K, KC_V, KC_B, RSFT_T(KC_H), KC_UP, KC_INS,
			KC_CAPS, KC_HOME, KC_END, KC_DEL, KC_BSPC, KC_A, KC_LSFT, KC_RCTL, KC_RALT, KC_SPC, KC_PGDN, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT
		),
	[1] = LAYOUT_ortho_5x15(/* Function keys */
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_SLCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_TRNS, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PAUS,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG
		)
};
