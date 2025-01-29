#include "m95128.h"

uint8_t read_value;
uint8_t old_last_page;
uint8_t new_last_page;
void spi_eeprom_select(bool state)
{
    SET_PIN_OUT(DDRB, DDB0);
    if (!state) {
        SET_PIN_HIGH(PORTB, PB0);
    } else {
        SET_PIN_LOW(PORTB, PB0);
    }
}

void eeprom_write(uint8_t page, unsigned const char* msg, uint8_t msg_len)
{
    spi_rfm69_select(false);

    spi_eeprom_select(true);
    spi_write(EEPROM_WREN);
    spi_eeprom_select(false);

    spi_eeprom_select(true);
    spi_write(EEPROM_WRITE);
    write_page_address(page);

    for (int i = 0; i < msg_len; i++) {
        spi_write(msg[i]);
    }

    spi_eeprom_select(false);

    spi_eeprom_select(true);
    spi_write(EEPROM_WRDI);
    spi_eeprom_select(false);

    while (1) {
        spi_eeprom_select(true);
        spi_write(EEPROM_RDSR);
        read_value = spi_read();
        spi_eeprom_select(false);
        if (read_value == 0x00) {
            return;
        }
    };
}

void eeprom_read(uint8_t page, unsigned char* msg, uint8_t msg_len)
{

    spi_eeprom_select(true);
    spi_write(EEPROM_WRDI);
    spi_eeprom_select(false);

    spi_eeprom_select(true);
    spi_write(EEPROM_READ);
    write_page_address(page);

    for (int i = 0; i < msg_len; i++) {
        msg[i] = spi_read();
    }
    spi_eeprom_select(false);
}

void delete_last_page()
{
    old_last_page = get_last_page();
    if (old_last_page == 0) // If we have nothing, no need to delete anything
    {
        return;
    }
    new_last_page = old_last_page - 1;
    write_last_page_value(new_last_page);
    eeprom_clear_page(old_last_page);
}

uint8_t get_last_page()
{
    memset(DATA_BUFFER_65, 0, 1);
    eeprom_read(0, DATA_BUFFER_65, 1);
    return (uint8_t)DATA_BUFFER_65[0];
}

void write_last_page_value(uint8_t page)
{
    DATA_BUFFER_7[0] = page;
    eeprom_write(0, DATA_BUFFER_7, 1);
}

void write_page_address(uint8_t page)
{
    uint16_t addr = page * 0x40; // Each page starts at 64 byte intervals.  And 64 byte is 0x40 or
                                 // 0b01000000;
    spi_write((addr >> 8) & 0xFF);
    spi_write(addr & 0xFF);
}

void eeprom_write_tx_data(uint8_t page, tx_rx_data_struct tx_data_in)
{
    if (page == 0) {
        return;
    }
    memset(DATA_BUFFER_65, ' ', 64);
    DATA_BUFFER_65[64] = '\0';
    memcpy(DATA_BUFFER_65, tx_data_in.msg, 60);
    DATA_BUFFER_65[60] = tx_data_in.flags;
    DATA_BUFFER_65[61] = tx_data_in.from;
    DATA_BUFFER_65[62] = tx_data_in.to;
    DATA_BUFFER_65[63] = tx_data_in.dtype;

    eeprom_write(page, DATA_BUFFER_65, 64);
}

tx_rx_data_struct eeprom_read_tx_data(uint8_t page)
{
    reset_txrx_struct(&TX_DATA);
    memset(DATA_BUFFER_65, ' ', 64);
    DATA_BUFFER_65[64] = '\0';
    eeprom_read(page, DATA_BUFFER_65, 64);
    memcpy(TX_DATA.msg, DATA_BUFFER_65, 60);
    TX_DATA.flags = DATA_BUFFER_65[60];
    TX_DATA.from = DATA_BUFFER_65[61];
    TX_DATA.to = DATA_BUFFER_65[62];
    TX_DATA.dtype = DATA_BUFFER_65[63];
    TX_DATA.len = 60;
    return TX_DATA;
}

tx_rx_data_struct read_struct_last_page()
{
    uint8_t page_num = get_last_page();
    return eeprom_read_tx_data(page_num);
}

void write_struct_to_last_page(tx_rx_data_struct tx_data_in)
{
    uint8_t page_val = get_last_page();
    uint8_t next_page_val;
    if (page_val == 255) {
        next_page_val = 1;
    } else {
        next_page_val = page_val + 1;
    }

    eeprom_write_tx_data(next_page_val, tx_data_in);
    write_last_page_value(next_page_val);
}

void eeprom_clear_page(uint8_t page)
{
    memset(DATA_BUFFER_65, ' ', 64);
    eeprom_write(page, DATA_BUFFER_65, 64);
}
