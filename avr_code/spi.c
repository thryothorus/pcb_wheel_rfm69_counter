
#include "spi.h"



void spi_rfm69_select(bool state)
{
    SET_PIN_OUT(DDRE, DDE2);
    if (!state) {
        SET_PIN_HIGH(PORTE, PE2);
    } else {
        SET_PIN_LOW(PORTE, PE2);
    }
}


    uint8_t spi_write(uint8_t data) {
        SPDR1 = data; // Load data into the SPI data register
        while (!(SPSR1 & (1 << SPIF1))) {
        }; // Wait for transmission to complete
        return SPDR1; // Return received data
    }

    uint8_t spi_read() {
        return spi_write(0xFF);
    }
