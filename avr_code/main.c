#include "adc.h"
#include "defines.h"
#include "interrupts.h"
#include "m95128.h"
#include "max31329.h"
#include "ndef.h"
#include "power_mgmt.h"
#include "rfm69.h"
#include "st25dv.h"
#include "states.h"
#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#define WAIT_FOREVER                                                                               \
    while (1) {                                                                                    \
        _delay_ms(100);                                                                            \
    };

#define DO_UART true

//#define NUM_CYCLES_SEND_BACKLOG 2

time_struct td;
tx_rx_data_struct tx_data;
tx_rx_data_struct rx_data;
uint16_t self_value;
uint16_t main_counter;
identifier_results id_data;
volatile uint8_t is_debouncing = 0;
volatile bool increment_minute_index = false;
volatile bool increment_wheel_count = false;
volatile uint8_t index_wheel_count = 0;
uint16_t total_wheel_counts[16];
RTC_RFM69_STATUS rtc_rfm69_status;
//uint8_t backlog_number;

ISR(INT0_vect) {
    increment_minute_index = true;

}

ISR(INT1_vect) {
    increment_wheel_count = true;
    //    increment_minute_index = true;
    if (!is_debouncing) {
        is_debouncing = 1;
        wdt_isr_enable();
    }
}

ISR(WDT_vect) {
    is_debouncing = 0;
    wdt_isr_disable();
}

void start_sleeping() {
    spi_eeprom_select(false);
    spi_rfm69_select(false);
    rfid_set_low_power_down(true);
    rfid_set_i2c_power(false);
    ldo_set_state(false);

    _delay_ms(10);
    sleep_bod_disable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_cpu();
}

uint16_t get_battery_reading() {
    adc_Enable();
    adc_GetConversion(14);
    adc_GetConversion(14);
    self_value = adc_GetConversion(14);
    adc_Disable();
    return self_value;
}

// i2c Addresses

// RTC
// 0x68 (0xD0 W) (0xD1 R)

// NFC
// 0x2D (0x5A W) (0x5B R)
// 0x53 (0xA6 W) (0xA7 R)
// 0x57 (0xAE W) (0xAF R)

int main(void) {
    ldo_set_state(true);
    _delay_ms(10);
    init_pins();
    uart_init();
    uart_sendString("\r\n\r\n ................... STARTING! ................... \r\n\r\n");
    i2c_init();

    init_spi();
    adc_Initialize();
    set_up_reed_interrupt();
    set_up_minute_interrupt();
    rtc_set_per_minute_alarm();
    rtc_set_alarm_config();
    rtc_enable_interrupts();
    rtc_read_interrupt_register();
    rtc_read_status_register();
    rfm69_init();






    for (uint8_t c = 0; c < 15; c++) {
        total_wheel_counts[c] = 0;
    }

    // Get the nugget's name and wheel diameter
    id_data = get_nugget_data();
    

    // Request time from radio
    rtc_rfm69_status = set_time_from_rfm69(id_data);
    uart_print_rtc_time(rtc_read_time());
    if (rtc_rfm69_status == RTC_RFM69_SET_TIME_SUCCESS)
    {
        for (int i=0;i<5;i++){
     led_1_set_state(true);
     _delay_ms(90);
     led_1_set_state(false);
     _delay_ms(10);
        }
    }
    else
    {
//        uart_sendString("Time set failed\r\n");
           for (int i=0;i<5;i++){
     led_1_set_state(true);
     _delay_ms(10);
     led_1_set_state(false);
     _delay_ms(90);
        }
    }
    
  get_battery_reading();  


 
 
 
       

    while (1) {
//        uart_sendString("LOOP\r\n");
        spi_rfm69_select(false);
        spi_eeprom_select(false);
//        uart_wait_until_sent();

     
        start_sleeping();
        cli();
        if (increment_wheel_count) {
            increment_wheel_count = false;
            total_wheel_counts[index_wheel_count]++;
        };


        if (increment_minute_index) {
            increment_minute_index = false;
            index_wheel_count += 1;

            rtc_read_interrupt_register();
            rtc_read_status_register();
            

            rtc_read_interrupt_register();
            rtc_read_status_register();


            if (index_wheel_count >= 15) {
                index_wheel_count = 0;
                ldo_set_state(true);
                rfm69_init();
                rfid_set_i2c_power(true);
                rfid_set_low_power_down(false);
                _delay_ms(10);
                id_data = get_nugget_data();

                // Request time from radio if we don't have a good time stamp yet
                if (rtc_rfm69_status == RTC_RFM69_SET_TIME_FAILED) {
                    rtc_rfm69_status = set_time_from_rfm69(id_data);
                }
                get_battery_reading();
                
                // Generate wheel counts message
                reset_txrx_struct(&tx_data);
                tx_data = generate_wheel_counts_message(
                        id_data, rtc_read_time(), get_battery_reading(), total_wheel_counts);

                rfm69_write_msg(tx_data);
                //        DATA_SEND_STATUS result = send_message(tx_data);
                //        if (result == DATA_NOT_SENT) {
                //            write_struct_to_last_page(tx_data);
                //        }

                //        tx_data = read_struct_last_page();

                for (uint8_t c = 0; c < 15; c++) {
                    total_wheel_counts[c] = 0;
                }

                //                backlog_number += 1;

                //        if ((result == DATA_SEND_SUCCESS) && (backlog_number >= NUM_CYCLES_SEND_BACKLOG)
                //            && (get_last_page() > 0)) {
                //            reset_txrx_struct(&tx_data);
                //            tx_data = read_struct_last_page();
                //            tx_data.flags = MSG_RESENT_COUNTS;
                //            tx_data.from = id_data.hashed;
                //            uart_sendString("Sending last page\r\n\r\n");
                //            uart_wait_until_sent();
                //            uart_print_tx_rx_data(tx_data);
                //            _delay_ms(10);
                //
                //            DATA_SEND_STATUS result = send_message(tx_data);
                //            delete_last_page();
                //
                //            backlog_number = 0;
                //        }
            }

        }
    }
}
