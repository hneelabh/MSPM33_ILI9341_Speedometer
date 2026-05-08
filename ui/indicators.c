
/* ========== indicators.c ========== */
#include "indicators.h"
#include "../config/app_config.h"

static lv_obj_t *left_indicator;
static lv_obj_t *right_indicator;
static bool left_indicator_state = false;
static bool right_indicator_state = false;

static uint8_t demo_step = 0;
static lv_timer_t *demo_timer = NULL;

static lv_obj_t* create_arrow_indicator(lv_obj_t *parent, bool is_left) {
    lv_obj_t *arrow = lv_label_create(parent);
    
    if (is_left) {
        lv_label_set_text(arrow, LV_SYMBOL_LEFT);
    } else {
        lv_label_set_text(arrow, LV_SYMBOL_RIGHT);
    }
    
    lv_obj_set_style_text_font(arrow, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(arrow, lv_color_hex(COLOR_GREEN), 0);
    
    return arrow;
}

static void demo_blink_cb(lv_timer_t *timer) {
    bool on = (demo_step % 2) == 0;
    uint8_t blink_number = (demo_step / 2) + 1;
    bool is_left_turn = (blink_number <= 3);
    
    /* Left indicator - active only during its 3 blinks */
    if (is_left_turn) {
        lv_obj_set_style_opa(left_indicator, on ? LV_OPA_100 : LV_OPA_0, 0);
        lv_obj_set_style_text_color(left_indicator, lv_color_hex(COLOR_GREEN), 0);
    } else {
        lv_obj_set_style_opa(left_indicator, LV_OPA_0, 0);
    }
    
    /* Right indicator - active only during its 3 blinks */
    if (!is_left_turn && blink_number > 3) {
        lv_obj_set_style_opa(right_indicator, on ? LV_OPA_100 : LV_OPA_0, 0);
        lv_obj_set_style_text_color(right_indicator, lv_color_hex(COLOR_GREEN), 0);
    } else {
        lv_obj_set_style_opa(right_indicator, LV_OPA_0, 0);
    }
    
    demo_step++;
    if (demo_step >= 12) {
        demo_step = 0;
    }
}

void Indicators_Create(lv_obj_t *parent) {
    left_indicator = create_arrow_indicator(parent, true);
    lv_obj_set_pos(left_indicator, LEFT_INDICATOR_X, LEFT_INDICATOR_Y);
    
    right_indicator = create_arrow_indicator(parent, false);
    lv_obj_set_pos(right_indicator, RIGHT_INDICATOR_X, RIGHT_INDICATOR_Y);
}

void Indicators_SetLeft(bool state) {
    left_indicator_state = state;
}

void Indicators_SetRight(bool state) {
    right_indicator_state = state;
}

void Indicators_StartDemo(void) {
    demo_step = 0;
    if (demo_timer == NULL) {
        demo_timer = lv_timer_create(demo_blink_cb, INDICATOR_BLINK_MS, NULL);
    } else {
        lv_timer_reset(demo_timer);
    }
}

void Indicators_StopDemo(void) {
    if (demo_timer) {
        lv_timer_del(demo_timer);
        demo_timer = NULL;
    }
    lv_obj_set_style_opa(left_indicator, LV_OPA_0, 0);
    lv_obj_set_style_opa(right_indicator, LV_OPA_0, 0);
    demo_step = 0;
}