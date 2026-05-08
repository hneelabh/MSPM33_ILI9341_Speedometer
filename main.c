/*
 * Main Application - Modular Speedometer
 * Clean, focused entry point
 */

#include <stdio.h>
#include "ti_msp_dl_config.h"
#include <ti/devices/msp/msp.h>
#include "lvgl/lvgl.h"

// Hardware modules
#include "hardware/spi_interface.h"
#include "hardware/tft_ili9341.h"

// LVGL integration
#include "lvgl_port/lvgl_init.h"
#include "lvgl_port/lvgl_timer.h"

// UI modules
#include "ui/speedometer_ui.h"
#include "ui/indicators.h"
#include "ui/fuel_gauge.h"
#include "ui/dashboard_info.h"

/* ========== Initialization ========== */
static void Hardware_Init(void) {
    SYSCFG_DL_init();
    SPI_Init();
    TFT_Init();
}

static void Display_Init(void) {
    LVGL_Init();
    LVGL_Timer_Setup();
}

static void UI_Init(void) {
    Speedometer_Create();
}

static void Demo_Setup(void) {
    // Configure initial demo state
    Dashboard_SetBluetoothStatus(true);
    Dashboard_SetCheckEngine(true);
    Dashboard_SetGear('D');
    Dashboard_SetOdometer(25201);  // Display 25201.0 km
    FuelGauge_SetLevel(80);
    Indicators_StartDemo();
}

/* ========== Main Program ========== */
int main(void) {
    // Initialize all subsystems
    Hardware_Init();
    Display_Init();
    UI_Init();
    Demo_Setup();
    
    // Main loop - Balanced update frequency
    while (1) {
        lv_timer_handler();
        delay_cycles(100);  // Balanced for smooth animation without overload
    }
    
    return 0;
}

/* ========== Public API Example Usage ========== */

// To change speed manually:
// Speedometer_SetSpeed(80);

// To control indicators:
// Indicators_SetLeft(true);
// Indicators_SetRight(false);

// To update fuel:
// FuelGauge_SetLevel(45);

// To update dashboard:
// Dashboard_SetOdometer(12345);
// Dashboard_IncrementOdometer();
// Dashboard_SetGear('P');
// Dashboard_SetBluetoothStatus(false);
// Dashboard_SetCheckEngine(false);