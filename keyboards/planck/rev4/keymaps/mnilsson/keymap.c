#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "tri_layer.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#endif

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _RAISE,
    _LOWER,
    _DATA_ENTRY,
    _GAME,
    _GAME_COLEMAK,
    _GAME_LOWER,
    _ADJUST
};

enum planck_keycodes
{
    QWERTY = SAFE_RANGE,
    COLEMAK,
    LOWER,
    RAISE,
    DATAENT,
    GAME,
    GAME_COLEMAK,

    MP_1,
    MP_2,
    MP_3,
    MP_4
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LOWER_GM MO(_GAME_LOWER)
#define RAISE_GM MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
 * ,------------------------------------------------------------------------------------.
 * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |-------+------+------+------+------+-------------+------+------+------+------+------|
 * |Tab/ctl|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |-------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | Hyper | Ctrl | Alt  | GUI  |Lower | Space| Enter|Raise | Left | Down |  Up  |Right |
 * `------------------------------------------------------------------------------------'
     */
    [_QWERTY] = {
        {KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC},
        {CTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT},
        {KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
        {KC_HYPR, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_ENT, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}},

    /* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Hyper| Ctrl | Alt  | GUI  |Lower | Space| Enter|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
     */
    [_COLEMAK] = {
        {KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC},
        {CTL_T(KC_TAB), KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT},
        {KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
        {KC_HYPR, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_ENT, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}},

    /* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | pgdn | pgup |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = {
        {MP_1   , MP_2   , MP_3   , MP_4   , _______, _______, _______, _______, _______, _______, _______, KC_BSPC},
        {KC_DEL , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , _______, _______, _______, _______, _______},
        {_______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PGDN, KC_PGUP, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
    },

    /*
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  !   |  @   |  #   |  $   |   %  |  ^  |   &  |   *   |   (  |   )  |  _   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  ~   |  `   |  +   |  =   |  |   |  \   |  [   |  ]   |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = {{_______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS},
                {KC_DEL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS},
                {_______, KC_TILD, KC_GRV, KC_PLUS, KC_EQL, KC_PIPE, KC_BSLS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______},
                {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}},

    /* Data entry layer
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |TogOut|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
     */

    [_DATA_ENTRY] = {
        {_______, _______, _______, _______, _______,  KC_BSPC, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_A, KC_B},
        {_______, _______, _______, _______, _______,  _______, KC_P4, KC_P5, KC_P6, KC_PAST, KC_C, KC_D},
        {_______, _______, _______, _______, _______,  _______, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_E, KC_F},
        {LOWER, _______, _______, _______, _______,  _______, KC_P0, KC_PDOT, KC_PENT, KC_PPLS, _______, RAISE}
    },

    /* Game
     * ,------------------------------------------------------------------------------------.
     * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |-------+------+------+------+------+-------------+------+------+------+------+------|
     * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |-------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
     * |-------+------+------+------+------+------+------+------+------+------+------+------|
     * |      | GUI | Ctrl | Alt  |Lower | Space| Enter|Raise | Left | Down |  Up  |Right |
     * `------------------------------------------------------------------------------------'
     */
    [_GAME] = {
        {KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC},
        {KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT},
        {KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
        {KC_NO, KC_LGUI, KC_LCTL, KC_LALT,  LOWER_GM, KC_SPC, KC_ENT, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}
    },

    /* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Hyper| Ctrl | Alt  | GUI  |Lower | Space| Enter|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
     */
    [_GAME_COLEMAK] = {
        {KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC},
        {KC_TAB, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT},
        {KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT},
        {KC_NO, KC_LGUI, KC_LCTL, KC_LALT, LOWER_GM, KC_SPC, KC_ENT, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}
    },

    /*
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  5   |  6   |  7   |  8   |   %  |  ^  |   &  |   *   |   (  |   )  |  _   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  9   |  0   |  -   |  =   |  |   |  \   |  [   |  ]   |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
     */
    [_GAME_LOWER] = {
        {_______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS},
        {_______, KC_5, KC_6, KC_7, KC_8, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, LOWER},
        {_______, KC_9, KC_0, KC_MINS, KC_EQL, KC_PIPE, KC_BSLS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______},
        {_______, _______, _______, _______, _______, _______, LOWER, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}},

    /* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Bootld|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk| Game |      |NUMKEY|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      | cm gm|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = {
        {_______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL},
        {_______, _______, _______, AU_ON, AU_OFF, AG_NORM, AG_SWAP, QWERTY, COLEMAK, GAME, _______, DATAENT},
        {_______, AU_PREV, AU_NEXT, MU_ON, MU_OFF, MI_ON, MI_OFF, GAME, GAME_COLEMAK, _______, _______, _______},
        {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    }

};

void raw_hid_receive(uint8_t *data, uint8_t length) { raw_hid_send(data, length);}

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_is(_GAME_COLEMAK) || layer_state_is(_GAME_LOWER)) {
        return update_tri_layer_state(state, _GAME_LOWER, _RAISE, _ADJUST);
    } else {
        return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	    uint8_t response[32];
	    memset(response, 0, 32);

    switch (keycode)
    {
        case QWERTY:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL << _QWERTY);
            }
            return false;
            break;

        case COLEMAK:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL << _COLEMAK);
            }
            return false;
            break;
        case GAME:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAME);
            }
            return false;
            break;
        case GAME_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_GAME_COLEMAK);
            }
            return false;
            break;


        case MP_1:;
                  // mp1
            if (record->event.pressed) {
                  response[0] = 'M';
                  response[1] = 'P';
                  response[2] = '1';
                  raw_hid_send(response, 32);
            }
                  return false;
                  break;
        case MP_2:;
            if (record->event.pressed) {
                  response[0] = 'M';
                  response[1] = 'P';
                  response[2] = '2';
                  raw_hid_send(response, 32);
            }
                  return false;
                  break;

        case DATAENT:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL << _DATA_ENTRY);
            }
            return false;
            break;
    }
    return true;
}

