/* 
 * File:   defines.h
 * Author: thebears
 *
 * Created on December 18, 2024, 11:41 AM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "stdint.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000UL  // 16 MHz clock speed
#define BAUD 38400
#define F_SCL 200000UL

#define DO_UART true

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

extern unsigned char DATA_BUFFER_65[64];
extern uint8_t DATA_BUFFER_7[7];
extern uint8_t DATA_BUFFER_254[254];
extern unsigned char DATA_BUFFER_20[20];

typedef struct {
    uint8_t payload_len;
    char payload[255];
    uint8_t success;
} ndef_message;
extern ndef_message NDEF_MSG;

typedef struct {
    char str[21]; // Pointer to the modified string
    size_t length; // Length of the modified string
} trimmed_string_struct;
extern trimmed_string_struct TRIMMED_STRING;

typedef struct {
    uint8_t name_len;
    char name_str[128];
    char diameter_str[128];
    uint8_t diameter_len;
    uint8_t hashed;
} identifier_results;
extern identifier_results IDENTIFIER;


typedef struct {
    uint8_t len;
    uint8_t to;
    uint8_t from;
    uint8_t dtype;
    uint8_t flags;
    unsigned char msg[60];
} tx_rx_data_struct;
extern tx_rx_data_struct TX_DATA;
extern tx_rx_data_struct RX_DATA;

typedef struct {
    uint8_t Second; // 0-59
    uint8_t Minute; // 0-59
    uint8_t Hour;   // 0-23
    uint8_t Wday;   // Day of week, 1-7 (1 = Sunday)
    uint8_t Day;    // 1-31
    uint8_t Month;  // 1-12
    uint8_t Year;   // Full year (e.g., 2024)
} time_struct;
extern time_struct TIME;


typedef enum {
    RTC_RFM69_SET_TIME_SUCCESS = 1,
    RTC_RFM69_SET_TIME_FAILED = 2,
} RTC_RFM69_STATUS;


typedef enum // Goes into ID
{ DATA_SEND_SUCCESS = 1,
  DATA_NOT_SENT = 2 } DATA_SEND_STATUS;
    

typedef enum // Goes into ID
{ MSG_TYPE_STRING = 1,
  MSG_TYPE_BINARY = 2 } MSG_DATA_TYPE;

typedef enum // Goes into flags
{ MSG_REQ_CTIME = 1,
  MSG_RESP_CTIME = 2,
  MSG_SEND_COUNTS = 31,
  MSG_RECV_COUNTS_SUCCESS = 32,
  MSG_RECV_COUNTS_FAIL = 33,
  MSG_RESENT_COUNTS = 34} MSG_REQUEST_TYPE_FLAG;

  

#define WHILE_BREAK(counter, attempts)      \
    counter+=1;                             \
    if ((counter+1) > attempts) {  break;};     

#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

