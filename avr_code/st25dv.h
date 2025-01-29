#include "i2c.h"
#include "defines.h"
#include "ndef.h"
#include "states.h"
#include <stdbool.h>
#include "rfm69.h"
#include <util/delay.h>
#ifndef ST25DV_H
#define ST25DV_H



#define I2C_SYSTEM_ADDR 0x57
#define I2C_USER_ADDR 0x53

identifier_results get_nugget_data();
ndef_message rfid_read_first_ndef_entry();
void rfid_set_low_power_down(bool state);
void rfid_set_i2c_power(bool state);
uint8_t rfid_read_memory(uint8_t* data, uint8_t num_bytes, uint16_t address);
uint8_t rfid_read_system_register();

trimmed_string_struct remove_spaces(char* str, uint8_t len_str);

#endif