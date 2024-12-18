//#ifndef UART_C
//#define	UART_C


#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>



char array_internal[16];
char binary_string[9];

void uart_init() {
    UBRR0H = (unsigned char) ((UBRR_BAUD) >> 8);
    UBRR0L = (unsigned char) (UBRR_BAUD);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_sendChar(char c) {
    while (!(UCSR0A & (1 << UDRE0))) {
    }
    UDR0 = c;
}

void uart_sendString(const char *str) {
    while (*str) {
        uart_sendChar(*str++);
    }

}

void uart_print_uint16(uint16_t meas, const char* buf) {
    snprintf(array_internal, sizeof(array_internal), "%u", meas);
    uart_sendString("   ");
    uart_sendString(array_internal);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_print_float(float meas, const char* buf) {
    dtostrf(meas, 3, 4, array_internal);
    uart_sendString("   ");
    uart_sendString(array_internal);
    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");

}

char HexLookUp[] = "0123456789abcdef";

void bytes2hex(unsigned char *src, char *out, int len) {
    while (len--) {
        *out++ = HexLookUp[*src >> 4];
        *out++ = HexLookUp[*src & 0x0F];
        src++;
    }
    *out = 0;
}

void uart_print_hex(unsigned char vin, const char* buf) {
    char hex_buff[3];
    bytes2hex(&vin, hex_buff, sizeof (vin));
    uart_sendString("   0x");

    uart_sendString(hex_buff);

    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");
}

void uart_print_binary(unsigned char vin, const char* buf) {

    uart_sendString("   ");

    binary_string[8] = '\0'; // Null-terminate the string

    for (int i = 0; i < 8; i++) {
        binary_string[7 - i] = (vin & (1 << i)) ? '1' : '0';
    }
    uart_sendString(binary_string);

    // int binary[9];
    // for (int n = 0; n < 8; n++)
    //     binary[7 - n] = (vin >> n) & 1;


    // char str[1];
    // for (int n = 0; n < 8; n++) {
    //     snprintf(str, sizeof(str), "%d", binary[n]);
    //     uart_sendString(str);
    // }

    uart_sendString("    ");
    uart_sendString(buf);
    uart_sendString("\r\n");

}

void uart_print_uint8(uint8_t vin, const char* buf) {

     
    uart_sendString("   ");
    snprintf(array_internal, sizeof(array_internal), "%u", vin);

    uart_sendString(array_internal);
    uart_sendString(" ");
    uart_sendString(buf);
    uart_sendString("\r\n");

}

