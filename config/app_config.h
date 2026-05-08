#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "ti_msp_dl_config.h"

/* ========== Hardware Pin Configuration ========== */
#define TFT_RESET_PORT          GPIO_TFT_RESET_PORT
#define TFT_RESET_PIN           GPIO_TFT_RESET_TFT_RESET_PIN_PIN
#define TFT_DC_PORT             GPIO_TFT_DC_PORT
#define TFT_DC_PIN              GPIO_TFT_DC_TFT_DC_PIN_PIN
#define TFT_CS_PORT             GPIO_TFT_CS_PORT
#define TFT_CS_PIN              GPIO_TFT_CS_TFT_CS_PIN_PIN
#define TFT_SPI_INST            SPI_1_INST

/* ========== Display Dimensions ========== */
#define SCREEN_WIDTH            320
#define SCREEN_HEIGHT           240
#define LVGL_TICK_MS            10
#define LVGL_BUFFER_LINES       15      // Conservative size for stability

/* ========== Speedometer Configuration ========== */
#define MAX_SPEED               160
#define METER_SIZE              200
#define NEEDLE_PIVOT_X          160
#define NEEDLE_PIVOT_Y          145

/* ========== Animation Configuration ========== */
#define ANIM_ACCEL_TIME_MS      2000
#define ANIM_DECEL_TIME_MS      2000
#define ANIM_PAUSE_TIME_MS      1000

/* ========== Indicator Configuration ========== */
#define INDICATOR_BLINK_MS      400     // Realistic car blinker timing

/* ========== Fuel Gauge Configuration ========== */
#define FUEL_GAUGE_WIDTH        20      // Vertical bar width
#define FUEL_GAUGE_HEIGHT       80     // Vertical bar height

/* ========== Color Definitions ========== */
#define COLOR_GREEN             0x00FF00
#define COLOR_AMBER             0xFFAA00
#define COLOR_BLUE_BT           0x00A0FF
#define COLOR_WARNING           0xFF9500
#define COLOR_FUEL_RED          0xFF0000
#define COLOR_FUEL_ORANGE       0xFF4000
#define COLOR_FUEL_YELLOW       0xFFFF00
#define COLOR_FUEL_GREEN        0x00FF00
#define COLOR_FUEL_BG           0x303030  // Background color

/* ========== UI Positioning ========== */
#define LEFT_INDICATOR_X        10
#define LEFT_INDICATOR_Y        10
#define RIGHT_INDICATOR_X       265
#define RIGHT_INDICATOR_Y       10
#define FUEL_GAUGE_X            10      // Left side of screen
#define FUEL_GAUGE_Y            80      // Centered vertically
#define ODOMETER_X              110
#define ODOMETER_Y              190
#define BT_SYMBOL_X             155
#define BT_SYMBOL_Y             90
#define CHECK_ENGINE_X          125
#define CHECK_ENGINE_Y          100
#define GEAR_X                  185
#define GEAR_Y                  100

#endif /* APP_CONFIG_H */