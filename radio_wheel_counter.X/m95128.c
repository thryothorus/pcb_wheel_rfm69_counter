#include "m95128.h"
void spi_eeprom_select(bool state)
{
    SET_PIN_OUT(DDRB, DDB0);
    if (!state)
    {
        SET_PIN_HIGH(PORTB, PB0);
    }
    else
    {
        SET_PIN_LOW(PORTB, PB0);
    }
}