#include "st25dv.h"

identifier_results get_nugget_data()
{
    NDEF_MSG = rfid_read_first_ndef_entry();
    TRIMMED_STRING = remove_spaces(NDEF_MSG.payload, NDEF_MSG.payload_len);
    char* delim_ptr = strchr(TRIMMED_STRING.str, ',');
    if (delim_ptr != NULL) {
        uint8_t index_comma = delim_ptr - TRIMMED_STRING.str;
        memcpy(IDENTIFIER.name_str, TRIMMED_STRING.str, index_comma);
        memcpy(
            IDENTIFIER.diameter_str, TRIMMED_STRING.str + index_comma + 1, TRIMMED_STRING.length);
        IDENTIFIER.name_len = index_comma;
        IDENTIFIER.diameter_len = TRIMMED_STRING.length - index_comma;
    } else {
        memcpy(IDENTIFIER.name_str, TRIMMED_STRING.str, TRIMMED_STRING.length);
        IDENTIFIER.name_len = TRIMMED_STRING.length;
        memcpy(IDENTIFIER.diameter_str, "N/A", 3);
        IDENTIFIER.diameter_len = 3;
    }

    IDENTIFIER.hashed = hash(IDENTIFIER.name_str, 0, 59);

    return IDENTIFIER;
}

trimmed_string_struct remove_spaces(char* str, uint8_t len_str)
{
    uint8_t i = 0, j = 0;
    memset(TRIMMED_STRING.str, ' ', 20);
    while (str[i]) {
        if (str[i] != ' ') {
            TRIMMED_STRING.str[j++] = str[i];
        }
        i++;
        if (i >= len_str) {
            break;
        }
    }

    TRIMMED_STRING.length = j;
    return TRIMMED_STRING;
}

void rfid_set_low_power_down(bool state)
{
    SET_PIN_OUT(DDRD, DDD5);
    if (state) {
        SET_PIN_HIGH(PORTD, PD5);
    } else {
        SET_PIN_LOW(PORTD, PD5);
    }
}

ndef_message rfid_read_first_ndef_entry()
{
    rfid_set_low_power_down(false);
    rfid_set_i2c_power(true);
    _delay_ms(10);
    memset(DATA_BUFFER_254, 0, 254);
    rfid_read_memory(DATA_BUFFER_254, 254, 0x0000 + 4);
    NDEF_MSG = readNDEFText(DATA_BUFFER_254);
    rfid_set_low_power_down(true);
    rfid_set_i2c_power(false);
    return NDEF_MSG;
}

uint8_t rfid_read_system_register()
{
    return read_one_byte_16bit_addr_no_err_register(I2C_SYSTEM_ADDR, 0x0000);
}

void rfid_set_i2c_power(bool state)
{

    SET_PIN_OUT(DDRE, DDE0);
    if (state) {
        SET_PIN_HIGH(PORTE, PE0);
    } else {
        SET_PIN_LOW(PORTE, PE0);
    }
}

uint8_t rfid_read_memory(uint8_t* data, uint8_t num_bytes, uint16_t address)
{
    return read_n_bytes_16bit_addr(I2C_USER_ADDR, address, data, num_bytes);
}
