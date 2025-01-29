/*
 * File:   max31329.h
 * Author: thebears
 *
 * Created on December 18, 2024, 1:24 PM
 */

#include "defines.h"
#include "i2c.h"
#include "rfm69.h"
#include "st25dv.h"
#include "uart.h"
#define I2C_ADDR 0x68

#ifndef MAX31329_H
#define MAX31329_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEC2BCD(n) (n + (6 * (n / 10)))
#define BCD2DEC(n) (n - (6 * (n >> 4)))

#define tmYearToY2k(Y) ((Y) - 30) // offset is from 2000
#define y2kYearToTm(Y) ((Y) + 30)

uint8_t rtc_enable_interrupts();
uint8_t rtc_set_per_minute_alarm();
uint8_t rtc_read_time_array(uint8_t* data);
time_struct rtc_read_time();
uint8_t rtc_write_time(time_struct tm);
uint8_t rtc_set_alarm_config();
uint8_t rtc_read_status_register();
uint8_t rtc_read_interrupt_register();
uint8_t rtc_read_register(uint8_t addr);
void uart_print_rtc_time(time_struct td);
RTC_RFM69_STATUS set_time_from_rfm69(identifier_results id_data);

#ifdef __cplusplus
}
#endif

#endif /* MAX31329_H */
