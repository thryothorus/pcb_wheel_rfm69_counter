/*
 * File:   rfm69.h
 * Author: thebears
 *
 * Created on December 11, 2024, 2:05 PM
 */
#include "defines.h"
#include "spi.h"
#include "states.h"
#include "uart.h"
#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#ifndef RFM69_H
#define RFM69_H

#define MODE_NOT_READY !(spi_read_rfm69_rt(REG_IRQ_FLAGS1) & VAL_IRQ_FLAGS1_MODEREADY)
#define RX_PAYLOAD_READY spi_read_rfm69_rt(REG_IRQ_FLAGS2) & VAL_IRQ_FLAGS2_RX_PAYLOADREADY
#define RX_PAYLOAD_NOT_READY !(RX_PAYLOAD_READY)
#define TX_NOT_SENT !(spi_read_rfm69_rt(REG_IRQ_FLAGS2) & VAL_IRQ_FLAGS2_TX_SENT)
#ifdef __cplusplus
extern "C" {
#endif

#define REG_FIFO 0x00
#define REG_FREQ_MSB 0x07
#define REG_FREQ_MIDDLE_SB 0x08
#define REG_FREQ_LSB 0x09
#define REG_FIFO_THRESH 0x3c
#define REG_TEST_DAGC 0x6f
#define REG_SYNC_CONFIG 0x2e
#define REG_SYNC_VALUE_1 0x2f
#define REG_OP_MODE 0x01
#define REG_DATA_MODUL 0x02
#define REG_BITRATE_MSB 0x03
#define REG_BITRATE_LSB 0x04
#define REG_FDEV_MSB 0x06
#define REG_FDEV_LSB 0x06
#define REG_RX_BW 0x19
#define REG_AFC_BW 0x1A
#define REG_PACKET_CONFIG_1 0x37
#define REG_PREAMBLE_MSB 0x2C
#define REG_PREAMBLE_LSB 0x2D
#define REG_PA_LEVEL 0x11
#define REG_TEST_PA1 0x5A
#define REG_TEST_PA2 0x5C
#define REG_IRQ_FLAGS1 0x27
#define REG_IRQ_FLAGS2 0x28
#define REG_RSSI_VALUE 0x24

#define REG_FREQ_DEV_MSB 0x05
#define VAL_FREQ_DEV_MSB 0x10

#define VAL_TEST_DAGC_DEFAULT 0x30
#define VAL_DATA_PACKET_MODE 0x00

#define VAL_BITRATE_250kbps_MSB 0x00
#define VAL_BITRATE_250kbps_LSB 0x80

#define VAL_DATA_MODUL_OOK 0x01
#define VAL_TX_START_FIFO_NOT_EMPTY 0x80
#define VAL_FIFO_LEVEL_INTERRUPT 0x0f

#define VAL_IRQ_FLAGS1_MODEREADY 0x80
#define VAL_IRQ_FLAGS2_TX_SENT 0x08
#define VAL_IRQ_FLAGS2_RX_PAYLOADREADY 0x04
#define VAL_OPMODE_MASK 0x1c
#define VAL_OPMODE_SLEEP 0x00
#define VAL_OPMODE_STDBY 0x04
#define VAL_OPMODE_TX 0x0c
#define VAL_OPMODE_RX 0x10
#define VAL_SYNCWORDS_ON 0x80
#define VAL_SYNCWORDS_SIZE_2_BYTES 0x08
#define VAL_PACKET_VARIABLE_LENGTH 0x80
#define VAL_PACKET_WHITENING 0x40
#define VAL_PACKET_CRCON 0x10

#define VAL_PA_PA1_ON 0x40
#define VAL_PA_PA2_ON 0x20
#define VAL_PA_20dB 0x1F

#define VAL_PALEVEL_PA1_ON 0x40
#define VAL_PALEVEL_PA2_ON 0x20
#define VAL_PALEVEL_PA1_OUTPUTPOWER 0x1f

#define VAL_TEST_PA1_NORMAL 0x55
#define VAL_TEST_PA2_NORMAL 0x70

#define VAL_TEST_PA1_BOOST 0x5d
#define VAL_TEST_PA2_BOOST 0x7c

#define RFM69_SPI_WRITE 0x80

// Target frequency is 433 MHz.
// Equation is 32MHz/2^19 = 61.03515625.  433 MHz/61.03515625 = 7,094,272
// 7,094,272 = 01101100 01000000 00000000 = 0x6C 0x40 0x00

// Target frequency is 434.0 MHz.
// Equation is 32MHz/2^19 = 61.03515625.  434 MHz/61.03515625 = 7,110,656
// 7,110,656 = 01101100 01000000 00000000 = 0x6C 0x80 0x00
#define VAL_FREQ_433MHz_MSB 0x6c
#define VAL_FREQ_433MHz_MID_SB 0x80
#define VAL_FREQ_433MHz_LSB 0x00

DATA_SEND_STATUS send_message(tx_rx_data_struct tx_data);
void rfm69_set_state(bool state);

uint8_t spi_read_rfm69_rt(uint8_t reg);
uint8_t spi_write_rfm69_rt(uint8_t reg, uint8_t val);
uint8_t spi_write_rfm69_multiple_rt(uint8_t reg, const char* vals, uint8_t len);
void set_rfm69_power_amp_boost();
void set_rfm69_power_amp_normal();
tx_rx_data_struct rfm69_read_msg();
void reset_txrx_struct(tx_rx_data_struct* s);
void rfm69_write_msg(tx_rx_data_struct txrxd);
void set_rfm69_mode(uint8_t mode);
void wait_rfm69_mode_ready();
void set_rfm69_tx_mode();
void wait_tx_sent();
void wait_rx_payload_ready();
void reset_rfm69();
void set_rfm69_rx_mode();
void set_rfm69_standby();
void set_rfm69_sleep();
void set_rfm69_idle();
void set_rfm69_tx_power();
void rfm69_init();
bool wait_rx_payload_ready_timeout(uint16_t attempts);
uint8_t hash(const char* str, uint8_t min, uint8_t max);
uint32_t hash_3bytes(unsigned const char* str, uint8_t str_len);
void uart_print_tx_rx_data(tx_rx_data_struct tx_rx_print);

tx_rx_data_struct generate_wheel_counts_message(
    identifier_results idd, time_struct time, uint16_t battery_value, volatile uint16_t counts[15]);

#ifdef __cplusplus
}
#endif

#endif /* RFM69_H */
