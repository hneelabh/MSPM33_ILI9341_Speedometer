// /* ========== fuel_gauge.c ========== */
// #include "fuel_gauge.h"
// #include "../config/app_config.h"
// 
// static lv_obj_t *fuel_bar;
// static lv_obj_t *fuel_fill;
// static uint8_t fuel_level = 80;
// 
// void FuelGauge_Create(lv_obj_t *parent) {
//     // Outer container (border)
//     fuel_bar = lv_obj_create(parent);
//     lv_obj_set_size(fuel_bar, FUEL_GAUGE_WIDTH, FUEL_GAUGE_HEIGHT);
//     lv_obj_set_pos(fuel_bar, FUEL_GAUGE_X, FUEL_GAUGE_Y);
//     lv_obj_set_style_bg_color(fuel_bar, lv_color_hex(COLOR_FUEL_BG), 0);
//     lv_obj_set_style_bg_opa(fuel_bar, LV_OPA_80, 0);
//     lv_obj_set_style_border_width(fuel_bar, 2, 0);
//     lv_obj_set_style_border_color(fuel_bar, lv_color_make(100, 100, 100), 0);
//     lv_obj_set_style_radius(fuel_bar, 3, 0);
//     lv_obj_set_style_pad_all(fuel_bar, 3, 0);
//     lv_obj_clear_flag(fuel_bar, LV_OBJ_FLAG_SCROLLABLE);
//     
//     // Inner fill bar (colored based on fuel level)
//     fuel_fill = lv_obj_create(fuel_bar);
//     lv_obj_set_size(fuel_fill, FUEL_GAUGE_WIDTH - 10, 0);  // Height set by SetLevel
//     lv_obj_set_style_bg_color(fuel_fill, lv_color_hex(COLOR_FUEL_GREEN), 0);
//     lv_obj_set_style_border_width(fuel_fill, 0, 0);
//     lv_obj_set_style_radius(fuel_fill, 2, 0);
//     lv_obj_set_style_shadow_width(fuel_fill, 0, 0);
//     lv_obj_clear_flag(fuel_fill, LV_OBJ_FLAG_SCROLLABLE);
//     
//     // Position at bottom (will grow upward)
//     lv_obj_align(fuel_fill, LV_ALIGN_BOTTOM_MID, 0, 0);
//     
//     // Set initial level
//     FuelGauge_SetLevel(fuel_level);
// }
// 
// void FuelGauge_SetLevel(uint8_t level) {
//     if (level > 100) level = 100;
//     fuel_level = level;
//     
//     if (!fuel_fill) return;
//     
//     // Calculate fill height (leave padding)
//     int max_fill_height = FUEL_GAUGE_HEIGHT - 10;
//     int fill_height = (level * max_fill_height) / 100;
//     
//     // Update fill bar height
//     lv_obj_set_height(fuel_fill, fill_height);
//     
//     // Update color based on level (gradient from red to green)
//     lv_color_t fill_color;
//     if (fuel_level <= 20) {
//         fill_color = lv_color_hex(COLOR_FUEL_RED);
//     } else if (fuel_level <= 40) {
//         fill_color = lv_color_hex(COLOR_FUEL_ORANGE);
//     } else if (fuel_level <= 60) {
//         fill_color = lv_color_hex(0xFF8000);  // Orange
//     } else if (fuel_level <= 80) {
//         fill_color = lv_color_hex(COLOR_FUEL_YELLOW);
//     } else {
//         fill_color = lv_color_hex(COLOR_FUEL_GREEN);
//     }
//     
//     lv_obj_set_style_bg_color(fuel_fill, fill_color, 0);
//     
//     // Re-align to bottom (fills upward)
//     lv_obj_align(fuel_fill, LV_ALIGN_BOTTOM_MID, 0, 0);
// }

/* ========== fuel_gauge.c ========== */
#include "fuel_gauge.h"
#include "../config/app_config.h"

static lv_obj_t *fuel_bar;
static lv_obj_t *fuel_fill;
static lv_obj_t *label_e;
static lv_obj_t *label_f;
static uint8_t fuel_level = 80;

