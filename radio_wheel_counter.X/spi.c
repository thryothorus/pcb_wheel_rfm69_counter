
#include "spi.h"





    uint8_t spi_write(uint8_t data) {
        SPDR1 = data; // Load data into the SPI data register
        while (!(SPSR1 & (1 << SPIF1))) {
        }; // Wait for transmission to complete
        return SPDR1; // Return received data
    }

    uint8_t spi_read() {
        return spi_write(0xFF);
    }
