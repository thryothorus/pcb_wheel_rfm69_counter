/*
 * File:   uart.h
 * Author: thebears
 *
 * Created on December 6, 2024, 11:16 AM
 */

#include "defines.h"
#define UBRR_BAUD F_CPU / 16 / BAUD - 1

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif

void uart_init();
void uart_sendChar(char c);
void uart_sendString(const char* str);
void uart_sendStringArray(unsigned char str[], uint8_t len);
void uart_print_uint16(uint16_t meas, const char* buf);
void uart_print_hex(unsigned char vin, const char* buf);
void uart_print_hex_bin(unsigned char vin, const char* buf);
void uart_print_binary_hex(unsigned char vin, unsigned char buf);
void uart_print_float(float meas, const char* buf);
void uart_print_binary(unsigned char vin, const char* buf);
void uart_print_uint8(uint8_t vin, const char* buf);
void uart_print_uint8_array(uint8_t* array, size_t length, const char* buf);
void uart_wait_until_sent();

#ifdef __cplusplus
}
#endif

#endif /* UART_H */
