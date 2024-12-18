/* 
 * File:   spi.h
 * Author: thebears
 *
 * Created on December 6, 2024, 11:02 AM
 */
#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "states.h"

#ifndef M95128__H
#define	M95128__H

#define EEPROM_WREN     0b00000110 // 0x06
#define EEPROM_WRDI     0b00000100 // 0x04
#define EEPROM_RDSR     0b00000101 // 0x05
#define EEPROM_WRSR     0b00000001 // 0x01
#define EEPROM_READ     0b00000011 // 0x03
#define EEPROM_WRITE    0b00000010 // 0x02
#define EEPROM_RDID     0b10000011 // 0x83
#define EEPROM_WRID     0b10000010 // 0x82
#define EEPROM_RDLS     0b10000011 // 0x83
#define EEPROM_LID      0b10000010 // 0x82
#ifdef	__cplusplus
extern "C" {
#endif


    void spi_eeprom_select(bool state);

#ifdef	__cplusplus
}
#endif

#endif	/* M95128__H */

