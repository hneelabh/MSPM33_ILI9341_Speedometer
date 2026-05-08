/* ========== fuel_gauge.h ========== */
#ifndef FUEL_GAUGE_H
#define FUEL_GAUGE_H

#include <stdint.h>
#include "lvgl/lvgl.h"

/* Create fuel gauge on parent screen */
void FuelGauge_Create(lv_obj_t *parent);

/* Set fuel level (0-100%) */
void FuelGauge_SetLevel(uint8_t level);

#endif /* FUEL_GAUGE_H */