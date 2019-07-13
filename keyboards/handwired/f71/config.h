#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x6060
#define DEVICE_VER 0x0006
#define MANUFACTURER zonefuenf
#define PRODUCT F71 Keyboard
#define DESCRIPTION A compact keyboard with function key column

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MATRIX_ROW_PINS \
  { A4, A5, A6, A7, A8 }
#define MATRIX_COL_PINS \
  { A1, A0, B8, B13, B14, B15, B7, B6, B5, B2, B1, B12, B11, B10, B9, B0 }

#define DEBOUNCE 6

#define WS2812_LED_N 0
#define RGBLED_NUM WS2812_LED_N
#define TAPPING_TERM 400  
