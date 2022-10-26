#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _SYMBOLS 1
#define _NAVNUM 2

#define OSM_SMB OSL(_SYMBOLS)
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
// #define CM TO(_COLEMAK)
// #define SYM TO(_SYMBOLS)
// #define NVNM TO(_NAVNUM)

// KeyMap ---------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_MINS,
        OSM_SFT, KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_M  , KC_N  , KC_E  , KC_I  , KC_O  ,OSM_SMB,
        OSM_CTL, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                         RAISE,KC_SPC,                        KC_ENT, LOWER,
                                         KC_TAB,KC_HOME,                         KC_END,  KC_DEL,
                                         KC_BSPC, KC_GRV,                        KC_LGUI, KC_LALT
    ),

    [_SYMBOLS] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                                                _______,KC_PSCR,            _______, KC_P0,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______

    ),

    [_NAVNUM] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
          _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
          _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                                                  _______,_______,            KC_EQL ,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    )
};

// Encoder Section ------------------------------------------------------------
void lr_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_RGHT);
    } else {
        tap_code(KC_LEFT)
    }
}

void ud_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_DOWN);
    } else {
        tap_code(KC_UP)
    }
}

void scroll_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_WH_D);
    } else {
        tap_code(KC_WH_U)
    }
}

void volume_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU)
    }
}

void LED_brightness(bool clockwise){
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU)
    }
}

void LED_hue(bool clockwise){
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU)
    }
}

static void (*left_modes[3])() = {ud_mode, volume_mode, LED_brightness};

static void (*right_modes[3])() = {lr_mode, scroll_mode, LED_hue};

static int current_mode_left = 0;

static int current_mode_right = 0;

void encoder_increment_left(){
    current_mode_left = (current_mode_left + 1) % 3
}

void encoder_increment_right(){
    current_mode_right = (current_mode_right + 1) % 3
}

void encoder_tap_left(){
    switch (current_mode_left) {
    case 0: // Up/Down mode
        // Not defined
        return;
    case 1: // volume mode
        tap_code(KC_MUTE)
        return;
    case 2: // LED brightness toggle
        // toggle LED on/off
        return;
    }
}

void encoder_tap_right(){
    switch (current_mode_right) {
    case 0: // Left/Right mode
        tap_code(KC_SPC)
        return;
    case 1: // Scroll mode
        tap_code(KC_BTN3)
        return;
    case 2: // LED hue toggle
        // toggle LED pattern
        return;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        (*left_modes[current_mode_left])(clockwise);
    } else if (index == 1) {
        (*right_modes[current_mode_right])(clockwise);
    }
    return false;
}

// Added Keys -----------------------------------------------------------------
enum my_keycodes {
    KC_EIL = SAFE_RANGE,
    KC_EIR,
    KC_ETL,
    KC_ETR,
    TD_ENCL,
    TD_ENCR,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ENCL] = ACTION_TAP_DANCE_DOUBLE(KC_ETL, KC_EIL),
    [TD_ENCR] = ACTION_TAP_DANCE_DOUBLE(KC_ETR, KC_EIR),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    /* Sample Key
    case KC_KEYCODE:
        if (record->event.pressed) {
        // Do something when pressed
        } else {
        // Do something else when release
        }
        return false; // true: continue processing key | false: stop processing key
    */
    case KC_EIL:
        if (record->event.pressed) {
            encoder_increment_left()
        }
        return false;
    case KC_EIR:
        if (record->event.pressed) {
            encoder_increment_right()
        }
        return false;
    case KC_ETL:
        if (record->event.pressed) {
            encoder_tap_left()
        }
        return false;
    case KC_ETR:
        if (record->event.pressed) {
            encoder_tap_right()
        }
        return false;
    default:
        return true; // Process all other keycodes normally
    }
}
