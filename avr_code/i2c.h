#include "defines.h"
#include <avr/io.h>
#ifndef i2c_H
#define i2c_H


#define TWSR TWSR0
#define TWDR TWDR0
#define TWBR TWBR0
#define TWCR TWCR0




void i2c_init();
uint8_t i2c_start(uint8_t address);
void i2c_stop();
void i2c_scan();
uint8_t i2c_read_ack();
uint8_t i2c_read_nack();
uint8_t i2c_write(uint8_t data);


#endif