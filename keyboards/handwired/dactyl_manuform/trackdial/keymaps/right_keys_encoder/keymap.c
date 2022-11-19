#include QMK_KEYBOARD_H

// Trackball Section ----------------------------------------------------------
// void pointing_device_init_kb(void) {
// #ifdef PMW33XX_CPI
//     pointing_device_set_cpi(PMW33XX_CPI);
// #endif
// }


// Encoder Section ------------------------------------------------------------
void lr_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_RGHT);
    } else {
        tap_code(KC_LEFT);
    }
}

void ud_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_DOWN);
    } else {
        tap_code(KC_UP);
    }
}

void scroll_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_WH_U);
    } else {
        tap_code(KC_WH_D);
    }
}

void volume_mode(bool clockwise){
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
}

void LED_brightness(bool clockwise){
    if (clockwise) {
        rgb_matrix_increase_val();
    } else {
        rgb_matrix_decrease_val();
    }
}

void LED_hue(bool clockwise){
    if (clockwise) {
        rgb_matrix_increase_hue();
    } else {
        rgb_matrix_decrease_hue();
    }
}

static void (*left_modes[3])(bool clockwise) = {ud_mode, volume_mode, LED_brightness};

static void (*right_modes[3])(bool clockwise) = {lr_mode, scroll_mode, LED_hue};

static uint8_t current_mode_left = 0;

static uint8_t current_mode_right = 0;

static void encoder_increment_left(void){
    current_mode_left = (current_mode_left + 1) % 3;
}

static void encoder_increment_right(void){
    current_mode_right = (current_mode_right + 1) % 3;
}

static void encoder_tap_left(void){
    switch (current_mode_left) {
    case 0: // Up/Down mode
        // Not defined
        return;
    case 1: // volume mode
        tap_code(KC_MUTE);
        return;
    case 2: // LED brightness toggle
        // toggle LED on/off
        rgb_matrix_toggle();
        return;
    }
}

static void encoder_tap_right(void){
    switch (current_mode_right) {
    case 0: // Left/Right mode
        tap_code(KC_SPC);
        return;
    case 1: // Scroll mode
        tap_code(KC_BTN3);
        return;
    case 2: // LED hue toggle
        // toggle LED pattern
        rgb_matrix_step();
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

enum {
    TD_ENCL,
    TD_ENCR,
};

void tap_dance_left_encoder(qk_tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        encoder_tap_left();
    } else if (state->count == 2) {
        encoder_increment_left();
    }
}

void tap_dance_right_encoder(qk_tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        encoder_tap_right();
    } else if (state->count == 2) {
        encoder_increment_right();
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ENCL] = ACTION_TAP_DANCE_FN(tap_dance_left_encoder),
    [TD_ENCR] = ACTION_TAP_DANCE_FN(tap_dance_right_encoder),
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//     /* Sample Key
//     case KC_KEYCODE:
//         if (record->event.pressed) {
//         // Do something when pressed
//         } else {
//         // Do something else when release
//         }
//         return false; // true: continue processing key | false: stop processing key
//     */
//     default:
//         return true; // Process all other keycodes normally
//     }
// }

#define _COLEMAK 0
#define _SYMBOLS 1
#define _NUMBERS 2

#define OSM_SYM OSL(_SYMBOLS)
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
// #define CM TO(_COLEMAK)
 #define SYM TO(_SYMBOLS)
 #define NUM TO(_NUMBERS)

// KeyMap ---------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_4,
        KC_LGUI, KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,                         KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_HOME,
        OSM_SFT, KC_A  , KC_R  , KC_S  , KC_T  , KC_G  ,                         KC_M  , KC_N  , KC_E  , KC_I  , KC_O  ,OSM_SYM,
        OSM_CTL, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,                         KC_K  , KC_H  ,KC_COMM,KC_DOT ,KC_SLSH,KC_END,
                         SYM   , NUM   ,                                                         KC_2  , KC_3  ,
                                        TD(TD_ENCL),KC_BSPC,                            TD(TD_ENCR),
                                        KC_TAB , KC_SPC,             KC_BTN2,       KC_BTN3,
                                        KC_LALT, KC_ENT,                   KC_BTN1
    ),

    [_SYMBOLS] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,_______,
        _______,_______,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,_______,_______,
        _______,_______,_______,_______,_______,_______,                        KC_P1  , KC_P1 , KC_P2 , KC_P3 ,_______,_______,
                        _______,_______,                                                        _______,_______,
                                        _______,_______,                                _______,
                                        _______,_______,         _______,       _______,
                                        _______,_______,                 _______

    ),

    [_NUMBERS] = LAYOUT_5x6(
        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
        _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
        _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
                        _______,_______,                                                        _______,_______,
                                        _______,_______,                                _______,
                                        _______,_______,         _______,       _______,
                                        _______,_______,                 _______
    )
};