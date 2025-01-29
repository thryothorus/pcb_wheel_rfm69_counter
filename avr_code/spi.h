#include <avr/io.h>
#include "defines.h"
#include "states.h"
#include <stdbool.h>
#ifndef SPI_H
#define SPI_H


uint8_t spi_write(uint8_t data);
uint8_t spi_read();
void spi_rfm69_select(bool state);

#endif