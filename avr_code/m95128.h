/*
 * File:   spi.h
 * Author: thebears
 *
 * Created on December 6, 2024, 11:02 AM
 */
#include "defines.h"
#include "rfm69.h"
#include "spi.h"
#include "states.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

#ifndef M95128__H
#define M95128__H

#define EEPROM_WREN 0b00000110 // 0x06
#define EEPROM_WRDI 0b00000100 // 0x04
#define EEPROM_RDSR 0b00000101 // 0x05
#define EEPROM_WRSR 0b00000001 // 0x01
#define EEPROM_READ 0b00000011 // 0x03
#define EEPROM_WRITE 0b00000010 // 0x02
#define EEPROM_RDID 0b10000011 // 0x83
#define EEPROM_WRID 0b10000010 // 0x82
#define EEPROM_RDLS 0b10000011 // 0x83
#define EEPROM_LID 0b10000010 // 0x82
#define PAGE_SIZE 64
#ifdef __cplusplus
extern "C" {
w
#endif

    void
    spi_eeprom_select(bool state);
void eeprom_write(uint8_t page, char* msg, uint8_t msg_len);
void eeprom_read(uint8_t page, char* msg, uint8_t msg_len);
void eeprom_write_tx_data(uint8_t page, tx_rx_data_struct tx_data);
void write_page_address(uint8_t page);
uint8_t get_last_page();
tx_rx_data_struct eeprom_read_tx_data(uint8_t page);
void delete_last_page();
uint8_t get_last_page();
uint8_t write_last_page_value(uint8_t page);
void eeprom_clear_page(uint8_t page);
void write_page_address(uint8_t page);
void eeprom_write_tx_data(uint8_t page, tx_rx_data_struct tx_data);
void write_struct_to_last_page(tx_rx_data_struct tx_data);
tx_rx_data_struct read_struct_last_page();
#ifdef __cplusplus
}
#endif

#endif /* M95128__H */
