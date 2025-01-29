#include "defines.h"
#include <avr/io.h>

#define I2C_START_WRITE(device_addr)                                           \
    {                                                                          \
        if (i2c_start((device_addr << 1) | 0x00)) {                            \
            return 1;                                                          \
        }                                                                      \
    }

#define I2C_START_READ(device_addr)                                            \
    {                                                                          \
        if (i2c_start((device_addr << 1) | 0x01)) {                            \
            return 1;                                                          \
        }                                                                      \
    }

#ifndef i2c_H
#define i2c_H

#define TWSR TWSR0
#define TWDR TWDR0
#define TWBR TWBR0
#define TWCR TWCR0

void i2c_init();
uint8_t i2c_start(uint8_t address);

uint8_t write_one_byte(uint8_t device_addr, uint8_t register_addr,
                       uint8_t data);
uint8_t write_n_bytes(uint8_t device_addr, uint8_t register_addr, uint8_t *data,
                      uint8_t n_bytes);

uint8_t read_one_byte_16bit_addr_no_err_register(uint8_t device_addr, uint16_t register_addr);
uint8_t read_one_byte_16bit_addr(uint8_t device_addr, uint16_t register_addr,
                      uint8_t *data);
uint8_t read_n_bytes_16bit_addr(uint8_t device_addr, uint16_t register_addr, uint8_t *data,
                     uint8_t n_bytes);


uint8_t read_one_byte_no_err_register(uint8_t device_addr, uint8_t register_addr);
uint8_t read_one_byte(uint8_t device_addr, uint8_t register_addr,
                      uint8_t *data);
uint8_t read_n_bytes(uint8_t device_addr, uint8_t register_addr, uint8_t *data,
                     uint8_t n_bytes);

void i2c_stop();
void i2c_scan();
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();
uint8_t i2c_write(uint8_t data);

#endif