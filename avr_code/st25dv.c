#include "st25dv.h"

trimmed_string_struct trimmed_string;
identifier_results id_result;
trimmed_string_struct string_trim_result;

identifier_results get_nugget_data()
{
    ndef_message rfid_msg = rfid_read_first_ndef_entry();

    uart_sendString(rfid_msg.payload);
    uart_sendString("\r\n");
    
    string_trim_result = remove_spaces(rfid_msg.payload, rfid_msg.payload_len);
    uart_sendString(string_trim_result.str);
    uart_sendString("\r\n");
    char* delim_ptr = strchr(string_trim_result.str, ',');
    if (delim_ptr != NULL) {
        uint8_t index_comma = delim_ptr - string_trim_result.str;
        memcpy(id_result.name_str, string_trim_result.str, index_comma);
        memcpy(
            id_result.diameter_str, string_trim_result.str + index_comma + 1,
            string_trim_result.length);
        id_result.name_len = index_comma;
        id_result.diameter_len = string_trim_result.length - index_comma;
    } else {
        memcpy(id_result.name_str, string_trim_result.str, string_trim_result.length);
        id_result.name_len = string_trim_result.length;
        memcpy(id_result.diameter_str, "N/A", 3);
        id_result.diameter_len = 3;
    }
    
    id_result.hashed = hash(id_result.name_str, 0, 59);

    return id_result;
}

trimmed_string_struct remove_spaces(char* str, uint8_t len_str)
{
    uint8_t i = 0, j = 0;
    memset(trimmed_string.str,' ',20);
    while (str[i]) {
        if (str[i] != ' ') {
            trimmed_string.str[j++] = str[i];
        }
        i++;
        if (i >= len_str) {
            break;
        }
    }
    
    trimmed_string.length = j;
    return trimmed_string;
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
    uint8_t mem_data[254];
    rfid_read_memory(mem_data, 254, 0x0000 + 4);
    ndef_message the_msg = readNDEFText(mem_data);
    rfid_set_low_power_down(true);
    return the_msg;
    rfid_set_i2c_power(false);
}

uint8_t rfid_read_system_register()
{
    return read_one_byte_16bit_addr_no_err_register(I2C_SYSTEM_ADDR, 0x0000);
    //    0xAE
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
