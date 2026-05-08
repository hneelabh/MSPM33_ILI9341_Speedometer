// /* ========== lvgl_init.c ========== */
// #include "lvgl_init.h"
// #include "../hardware/tft_ili9341.h"
// #include "../hardware/spi_interface.h"
// #include "../config/app_config.h"// 

// /* LVGL Display Buffers */
// static lv_color_t lvgl_buf1[SCREEN_WIDTH * 10];
// static lv_color_t lvgl_buf2[SCREEN_WIDTH * 10];
// static lv_disp_drv_t disp_drv;
// static lv_disp_draw_buf_t disp_buf;// 

// /* LVGL Display Flush Callback */
// static void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
//     uint16_t width = area->x2 - area->x1 + 1;
//     uint16_t height = area->y2 - area->y1 + 1;
//     
//     TFT_SetAddressWindow(area->x1, area->y1, area->x2, area->y2);
//     
//     SPI_DC_Data();
//     SPI_CS_Low();
//     
//     uint16_t *pixels = (uint16_t *)color_p;
//     for (uint32_t i = 0; i < width * height; i++) {
//         uint16_t pixel = pixels[i];
//         SPI_WriteByte(pixel >> 8);
//         SPI_WriteByte(pixel & 0xFF);
//     }
//     
//     SPI_CS_High();
//     
//     lv_disp_flush_ready(disp_drv);
// }// 

// void LVGL_Init(void) {
//     lv_init();
//     
//     lv_disp_draw_buf_init(&disp_buf, lvgl_buf1, lvgl_buf2, SCREEN_WIDTH * 10);
//     
//     lv_disp_drv_init(&disp_drv);
//     disp_drv.hor_res = SCREEN_WIDTH;
//     disp_drv.ver_res = SCREEN_HEIGHT;
//     disp_drv.flush_cb = lvgl_flush_cb;
//     disp_drv.draw_buf = &disp_buf;
//     lv_disp_drv_register(&disp_drv);
// }// 

// lv_disp_drv_t* LVGL_GetDisplayDriver(void) {
//     return &disp_drv;
// }


/* ========== lvgl_init.c ========== */
#include "lvgl_init.h"
#include "../hardware/tft_ili9341.h"
#include "../hardware/spi_interface.h"
#include "../config/app_config.h"

/* LVGL Display Buffers - Larger for smoother rendering */
static lv_color_t lvgl_buf1[SCREEN_WIDTH * LVGL_BUFFER_LINES];
static lv_color_t lvgl_buf2[SCREEN_WIDTH * LVGL_BUFFER_LINES];
static lv_disp_drv_t disp_drv;
static lv_disp_draw_buf_t disp_buf;

/* LVGL Display Flush Callback - OPTIMIZED BUT STABLE */
static void lvgl_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    uint16_t width = area->x2 - area->x1 + 1;
    uint16_t height = area->y2 - area->y1 + 1;
    uint32_t size = width * height;
    
    TFT_SetAddressWindow(area->x1, area->y1, area->x2, area->y2);
    
    SPI_DC_Data();
    SPI_CS_Low();
    
    uint16_t *pixels = (uint16_t *)color_p;
    
    // Optimized but stable: wait every few pixels
    for (uint32_t i = 0; i < size; i++) {
        uint16_t pixel = pixels[i];
        
        // Send high byte
        DL_SPI_transmitData8(TFT_SPI_INST, pixel >> 8);
        while (DL_SPI_isBusy(TFT_SPI_INST));
        
        // Send low byte
        DL_SPI_transmitData8(TFT_SPI_INST, pixel & 0xFF);
        while (DL_SPI_isBusy(TFT_SPI_INST));
    }
    
    SPI_CS_High();
    
    lv_disp_flush_ready(disp_drv);
}

void LVGL_Init(void) {
    lv_init();
    
    lv_disp_draw_buf_init(&disp_buf, lvgl_buf1, lvgl_buf2, SCREEN_WIDTH * LVGL_BUFFER_LINES);
    
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);
}

lv_disp_drv_t* LVGL_GetDisplayDriver(void) {
    return &disp_drv;
}
