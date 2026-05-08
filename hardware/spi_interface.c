/* ========== spi_interface.c ========== */
#include "spi_interface.h"

void SPI_Init(void) {
    // Set initial pin states
    SPI_CS_High();
    SPI_DC_Data();
    DL_GPIO_setPins(TFT_RESET_PORT, TFT_RESET_PIN);
    //setting divider value to 0 for more fps
    DL_SPI_setBitRateSerialClockDivider(TFT_SPI_INST, 0);
    DL_SPI_enable(TFT_SPI_INST);
}

void SPI_WriteByte(uint8_t data) {
    DL_SPI_transmitData8(TFT_SPI_INST, data);
    while (DL_SPI_isBusy(TFT_SPI_INST));
}

void SPI_CS_Low(void) {
    DL_GPIO_clearPins(TFT_CS_PORT, TFT_CS_PIN);
}

void SPI_CS_High(void) {
    DL_GPIO_setPins(TFT_CS_PORT, TFT_CS_PIN);
}

void SPI_DC_Command(void) {
    DL_GPIO_clearPins(TFT_DC_PORT, TFT_DC_PIN);
}

void SPI_DC_Data(void) {
    DL_GPIO_setPins(TFT_DC_PORT, TFT_DC_PIN);
}

void SPI_WriteDataBulk(uint8_t *data, uint32_t len) {
    SPI_DC_Data();
    SPI_CS_Low();
    for (uint32_t i = 0; i < len; i++) {
        SPI_WriteByte(data[i]);
    }
    SPI_CS_High();
}