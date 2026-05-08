/* ========== tft_ili9341.c ========== */
#include "tft_ili9341.h"
#include "spi_interface.h"
#include <ti/devices/msp/msp.h>
#include "../config/app_config.h"

/* ILI9341 Command Definitions */
#define CMD_SWRESET     0x01
#define CMD_SLPOUT      0x11
#define CMD_DISPON      0x29
#define CMD_CASET       0x2A
#define CMD_PASET       0x2B
#define CMD_RAMWR       0x2C
#define CMD_MADCTL      0x36
#define CMD_PIXFMT      0x3A
#define CMD_PWCTR1      0xC0
#define CMD_PWCTR2      0xC1
#define CMD_VMCTR1      0xC5
#define CMD_VMCTR2      0xC7
#define CMD_FRMCTR1     0xB1
#define CMD_DFUNCTR     0xB6
#define CMD_GMCTRP1     0xE0
#define CMD_GMCTRN1     0xE1

static void TFT_WriteCommand(uint8_t cmd) {
    SPI_DC_Command();
    SPI_CS_Low();
    SPI_WriteByte(cmd);
    SPI_CS_High();
}

static void TFT_WriteData(uint8_t data) {
    SPI_DC_Data();
    SPI_CS_Low();
    SPI_WriteByte(data);
    SPI_CS_High();
}

static void TFT_HardwareReset(void) {
    DL_GPIO_clearPins(TFT_RESET_PORT, TFT_RESET_PIN);
    delay_cycles(32000 * 10);
    DL_GPIO_setPins(TFT_RESET_PORT, TFT_RESET_PIN);
    delay_cycles(32000 * 120);
}

void TFT_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint8_t xData[4] = {x0 >> 8, x0 & 0xFF, x1 >> 8, x1 & 0xFF};
    uint8_t yData[4] = {y0 >> 8, y0 & 0xFF, y1 >> 8, y1 & 0xFF};
    
    TFT_WriteCommand(CMD_CASET);
    SPI_WriteDataBulk(xData, 4);
    
    TFT_WriteCommand(CMD_PASET);
    SPI_WriteDataBulk(yData, 4);
    
    TFT_WriteCommand(CMD_RAMWR);
}

void TFT_Init(void) {
    TFT_HardwareReset();
    
    TFT_WriteCommand(CMD_SWRESET);
    delay_cycles(32000 * 150);
    
    // Power control sequence
    TFT_WriteCommand(0xCB);
    TFT_WriteData(0x39); TFT_WriteData(0x2C); TFT_WriteData(0x00);
    TFT_WriteData(0x34); TFT_WriteData(0x02);
    
    TFT_WriteCommand(0xCF);
    TFT_WriteData(0x00); TFT_WriteData(0xC1); TFT_WriteData(0x30);
    
    TFT_WriteCommand(0xE8);
    TFT_WriteData(0x85); TFT_WriteData(0x00); TFT_WriteData(0x78);
    
    TFT_WriteCommand(0xEA);
    TFT_WriteData(0x00); TFT_WriteData(0x00);
    
    TFT_WriteCommand(0xED);
    TFT_WriteData(0x64); TFT_WriteData(0x03);
    TFT_WriteData(0x12); TFT_WriteData(0x81);
    
    TFT_WriteCommand(0xF7);
    TFT_WriteData(0x20);
    
    TFT_WriteCommand(CMD_PWCTR1);
    TFT_WriteData(0x23);
    
    TFT_WriteCommand(CMD_PWCTR2);
    TFT_WriteData(0x10);
    
    TFT_WriteCommand(CMD_VMCTR1);
    TFT_WriteData(0x3E); TFT_WriteData(0x28);
    
    TFT_WriteCommand(CMD_VMCTR2);
    TFT_WriteData(0x86);
    
    TFT_WriteCommand(CMD_MADCTL);
    TFT_WriteData(0x40);
    
    TFT_WriteCommand(CMD_PIXFMT);
    TFT_WriteData(0x55);
    
    TFT_WriteCommand(CMD_FRMCTR1);
    TFT_WriteData(0x00); TFT_WriteData(0x18);
    
    TFT_WriteCommand(CMD_DFUNCTR);
    TFT_WriteData(0x08); TFT_WriteData(0x82); TFT_WriteData(0x27);
    
    TFT_WriteCommand(0xF2);
    TFT_WriteData(0x00);
    
    TFT_WriteCommand(0x26);
    TFT_WriteData(0x01);
    
    // Gamma correction
    TFT_WriteCommand(CMD_GMCTRP1);
    TFT_WriteData(0x0F); TFT_WriteData(0x31); TFT_WriteData(0x2B);
    TFT_WriteData(0x0C); TFT_WriteData(0x0E); TFT_WriteData(0x08);
    TFT_WriteData(0x4E); TFT_WriteData(0xF1); TFT_WriteData(0x37);
    TFT_WriteData(0x07); TFT_WriteData(0x10); TFT_WriteData(0x03);
    TFT_WriteData(0x0E); TFT_WriteData(0x09); TFT_WriteData(0x00);
    
    TFT_WriteCommand(CMD_GMCTRN1);
    TFT_WriteData(0x00); TFT_WriteData(0x0E); TFT_WriteData(0x14);
    TFT_WriteData(0x03); TFT_WriteData(0x11); TFT_WriteData(0x07);
    TFT_WriteData(0x31); TFT_WriteData(0xC1); TFT_WriteData(0x48);
    TFT_WriteData(0x08); TFT_WriteData(0x0F); TFT_WriteData(0x0C);
    TFT_WriteData(0x31); TFT_WriteData(0x36); TFT_WriteData(0x0F);
    
    TFT_WriteCommand(CMD_SLPOUT);
    delay_cycles(32000 * 120);
    
    TFT_WriteCommand(CMD_DISPON);
    delay_cycles(32000 * 120);
}