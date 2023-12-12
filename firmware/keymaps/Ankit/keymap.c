// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include "action.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK,
    _SYM,
    _NUM,
    _FUN,
    _QWERTY,
};

typedef struct {
    bool is_pressed_action;
    int  state;
} tap;

// tap states
typedef enum {
    SINGLE_TAP        = 1,
    SINGLE_HOLD       = 2,
    DOUBLE_TAP        = 3,
    DOUBLE_HOLD       = 4,
    DOUBLE_SINGLE_TAP = 5, // send two single taps
    TRIPLE_TAP        = 6,
    TRIPLE_HOLD       = 7,
} x_td_state;

// tap dance declarations
enum {
    X_CTL,
    SOME_OTHER_DANCE,
};

x_td_state curr_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        if (state->pressed) return DOUBLE_HOLD;
        return DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TRIPLE_TAP;
        else
            return TRIPLE_HOLD;
    }
    return 8;
}

static tap x_tap_state = {
    .is_pressed_action = true,
    .state             = 0,
};

void x_finished(tap_dance_state_t *state, void *user_data) {
    x_tap_state.state = curr_dance(state);
    switch (x_tap_state.state) {
        case SINGLE_TAP:
            register_code(KC_X);
            break;
        case SINGLE_HOLD:
            register_code(KC_LCTL);
            break;
        case DOUBLE_TAP:
            register_code(KC_ESC);
            break;
        case DOUBLE_HOLD:
            register_code(KC_LEFT_ALT);
            break;
        case DOUBLE_SINGLE_TAP:
            register_code(KC_X);
            unregister_code(KC_X);
            register_code(KC_X);
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (x_tap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_X);
            break;
        case SINGLE_HOLD:
            unregister_code(KC_LEFT_CTRL);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_ESC);
            break;
        case DOUBLE_HOLD:
            unregister_code(KC_LEFT_ALT);
            break;
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_X);
    }
    x_tap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
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
        KC_Q,         KC_W, KC_F,    KC_P,    KC_G,           KC_J,          KC_L,          KC_U,     KC_Y,   KC_BSPC,
        KC_A,         KC_R, KC_S,    KC_T,    KC_D,           KC_H,          KC_N,          KC_E,     KC_I,   KC_O,
        LSFT_T(KC_Z), TD(X_CTL), KC_C,    KC_V,    KC_B,           KC_K,          KC_M,          KC_COMMA, KC_DOT, RSFT_T(KC_SLSH),
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
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   MO(_FUN),          KC_NO,   KC_NO,   KC_COMM,                   KC_DOT,  RSFT_T(KC_SLSH),
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
    ),
    [3] = LAYOUT_split_3x5_3(
         KC_NO,   KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_NO,
         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10,
         KC_F11,  DF(_QWERTY), DF(_COLEMAK),   QK_BOOT, KC_TRNS, KC_NO,   KC_NO,   KC_NO,  KC_NO, KC_F12,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
     ),
     [4] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W, KC_E,    KC_R,    KC_T,           KC_Y,          KC_U,          KC_I,     KC_O,   KC_P,
        KC_A,         KC_S, KC_D,    KC_F,    KC_G,           KC_H,          KC_J,          KC_K,     KC_L,   KC_BSPC,
        LSFT_T(KC_Z), KC_X, KC_C,    KC_V,    KC_B,           KC_N,          KC_M,          KC_COMMA, KC_DOT, RSFT_T(KC_SLSH),
                            LGUI_T(KC_CAPS), KC_LALT, LT(_NUM, KC_TAB),LGUI_T(KC_SPC), LT(_SYM, KC_ENT), RCTL_T(KC_ESC)
    ),
};
