// #ifndef UART_C
// #define	UART_C

#include "uart.h"

char output_buffer[512];
char array_internal[16];
char binary_string[9];

void uart_wait_until_sent()
{
    while (!(UCSR0A & (1 << TXC0))) { }
    UCSR0A |= (1 << TXC0);
}

void uart_print_uint8_array(uint8_t* array, size_t length, const char* buf)
{
    size_t pos = 0; // Track the current position in the buffer
    size_t buffer_size = 128;

    //    pos = snprintf(output_buffer + pos, buffer_size - pos, "["); // Start with an opening
    //    bracket

    uart_sendChar('[');
    for (size_t i = 0; i < length; i++) {
        //            uart_sendString("   ");
        snprintf(array_internal, sizeof(array_internal), "%u", array[i]);

        uart_sendString(array_internal);
        if (i < length - 1) {
            uart_sendString(",");
        }
        //        pos += snprintf(output_buffer + pos, buffer_size - pos, "%u", array[i]); // Add
        //        each number if (i < length - 1) {
        //            pos += snprintf(output_buffer + pos, buffer_size - pos, ", "); // Add a comma
        //            and space if not the last
        //        }
    }

    uart_sendChar(']');
    //    snprintf(output_buffer + pos, buffer_size - pos, "]"); // Add the closing bracket
    //    uart_sendString(output_buffer);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_init()
{
    UBRR0H = (unsigned char)((UBRR_BAUD) >> 8);
    UBRR0L = (unsigned char)(UBRR_BAUD);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_sendChar(char c)
{
    while (!(UCSR0A & (1 << UDRE0))) { }
    UDR0 = c;
}

void uart_sendStringArray(char str[], uint8_t len)
{
    for (uint8_t idx = 0; idx < len; idx++) {
        uart_sendChar(str[idx]);
    }
}
void uart_sendString(const char* str)
{
    while (*str) {
        uart_sendChar(*str++);
    }
}

void uart_print_uint16(uint16_t meas, const char* buf)
{
    snprintf(array_internal, sizeof(array_internal), "%u", meas);
    uart_sendString("   ");
    uart_sendString(array_internal);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_print_float(float meas, const char* buf)
{
    dtostrf(meas, 3, 4, array_internal);
    uart_sendString("   ");
    uart_sendString(array_internal);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

char HexLookUp[] = "0123456789abcdef";

void bytes2hex(unsigned char* src, char* out, int len)
{
    while (len--) {
        *out++ = HexLookUp[*src >> 4];
        *out++ = HexLookUp[*src & 0x0F];
        src++;
    }
    *out = 0;
}

void uart_print_binary_hex(unsigned char vin, unsigned char buf)
{
    char hex_buff[3];
    bytes2hex(&buf, hex_buff, sizeof(buf));

    uart_sendString("   ");
    binary_string[8] = '\0'; // Null-terminate the string

    for (int i = 0; i < 8; i++) {
        binary_string[7 - i] = (vin & (1 << i)) ? '1' : '0';
    }
    uart_sendString(binary_string);

    uart_sendString(" 0x");
    uart_sendString(hex_buff);
    uart_sendString("\r\n");
}

void uart_print_hex(unsigned char vin, const char* buf)
{
    char hex_buff[3];
    bytes2hex(&vin, hex_buff, sizeof(vin));
    uart_sendString("   0x");

    uart_sendString(hex_buff);

    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_print_hex_bin(unsigned char vin, const char* buf)
{
    char hex_buff[3];
    bytes2hex(&vin, hex_buff, sizeof(vin));
    uart_sendString("   0x");

    uart_sendString(hex_buff);

    uart_sendString("    ");

    binary_string[8] = '\0'; // Null-terminate the string
    for (int i = 0; i < 8; i++) {
        binary_string[7 - i] = (vin & (1 << i)) ? '1' : '0';
    }
    uart_sendString(binary_string);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_print_binary(unsigned char vin, const char* buf)
{
    uart_sendString("   ");
    binary_string[8] = '\0'; // Null-terminate the string
    for (int i = 0; i < 8; i++) {
        binary_string[7 - i] = (vin & (1 << i)) ? '1' : '0';
    }
    uart_sendString(binary_string);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_print_uint8(uint8_t vin, const char* buf)
{

    uart_sendString("   ");
    snprintf(array_internal, sizeof(array_internal), "%u", vin);

    uart_sendString(array_internal);
    uart_sendString(" ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}
