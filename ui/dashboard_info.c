/* ========== dashboard_info.c ========== */
#include "dashboard_info.h"
#include "../config/app_config.h"
#include <stdio.h>

static lv_obj_t *odometer_label;
static lv_obj_t *bt_symbol;
static lv_obj_t *check_engine_symbol;
static lv_obj_t *gear_label;

static uint32_t odometer_km = 0;
static bool bt_connected = false;
static bool check_engine_state = false;

static void create_odometer(lv_obj_t *parent) {
    lv_obj_t *odo_bg = lv_obj_create(parent);
    lv_obj_set_size(odo_bg, 100, 28);
    lv_obj_set_pos(odo_bg, ODOMETER_X, ODOMETER_Y);
    lv_obj_set_style_bg_color(odo_bg, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(odo_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(odo_bg, 0, 0);
    lv_obj_set_style_radius(odo_bg, 3, 0);
    lv_obj_set_style_shadow_width(odo_bg, 0, 0);
    lv_obj_clear_flag(odo_bg, LV_OBJ_FLAG_SCROLLABLE);
    
    odometer_label = lv_label_create(odo_bg);
    char buf[16];
    // Format with one decimal place
    uint32_t whole_km = odometer_km;
    snprintf(buf, sizeof(buf), "%lu.0", (unsigned long)whole_km);
    lv_label_set_text(odometer_label, buf);
    lv_obj_set_style_text_color(odometer_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(odometer_label, &lv_font_montserrat_16, 0);
    lv_obj_center(odometer_label);
}

static void create_bt_symbol(lv_obj_t *parent) {
    bt_symbol = lv_label_create(parent);
    lv_label_set_text(bt_symbol, LV_SYMBOL_BLUETOOTH);
    lv_obj_set_style_text_color(bt_symbol, lv_color_hex(COLOR_BLUE_BT), 0);
    lv_obj_set_style_text_font(bt_symbol, &lv_font_montserrat_18, 0);
    lv_obj_set_pos(bt_symbol, BT_SYMBOL_X, BT_SYMBOL_Y);
    
    if (!bt_connected) {
        lv_obj_add_flag(bt_symbol, LV_OBJ_FLAG_HIDDEN);
    }
}

static void create_check_engine_symbol(lv_obj_t *parent) {
    check_engine_symbol = lv_label_create(parent);
    lv_label_set_text(check_engine_symbol, LV_SYMBOL_WARNING);
    lv_obj_set_style_text_color(check_engine_symbol, lv_color_hex(COLOR_WARNING), 0);
    lv_obj_set_style_text_font(check_engine_symbol, &lv_font_montserrat_14, 0);
    lv_obj_set_pos(check_engine_symbol, CHECK_ENGINE_X, CHECK_ENGINE_Y);
}

static void create_gear_label(lv_obj_t *parent) {
    gear_label = lv_label_create(parent);
    lv_label_set_text(gear_label, "D");
    lv_obj_set_style_text_color(gear_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(gear_label, &lv_font_montserrat_14, 0);
    lv_obj_set_pos(gear_label, GEAR_X, GEAR_Y);
}

void Dashboard_Create(lv_obj_t *parent) {
    create_odometer(parent);
    create_bt_symbol(parent);
    create_check_engine_symbol(parent);
    create_gear_label(parent);
}

void Dashboard_SetOdometer(uint32_t km) {
    odometer_km = km;
    if (odometer_label) {
        char buf[16];
        // Format with one decimal place
        uint32_t whole_km = odometer_km;
        snprintf(buf, sizeof(buf), "%lu.0", (unsigned long)whole_km);
        lv_label_set_text(odometer_label, buf);
    }
}

void Dashboard_IncrementOdometer(void) {
    odometer_km++;
    if (odometer_label) {
        char buf[16];
        // Format with one decimal place
        uint32_t whole_km = odometer_km;
        snprintf(buf, sizeof(buf), "%lu.0", (unsigned long)whole_km);
        lv_label_set_text(odometer_label, buf);
    }
}

void Dashboard_SetBluetoothStatus(bool connected) {
    bt_connected = connected;
    if (bt_symbol) {
        if (connected) {
            lv_obj_clear_flag(bt_symbol, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(bt_symbol, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void Dashboard_SetCheckEngine(bool state) {
    check_engine_state = state;
    if (check_engine_symbol) {
        if (state) {
            lv_obj_clear_flag(check_engine_symbol, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_flag(check_engine_symbol, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void Dashboard_SetGear(char gear) {
    if (gear_label) {
        char buf[2] = {gear, '\0'};
        lv_label_set_text(gear_label, buf);
    }
}