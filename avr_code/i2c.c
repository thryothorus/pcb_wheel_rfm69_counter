#include "i2c.h"
#include <util/twi.h>

void i2c_init() {
    // Set SCL and SDA as inputs (automatically done by TWI hardware)
    TWSR = 0; // Prescaler = 1
    TWBR = (uint8_t) ((F_CPU / F_SCL - 16) / 2); // Set bitrate register
    TWCR = (1 << TWEN);
}

// Start i2c communication

uint8_t i2c_start(uint8_t address) {
    TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN); // Send START condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
    TWDR = address; // Load address into data register

    TWCR = (1 << TWINT) | (1 << TWEN); // Send address
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
    uint8_t status = TWSR & 0xF8;
    if (status != 0x18 && status != 0x40) return 1;
    return 0;
    //    return (TWSR & 0xF8); // Return the status code (check if ACK received)
}

// Stop i2c communication

void i2c_stop() {
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); // Send STOP condition
    while (!(TWCR & (1 << TWSTO))); // Wait for STOP to complete
}

uint8_t i2c_read_ack() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
    return TWDR;
}


uint8_t i2c_write(uint8_t data) {
    // Load data into TWDR
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));  // Wait for TWINT flag set
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK) return 1;  // Check ACK
    return 0;
}

uint8_t i2c_read_nack() {
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag to be set
    return TWDR;
}

// // Scan all i2c addresses (7-bit addressing)

// void i2c_scan() {
//     USART0_sendString("\r\ni2c Device Scan:\r\n");

//     for (uint8_t address = 1; address < 128; address++) {
//         uint8_t status = i2c_start(address << 1); // Shift address and start communication
//         if (status == 0x18 || status == 0x40) {
//             // If we received an ACK (0x18: Master Transmitter, 0x40: Master Receiver)
//             char buffer[32];
//             snprintf(buffer, sizeof (buffer), "\tDevice found at 0x%02X\r\n", address);
//             USART0_sendString(buffer);
//         }
//         i2c_stop(); // Always stop after each address
//     }

//     USART0_sendString("Scan complete.\r\n\r\n");
// }