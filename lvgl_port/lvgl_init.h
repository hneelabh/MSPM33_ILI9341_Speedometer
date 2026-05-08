/* ========== lvgl_init.h ========== */
#ifndef LVGL_INIT_H
#define LVGL_INIT_H

#include "lvgl/lvgl.h"

/* Initialize LVGL library and display driver */
void LVGL_Init(void);

/* Get the display driver (for reference if needed) */
lv_disp_drv_t* LVGL_GetDisplayDriver(void);

#endif /* LVGL_INIT_H */