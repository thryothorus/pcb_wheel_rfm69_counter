/*
 * File:   rfm69.h
 * Author: thebears
 *
 * Created on December 11, 2024, 2:05 PM
 */
#include <avr/io.h>
#include <stdbool.h>
#include "states.h"
#include "spi.h"
#ifndef RFM69_H
#define RFM69_H

#ifdef __cplusplus
extern "C"
{
#endif

// Target frequency is 433 MHz.
// Equation is 32MHz/2^19 = 61.03515625.  433 MHz/61.03515625 = 7094272
// 7094272 = 01101100 01000000 00000000 = 0x6C 0x40 0x00
#define REG_FREQ_MSB 0x07
#define REG_FREQ_MIDDLE_SB 0x08
#define REG_FREQ_LSB 0x09

#define VAL_FREQ_MSB 0x6c
#define VAL_FREQ_MIDDLE_SB 0x40
#define VAL_FREQ_LSB 0x00

    int8_t rssi;
    uint8_t len_payload;

    void rfm69_set_state(bool state) ;
    void spi_rfm69_select(bool state) ;
    uint8_t spi_read_rfm69_rt(uint8_t reg) ;
    uint8_t spi_write_rfm69_rt(uint8_t reg, uint8_t val) ;
    uint8_t spi_write_rfm69_multiple_rt(uint8_t reg, const char *vals, uint8_t len) ;
    void set_rfm69_power_amp_boost();
    void set_rfm69_power_amp_normal() ;
    void set_rfm69_mode(uint8_t mode);
    void wait_rfm69_mode_ready();
    void set_rfm69_tx_mode();
    void set_rfm69_rx_mode();
    void set_rfm69_standby();
    void set_rfm69_idle();
    void set_rfm69_tx() ;
#ifdef __cplusplus
}
#endif

#endif /* RFM69_H */
