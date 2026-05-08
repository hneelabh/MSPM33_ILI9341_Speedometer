/* ========== speedometer_ui.h ========== */
#ifndef SPEEDOMETER_UI_H
#define SPEEDOMETER_UI_H

#include <stdint.h>
#include "lvgl/lvgl.h"

/* Create the complete speedometer UI */
void Speedometer_Create(void);

/* Set speed (0-160 km/h) */
void Speedometer_SetSpeed(int16_t speed);

#endif /* SPEEDOMETER_UI_H */