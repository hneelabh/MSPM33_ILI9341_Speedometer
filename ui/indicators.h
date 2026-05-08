/* ========== indicators.h ========== */
#ifndef INDICATORS_H
#define INDICATORS_H

#include <stdbool.h>
#include "lvgl/lvgl.h"

/* Create turn signal indicators on parent screen */
void Indicators_Create(lv_obj_t *parent);

/* Control functions */
void Indicators_SetLeft(bool state);
void Indicators_SetRight(bool state);

/* Demo functions */
void Indicators_StartDemo(void);
void Indicators_StopDemo(void);

#endif /* INDICATORS_H */