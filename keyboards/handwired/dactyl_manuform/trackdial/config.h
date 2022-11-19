#pragma once

#include "config_common.h"
// Metadata
#define PRODUCT_ID      0x8658
#define DEVICE_VER      0x0001
#ifdef MANUFACTURER
 #undef MANUFACTURER
#endif
#define MANUFACTURER    JQuan
#define VENDOR_ID       0xFEED

// Communication
// #define USE_I2C

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { B7, D5, C7, F1, F0, B6 }

#define DIODE_DIRECTION ROW2COL // Right
// #define DIODE_DIRECTION COL2ROW

// WS2812 RGB LED strip input and number of LEDs
// #define RGB_DI_PIN D3
// #define RGBLED_NUM 60

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3
