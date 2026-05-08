/* ========== dashboard_info.h ========== */
#ifndef DASHBOARD_INFO_H
#define DASHBOARD_INFO_H

#include <stdint.h>
#include <stdbool.h>
#include "lvgl/lvgl.h"

/* Create all dashboard info elements */
void Dashboard_Create(lv_obj_t *parent);

/* Control functions */
void Dashboard_SetOdometer(uint32_t km);
void Dashboard_IncrementOdometer(void);
void Dashboard_SetBluetoothStatus(bool connected);
void Dashboard_SetCheckEngine(bool state);
void Dashboard_SetGear(char gear);

#endif /* DASHBOARD_INFO_H */
