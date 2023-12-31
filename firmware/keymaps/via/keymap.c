// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

enum layers {
  _COLEMAK,
  _SYM,
  _NUM,
  _FUN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬──────┐
      * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ BSPC │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼──────┤
      * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │   P  │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼──────┤
      * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │   /  │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴──────┘
      *        ┌────┐                           ┌─────┐
      *        │CTRL├─────┐               ┌─────┤ ESC │
      *        └────┤ ALT ├─────┐   ┌─────┤ ENT ├─────┘
      *             └─────┤ TAB │   │ SPC ├─────┘
      *                   └─────┘   └─────┘
      */
    [0] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W, KC_F,    KC_P,    KC_G,           KC_J,          KC_L,          KC_U,     KC_Y,   LT(_NUM, KC_BACKSPACE),
        KC_A,         KC_R, KC_S,    KC_T,    KC_D,           KC_H,          KC_N,          KC_E,     KC_I,   KC_O,
        LSFT_T(KC_Z), KC_X, KC_C,    KC_V,    KC_B,           KC_K,          KC_M,          KC_COMMA, KC_DOT, RSFT_T(KC_SLSH),
                            LGUI_T(KC_CAPS), KC_LALT, LT(_NUM, KC_TAB),LGUI_T(KC_SPC), LT(_SYM, KC_ENT), RCTL_T(KC_ESC)
    ),
    [1] = LAYOUT_split_3x5_3(
        KC_UNDS,         KC_MINS, KC_PLUS, KC_EQL,  KC_COLN, KC_GRV,   KC_MRWD, KC_MPLY, KC_MFFD, KC_DEL,
        KC_LCBR,         KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, KC_ESC,   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,
        LSFT_T(KC_LBRC), KC_QUOT, KC_DQUO, KC_RBRC, KC_SCLN, KC_TILDE, KC_VOLD, KC_MUTE, KC_VOLU, RSFT_T(KC_BSLS),
                                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
    ),
    [2] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_ASTR,                   KC_CAPS, KC_BSPC,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,                      KC_9,    KC_0,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   MO(_FUN),          MO(_FUN),   KC_NO,   KC_COMM,                   KC_DOT,  RSFT_T(KC_SLSH),
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
    ),
    [3] = LAYOUT_split_3x5_3(
         KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_NO,
         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10,
         KC_F11,  KC_NO, KC_NO,   QK_BOOT, KC_TRNS, KC_NO,   QK_BOOT,   KC_NO,  KC_NO, KC_F12,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
};