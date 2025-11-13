/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"


#define ESC_SHT SFT_T(KC_ESC)
#define CLN_SHT SFT_T(KC_SCLN)
#define ENT_CTL MT(MOD_LCTL, KC_ENT)
#define BSPC_LT2 LT(2, KC_BSPC)
#define SPC_LT1 LT(1, KC_SPC)
#define L_LT3 LT(3, KC_L)
#define TAB_LT3 LT(3, KC_TAB)

#define SCRN_SHT LSFT(LGUI(KC_S))
#define WIN_SEC LCTL(LALT(KC_DEL))
#define CH_LANG LSFT(KC_SPC)

// Tap Dance declarations
enum {
    TD_Q_ESC,
};
tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
};
#define Q_ESC TD(TD_Q_ESC)

// macros declarations
enum custom_keycodes {
    COMM_ECXL = SAFE_RANGE,
    DOT_QUES,
    SLSH_BSLS,
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COMM_ECXL:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods(); // get shift key situation
                if (current_mods & MOD_MASK_SHIFT) { // check Shift
                    tap_code16(S(KC_1));
                    return false;
                } else {
                    tap_code(KC_COMM);
                    return false;
                }
            }
            break;
        case DOT_QUES:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods(); // get shift key situation
                if (current_mods & MOD_MASK_SHIFT) { // check Shift
                    tap_code16(S(KC_SLSH));
                    return false;
                } else {
                    tap_code(KC_DOT);
                    return false;
                }
            }
            break;
        case SLSH_BSLS:
            if (record->event.pressed) {
                uint8_t current_mods = get_mods(); // get shift key situation
                if (current_mods & MOD_MASK_SHIFT) { // check Shift
                    tap_code16(S(KC_BSLS));
                    return false;
                } else {
                    tap_code(KC_SLSH);
                    return false;
                }
            }
            break;
    }
    return true;
}

#define SCR_LEFT KC_MS_WH_LEFT
#define SCR_DOWN KC_MS_WH_DOWN
#define SCR_UP KC_MS_WH_UP
#define SCR_RGHT KC_MS_WH_RIGHT


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    Q_ESC    , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , L_LT3    , CLN_SHT  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , COMM_ECXL, DOT_QUES , SLSH_BSLS,
    KC_LCTL  , KC_LGUI  , KC_LALT  , ESC_SHT  ,SPC_LT1   ,BSPC_LT2  ,      TAB_LT3  , ENT_CTL  , _______  , _______  , _______  , KC_DEL
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    S(KC_6)  , S(KC_3)  ,S(KC_BSLS), S(KC_7)  , S(KC_8)  ,                            KC_MINS  , KC_EQL   , KC_QUOT  , S(KC_GRV), S(KC_5)  ,
    S(KC_2)  ,S(KC_COMM),S(KC_LBRC), KC_LBRC  , S(KC_9)  ,                            S(KC_0)  , KC_RBRC  ,S(KC_RBRC), S(KC_DOT), S(KC_4)  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      CH_LANG  , KC_LSFT  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , KC_PGDN  , KC_PGUP  , _______  , _______  ,
    _______  , _______  , KC_LGUI  , KC_LALT  , KC_TAB   ,                            KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,
    _______  , _______  , _______  , _______  , KC_LCTL  ,                            SCR_LEFT , SCR_DOWN , SCR_UP   , SCR_RGHT ,  _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      KC_APP   , KC_LSFT  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  , KC_7     , KC_8     , KC_9     , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_0     , KC_4     , KC_5     , KC_6     , _______  ,                            _______  , _______  , SCRN_SHT , WIN_SEC  , _______  ,
    _______  , KC_1     , KC_2     , KC_3     , _______  ,                            KC_LCTL  , _______  , RGB_VAD  , RGB_VAI  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , RGB_TOG
  ),
};
// clang-format on

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif


// combo declarations
#ifdef COMBO_ENABLE
enum combos{
  BTN1,
  BTN2,
  BTN4,
  BTN5,
};
const uint16_t PROGMEM btn1[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM btn2[] = {KC_K, LT(3, KC_L), COMBO_END};
const uint16_t PROGMEM btn4[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM btn5[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[] = {
  [BTN1] = COMBO(btn1, KC_BTN1),
  [BTN2] = COMBO(btn2, KC_BTN2),
  [BTN4] = COMBO(btn4, KC_BTN4),
  [BTN5] = COMBO(btn5, KC_BTN5),
};
#endif


// per key tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPC_LT1:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}


layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    // control LED by layer
    HSV hsv = rgblight_get_hsv();  // get current HSV
    switch (get_highest_layer(state)) {
        case 0: hsv.h = 43;  break;  // HSV_YELLOW
        case 1: hsv.h = 0;   break;  // HSV_RED
        case 2: hsv.h = 85;  break;  // HSV_GREEN
        case 3: hsv.h = 170; break;  // HSV_BLUE
    }
    rgblight_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);  // adjust brightness

    return state;
}