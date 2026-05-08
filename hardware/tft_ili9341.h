/* ========== tft_ili9341.h ========== */
#ifndef TFT_ILI9341_H
#define TFT_ILI9341_H

#include <stdint.h>

/* Initialize the ILI9341 display */
void TFT_Init(void);

/* Set drawing window */
void TFT_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

#endif /* TFT_ILI9341_H */