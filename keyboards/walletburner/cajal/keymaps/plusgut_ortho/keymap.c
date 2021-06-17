/* Copyright 2020 Worldspawn <mcmancuso@gmail.com>
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
#include "keymap_extras/keymap_german.h"

enum plaid_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

#define LOWER LT(_LOWER,KC_SPC)
#define RAISE MO(_RAISE)
#define ADJUS MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_ortho(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, _______, RGB_TOG,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    DE_SCLN, KC_ENT,  _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    DE_COMM, DE_DOT,  DE_SLSH, _______, _______,
        _______, _______, KC_LALT, RAISE,   LOWER,   KC_LSFT, KC_LSFT, KC_LCTL, KC_RGUI, _______, _______, _______, _______, _______
    ),

    [_LOWER] = LAYOUT_ortho(
        _______, DE_AT,   DE_PIPE, DE_EURO, DE_UNDS, DE_TILD, DE_AMPR, DE_UE,   DE_PERC, DE_OE,   DE_CIRC, KC_DEL,  _______, _______,
        _______, DE_AE,   DE_SS,   DE_QST,  DE_DQUO, DE_EQL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, DE_COLN, DE_ASTR, _______,
        _______, DE_QUES, DE_EXLM, DE_DLR,  DE_GRV,  DE_QUOT, _______, DE_PLUS, DE_MINS, DE_HASH, DE_BSLS, DE_ACUT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_RAISE] = LAYOUT_ortho(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  _______, _______,
        _______, DE_LESS, DE_LBRC, DE_LCBR, DE_LPRN, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______, _______,
        _______, DE_MORE, DE_RBRC, DE_RCBR, DE_RPRN, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, ADJUS,   _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_ortho(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};


layer_state_t layer_state_set_user(layer_state_t state) {
    writePinLow(B7);
    writePinLow(B6);
    switch (get_highest_layer(state)) {
        case _LOWER:
            writePinHigh(B7);
            break;
        case _RAISE:
            writePinHigh(B6);
            break;
        case _ADJUST:
            writePinHigh(B7);
            writePinHigh(B6);
            break;
    }
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(B5, led_state.caps_lock);
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    return true;
}