void FuelGauge_Create(lv_obj_t *parent) {
    // Outer container (border)
    fuel_bar = lv_obj_create(parent);
    lv_obj_set_size(fuel_bar, FUEL_GAUGE_WIDTH, FUEL_GAUGE_HEIGHT);
    lv_obj_set_pos(fuel_bar, FUEL_GAUGE_X, FUEL_GAUGE_Y);
    lv_obj_set_style_bg_color(fuel_bar, lv_color_hex(COLOR_FUEL_BG), 0);
    lv_obj_set_style_bg_opa(fuel_bar, LV_OPA_80, 0);
    lv_obj_set_style_border_width(fuel_bar, 2, 0);
    lv_obj_set_style_border_color(fuel_bar, lv_color_make(100, 100, 100), 0);
    lv_obj_set_style_radius(fuel_bar, 3, 0);
    lv_obj_set_style_pad_all(fuel_bar, 3, 0);
    lv_obj_clear_flag(fuel_bar, LV_OBJ_FLAG_SCROLLABLE);
   
    // Inner fill bar (colored based on fuel level)
    fuel_fill = lv_obj_create(fuel_bar);
    lv_obj_set_size(fuel_fill, FUEL_GAUGE_WIDTH - 10, 0); // Height set by SetLevel
    lv_obj_set_style_bg_color(fuel_fill, lv_color_hex(COLOR_FUEL_GREEN), 0);
    lv_obj_set_style_border_width(fuel_fill, 0, 0);
    lv_obj_set_style_radius(fuel_fill, 2, 0);
    lv_obj_set_style_shadow_width(fuel_fill, 0, 0);
    lv_obj_clear_flag(fuel_fill, LV_OBJ_FLAG_SCROLLABLE);
   
    // Position at bottom (will grow upward)
    lv_obj_align(fuel_fill, LV_ALIGN_BOTTOM_MID, 0, 0);
   
    // "E" label at bottom outside
    label_e = lv_label_create(parent);
    lv_label_set_text(label_e, "E");
    lv_obj_set_style_text_color(label_e, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_e, &lv_font_montserrat_14, 0); // Adjust font size if needed
    lv_obj_align_to(label_e, fuel_bar, LV_ALIGN_OUT_BOTTOM_MID, 0, 2);
   
    // "F" label at top outside
    label_f = lv_label_create(parent);
    lv_label_set_text(label_f, "F");
    lv_obj_set_style_text_color(label_f, lv_color_white(), 0);
    lv_obj_set_style_text_font(label_f, &lv_font_montserrat_14, 0); // Adjust font size if needed
    lv_obj_align_to(label_f, fuel_bar, LV_ALIGN_OUT_TOP_MID, 0, -2);
   
    // Set initial level
    FuelGauge_SetLevel(fuel_level);
}

void FuelGauge_SetLevel(uint8_t level) {
    if (level > 100) level = 100;
    fuel_level = level;
   
    if (!fuel_fill) return;
   
    // Calculate fill height (leave padding)
    int max_fill_height = FUEL_GAUGE_HEIGHT - 10;
    int fill_height = (level * max_fill_height) / 100;
   
    // Update fill bar height
    lv_obj_set_height(fuel_fill, fill_height);
   
    // Update color based on level (gradient from red to green)
    lv_color_t fill_color;
    if (fuel_level <= 20) {
        fill_color = lv_color_hex(COLOR_FUEL_RED);
    } else if (fuel_level <= 40) {
        fill_color = lv_color_hex(COLOR_FUEL_ORANGE);
    } else if (fuel_level <= 60) {
        fill_color = lv_color_hex(0xFF8000); // Orange
    } else if (fuel_level <= 80) {
        fill_color = lv_color_hex(COLOR_FUEL_YELLOW);
    } else {
        fill_color = lv_color_hex(COLOR_FUEL_GREEN);
    }
   
    lv_obj_set_style_bg_color(fuel_fill, fill_color, 0);
   
    // Re-align to bottom (fills upward)
    lv_obj_align(fuel_fill, LV_ALIGN_BOTTOM_MID, 0, 0);
}