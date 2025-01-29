#include "i2c.h"
#include <util/twi.h>

void i2c_init()
{
    // Set SCL and SDA as inputs (automatically done by TWI hardware)
    TWSR = 0; // Prescaler = 1
    TWBR = (uint8_t)((F_CPU / F_SCL - 16) / 2); // Set bitrate register
    TWCR = (1 << TWEN);
}

// Start i2c communication
uint8_t i2c_start(uint8_t address)
{
    TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN); // Send START condition
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT flag to be set
    TWDR = address; // Load address into data register

    TWCR = (1 << TWINT) | (1 << TWEN); // Send address
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT flag to be set
    uint8_t status = TWSR & 0xF8;
    if (status != 0x18 && status != 0x40)
        return 1;
    return 0;
    //    return (TWSR & 0xF8); // Return the status code (check if ACK
    //    received)
}

uint8_t write_one_byte(uint8_t device_addr, uint8_t register_addr, uint8_t data)
{
    return write_n_bytes(device_addr, register_addr, &data, 1);
}

uint8_t write_n_bytes(uint8_t device_addr, uint8_t register_addr, uint8_t* data, uint8_t n_bytes)
{
    I2C_START_WRITE(device_addr);
    i2c_write(register_addr);
    for (uint8_t i = 0; i < n_bytes; i++) {
        i2c_write(data[i]);
    }
    i2c_stop();
    return 0;
}

uint8_t read_one_byte_no_err_register(uint8_t device_addr, uint8_t register_addr)
{
    uint8_t data;
    read_one_byte(device_addr, register_addr, &data);
    return data;
}

uint8_t read_one_byte(uint8_t device_addr, uint8_t register_addr, uint8_t* data)
{
    return read_n_bytes(device_addr, register_addr, data, 1);
}

uint8_t read_n_bytes(uint8_t device_addr, uint8_t register_addr, uint8_t* data, uint8_t n_bytes)
{

    I2C_START_WRITE(device_addr);
    i2c_write(register_addr);
    I2C_START_READ(device_addr);

    for (uint8_t i = 0; i < (n_bytes - 1); i++) {
        data[i] = i2c_read_ack();
    }

    data[n_bytes - 1] = i2c_read_nack();
    i2c_stop();

    return 0;
}

uint8_t read_one_byte_16bit_addr_no_err_register(uint8_t device_addr, uint16_t register_addr)
{
    uint8_t data;
    read_one_byte_16bit_addr(device_addr, register_addr, &data);
    return data;
}

uint8_t read_one_byte_16bit_addr(uint8_t device_addr, uint16_t register_addr, uint8_t* data)
{
    return read_n_bytes_16bit_addr(device_addr, register_addr, data, 1);
}

uint8_t
read_n_bytes_16bit_addr(uint8_t device_addr, uint16_t register_addr, uint8_t* data, uint8_t n_bytes)
{

    I2C_START_WRITE(device_addr);
    //    i2c_write(0xAE);
    i2c_write(register_addr >> 8);
    i2c_write(register_addr & 0xFF);
    I2C_START_READ(device_addr);

    for (uint8_t i = 0; i < (n_bytes - 1); i++) {
        data[i] = i2c_read_ack();
    }

    data[n_bytes - 1] = i2c_read_nack();
    i2c_stop();

    return 0;
}

// Stop i2c communication
void i2c_stop()
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); // Send STOP condition
    while (!(TWCR & (1 << TWSTO)))
        ; // Wait for STOP to complete
}

uint8_t i2c_read_ack()
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT flag to be set
    return TWDR;
}

uint8_t i2c_write(uint8_t data)
{
    // Load data into TWDR
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT flag set
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
        return 1; // Check ACK
    return 0;
}

uint8_t i2c_read_nack()
{
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)))
        ; // Wait for TWINT flag to be set
    return TWDR;
}