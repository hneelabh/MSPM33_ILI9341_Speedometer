/* ========== spi_interface.h ========== */
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../config/app_config.h"

/* Initialize SPI hardware */
void SPI_Init(void);

/* Low-level pin control */
void SPI_CS_Low(void);
void SPI_CS_High(void);
void SPI_DC_Command(void);
void SPI_DC_Data(void);

/* Data transmission */
void SPI_WriteByte(uint8_t data);
void SPI_WriteDataBulk(uint8_t *data, uint32_t len);

#endif /* SPI_INTERFACE_H */