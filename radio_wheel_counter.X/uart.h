/* 
 * File:   uart.h
 * Author: thebears
 *
 * Created on December 6, 2024, 11:16 AM
 */

#include "defines.h"
#define UBRR_BAUD F_CPU/16/BAUD-1
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>



#ifndef UART_H
#define	UART_H


#ifdef	__cplusplus
extern "C" {
#endif


    extern char array_internal[16];
    extern char binary_string[9];

    void uart_init();
    void uart_sendChar(char c);
    void uart_sendString(const char *str);
    void uart_print_uint16(uint16_t meas, const char* buf);
    void uart_print_hex(unsigned char vin, const char* buf);
    void uart_print_hex_bin(unsigned char vin, const char* buf);
    void uart_print_float(float meas, const char* buf);
    void uart_print_binary(unsigned char vin, const char* buf);
    void uart_print_uint8(uint8_t vin, const char* buf);







#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

