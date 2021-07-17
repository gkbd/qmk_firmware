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

#define PRENASAL(code) (KC_A <= (code) && (code) <= KC_Z && code != KC_T && code != KC_S && code != KC_C && code != KC_P && code != KC_G && code != KC_W && code != KC_X)

uint16_t last_vowel = KC_NO;
uint16_t last_prenasal = KC_NO;

uint16_t left_adaptive_key = KC_NO;
uint16_t right_adaptive_key = KC_NO;

static uint16_t prenasal_proximity;
static uint16_t vowel_proximity;

enum custom_keycodes {
    HM = SAFE_RANGE,
    ON,
};

bool prenasal(void) {
	return last_prenasal == KC_O && timer_elapsed(prenasal_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG);
};

bool postvowel(void) {
	return last_vowel == KC_O && timer_elapsed(vowel_proximity) < MIN_PROXIMITY && !(get_mods() & ~MOD_MASK_SHIFT & MOD_MASK_CAG);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == HM) {
		
        if (record->event.pressed) {

			keycode = prenasal()?KC_M:KC_H;
			register_code(keycode);
			left_adaptive_key = keycode;

		}
		else {
			unregister_code(left_adaptive_key);
		}
	}

    if (keycode == ON) {
		
        if (record->event.pressed) {

			keycode = postvowel()?KC_N:KC_O;	
			register_code(keycode);
			right_adaptive_key = keycode;

		}
		else {
			unregister_code(right_adaptive_key);
		}
	}

	if (!IS_MOD(keycode) && keycode != OSM(MOD_LSFT) && record->event.pressed) {
		
		last_vowel = keycode;
		last_prenasal = keycode;

		if(PRENASAL(keycode)) {
			last_prenasal = KC_O;
			prenasal_proximity = timer_read();
		}

		if(keycode == KC_E || keycode == KC_A || keycode == KC_O || keycode == KC_I || keycode == KC_U) {
			last_vowel = KC_O;
			vowel_proximity = timer_read();
		}
	}

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x15(/* Base */
			KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LBRC, KC_APP, KC_RBRC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
			KC_GRV, KC_COMM, KC_J, KC_B, KC_W, KC_Y, KC_LCBR, KC_PSCR, KC_RCBR, KC_G, KC_P, KC_V, KC_N, KC_SCLN, KC_MINS,
			KC_TAB, KC_F, HM, ON, KC_E, KC_U, LCTL(KC_BSPC), MO(1), KC_BSPC, KC_D, KC_T, KC_SPC, KC_S, KC_C, KC_HOME,
			KC_PGUP, KC_DOT, KC_Z, KC_X, KC_O, KC_QUOT, KC_SLSH, KC_LGUI, KC_BSLS, KC_K, KC_M, KC_Q, KC_H, KC_UP, KC_END,
			KC_PGDN, KC_CAPS, KC_INS, KC_DEL, KC_I, KC_A, OSM(MOD_LSFT), KC_RCTL, KC_RALT, KC_R, KC_L, KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT
		),
	[1] = LAYOUT_ortho_5x15(/* Function keys */
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			KC_SLCK, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_TRNS, KC_NO, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_PAUS,
			KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
			RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG
		)
};

