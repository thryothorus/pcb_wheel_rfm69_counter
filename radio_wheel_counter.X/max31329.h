/* 
 * File:   max31329.h
 * Author: thebears
 *
 * Created on December 18, 2024, 1:24 PM
 */

#include "i2c.h"
#define I2C_ADDR 0x68

#ifndef MAX31329_H
#define	MAX31329_H

#ifdef	__cplusplus
extern "C" {
#endif


#define DEC2BCD(n) ( n + 6 * (n / 10) )
#define BCD2DEC(n) (n - 6 * (n >> 4))
#define  tmYearToY2k(Y)      ((Y) - 30)    // offset is from 2000
#define  y2kYearToTm(Y)      ((Y) + 30)

    typedef struct {
        uint8_t Second; // 0-59
        uint8_t Minute; // 0-59
        uint8_t Hour; // 0-23
        uint8_t Wday; // Day of week, 1-7 (1 = Sunday)
        uint8_t Day; // 1-31
        uint8_t Month; // 1-12
        uint8_t Year; // Full year (e.g., 2024)
    } time_struct;

    extern uint8_t data[7];
    extern time_struct time_data;
    uint8_t rtc_enable_interrupts();
    uint8_t rtc_set_per_minute_alarm();
    uint8_t rtc_read_time_array(uint8_t *data);
    time_struct rtc_read_time();
    uint8_t rtc_write_time(time_struct tm);
    uint8_t rtc_set_alarm_config();
    uint8_t rtc_read_status_register();
    uint8_t rtc_read_interrupt_register();
    uint8_t rtc_read_register(uint8_t addr);

#ifdef	__cplusplus
}
#endif

#endif	/* MAX31329_H */

