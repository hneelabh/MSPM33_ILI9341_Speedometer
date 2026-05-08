/* ========== speedometer_ui.c ========== */
#include "speedometer_ui.h"
#include "indicators.h"
#include "fuel_gauge.h"
#include "dashboard_info.h"
#include "../config/app_config.h"
#include "assets/re_logo.h"
#include <stdio.h>

static lv_obj_t *meter;
static lv_meter_indicator_t *needle_indicator;
static lv_meter_scale_t *scale;
static lv_obj_t *speed_label;

static void set_needle_value(void *indicator, int32_t value) {
    lv_meter_set_indicator_value(meter, (lv_meter_indicator_t *)indicator, value);
    
    if (speed_label) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", (int)value);
        lv_label_set_text(speed_label, buf);
    }
}

static void create_speedometer_background(lv_obj_t *scr) {
    // Create LVGL image descriptor for speedometer background
    static lv_img_dsc_t speedometer_dsc = {
        .header.always_zero = 0,
        .header.w = SPEEDOMETER_WIDTH,
        .header.h = SPEEDOMETER_HEIGHT,
        .data_size = SPEEDOMETER_WIDTH * SPEEDOMETER_HEIGHT * LV_COLOR_SIZE / 8,
        .header.cf = LV_IMG_CF_TRUE_COLOR,
        .data = (uint8_t *)speedometerImage,
    };
    
    lv_obj_t *speedometer_img = lv_img_create(scr);
    lv_img_set_src(speedometer_img, &speedometer_dsc);
    
    uint16_t x_offset = (SCREEN_WIDTH - SPEEDOMETER_WIDTH) / 2;
    uint16_t y_offset = (SCREEN_HEIGHT - SPEEDOMETER_HEIGHT) / 2;
    lv_obj_set_pos(speedometer_img, x_offset, y_offset);
}

static void create_meter_and_needle(lv_obj_t *scr) {
    meter = lv_meter_create(scr);
    lv_obj_set_size(meter, METER_SIZE, METER_SIZE);
    
    int16_t meter_x = NEEDLE_PIVOT_X - (METER_SIZE / 2);
    int16_t meter_y = NEEDLE_PIVOT_Y - (METER_SIZE / 2);
    lv_obj_set_pos(meter, meter_x, meter_y);
    
    // Make meter transparent (only for needle math)
    lv_obj_set_style_bg_opa(meter, LV_OPA_TRANSP, 0);
    lv_obj_set_style_bg_opa(meter, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(meter, LV_OPA_TRANSP, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(meter, 0, LV_PART_TICKS);
    lv_obj_set_style_border_width(meter, 0, 0);
    lv_obj_set_style_shadow_width(meter, 0, 0);
    lv_obj_set_style_outline_width(meter, 0, 0);
    lv_obj_set_style_pad_all(meter, 0, 0);
    lv_obj_set_style_radius(meter, 0, 0);
    lv_obj_clear_flag(meter, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(meter, LV_OBJ_FLAG_SCROLLABLE);
    
    scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_range(meter, scale, 0, MAX_SPEED, 260, 140);
    
    needle_indicator = lv_meter_add_needle_line(meter, scale, 4,  lv_palette_main(LV_PALETTE_RED), -10);
    
    // Center dot for needle pivot
    lv_obj_t *center_dot = lv_obj_create(scr);
    lv_obj_set_size(center_dot, 12, 12);
    lv_obj_set_style_radius(center_dot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(center_dot, lv_color_make(200, 200, 200), 0);
    lv_obj_set_style_border_width(center_dot, 2, 0);
    lv_obj_set_style_border_color(center_dot, lv_color_make(80, 80, 80), 0);
    lv_obj_set_style_shadow_width(center_dot, 0, 0);
    lv_obj_clear_flag(center_dot, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(center_dot, NEEDLE_PIVOT_X - 6, NEEDLE_PIVOT_Y - 6);
}

static void create_digital_speed_display(lv_obj_t *scr) {
    lv_obj_t *speed_bg = lv_obj_create(scr);
    lv_obj_set_size(speed_bg, 60, 60);
    lv_obj_set_style_radius(speed_bg, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(speed_bg, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(speed_bg, LV_OPA_90, 0);
    lv_obj_set_style_border_width(speed_bg, 2, 0);
    lv_obj_set_style_border_color(speed_bg, lv_color_make(100, 100, 100), 0);
    lv_obj_set_style_shadow_width(speed_bg, 0, 0);
    lv_obj_clear_flag(speed_bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(speed_bg, NEEDLE_PIVOT_X - 30, NEEDLE_PIVOT_Y - 30);
    
    speed_label = lv_label_create(speed_bg);
    lv_label_set_text(speed_label, "0");
    lv_obj_set_style_text_color(speed_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_30, 0);
    lv_obj_center(speed_label);
}

static void start_speed_animation(void) {
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_exec_cb(&anim, set_needle_value);
    lv_anim_set_var(&anim, needle_indicator);
    lv_anim_set_values(&anim, 0, MAX_SPEED);
    lv_anim_set_time(&anim, ANIM_ACCEL_TIME_MS);
    lv_anim_set_repeat_delay(&anim, ANIM_PAUSE_TIME_MS);
    lv_anim_set_playback_time(&anim, ANIM_DECEL_TIME_MS);
    lv_anim_set_playback_delay(&anim, ANIM_PAUSE_TIME_MS);
    lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&anim);
}

void Speedometer_Create(void) {
    lv_obj_t *scr = lv_scr_act();
    
    // Set black background with no borders
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_border_width(scr, 0, 0);
    lv_obj_set_style_outline_width(scr, 0, 0);
    lv_obj_set_style_pad_all(scr, 0, 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    
    // Create UI components
    create_speedometer_background(scr);
    create_meter_and_needle(scr);
    create_digital_speed_display(scr);
    
    // Create sub-components
    Indicators_Create(scr);
    FuelGauge_Create(scr);
    Dashboard_Create(scr);
    
    // Start animation
    start_speed_animation();
}

void Speedometer_SetSpeed(int16_t speed) {
    if (speed < 0) speed = 0;
    if (speed > MAX_SPEED) speed = MAX_SPEED;
    lv_meter_set_indicator_value(meter, needle_indicator, speed);
    
    if (speed_label) {
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", (int)speed);
        lv_label_set_text(speed_label, buf);
    }
}