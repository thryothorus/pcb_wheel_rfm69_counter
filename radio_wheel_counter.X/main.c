#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "states.h"
#include "st25dv.h"
#include "interrupts.h"
#include "max31329.h"
time_struct td;
volatile uint8_t debounce_flag = 0;

ISR(INT1_vect) {
    if (debounce_flag == 0) {
        uart_sendString("bump!\n\r");
        _delay_ms(1);
        debounce_flag = 1;
        TCNT0 = 0;
    }
}

ISR(TIMER0_OVF_vect) {
    debounce_flag = 0; // Clear debounce flag
}

void start_sleeping() {
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sei();
    sleep_bod_disable();
    sleep_cpu();

}

int main(void) {
    led_2_set_state(false);
    uart_init();
    _delay_ms(10);
    uart_sendString("Hello!\n\r");
    _delay_ms(10);
    rfid_set_low_power_down(true);
    ldo_set_state(false);

    init_pins();
    set_up_reed_interrupt();
    set_debounce_timer_interrupt();

    i2c_init();


    td.Second = 1;
    td.Minute = 6;
    td.Hour = 14;
    td.Day = 18;
    td.Month = 12;
    td.Year = 24;
    td.Wday = 4;

    rtc_write_time(td);
    rtc_set_per_minute_alarm();
    rtc_set_alarm_config();
    rtc_enable_interrupts();
    while (1) {

        uart_sendString("---------\r\n");
        
        uart_print_binary(rtc_read_status_register(), "STATUS");
        uart_print_binary(rtc_read_interrupt_register(),"INTERRUPTS");
        

        if (true) {
            td = rtc_read_time();
//            uart_print_uint8(td.Second, "Second");
            uart_print_uint8(td.Minute, "Minute");
//            uart_print_uint8(td.Hour, "Hour");
//            uart_print_uint8(td.Wday, "WeekDay");
//            uart_print_uint8(td.Day, "Day");
//            uart_print_uint8(td.Month, "Month");
//            uart_print_uint8(td.Year, "Year");
            uart_sendString("---------\r\n");
            
        };
        _delay_ms(1000);
    }
}


//    sleep_cpu();
//    _delay_ms(250);
//    led_1_set_state(true);
// Main loop (does nothing in this case)
//    while (1) {
// The device will keep scanning the I2C bus and output to UART
//                I2C_scan();
//    }


//    DDRC |= (1 << DDC3);    
//    PORTC |= (1 << PC3);
//    rfid_set_low_power_down(false); 
//    spi_rfm69_select(false);


//        spi_rfm69_select(true);
//    spi_eeprom_select(false);

//
//    USART0_init(UBRR_BAUD);
//    I2C_init();
//    _delay_ms(100);

// Scan for I2C devices
//    I2C_scan();
//    led_3_set_state(true);
//
//
//    uart_print_hex_bin(SPCR1, "SPCR1\r\n");
//
//    spi_eeprom_select(true);
//    uart_print_hex_bin(spi_write(EEPROM_RDSR), "RDSR");
//    uart_print_hex_bin(spi_read(), "    read");
//    spi_eeprom_select(false);
//
//    spi_eeprom_select(true);
//    uart_print_hex(spi_write(EEPROM_WREN), "WREN");
//    spi_eeprom_select(false);
//
//    spi_eeprom_select(true);
//    uart_print_hex(spi_write(EEPROM_RDSR), "RDSR");
//    uart_print_hex(spi_read(), "    read");
//    spi_eeprom_select(false);
//
//    spi_eeprom_select(true);
//    uart_print_hex(spi_write(EEPROM_WRITE), "WRITE");
//    uart_print_hex(spi_write(0x00), "    addr");
//    uart_print_hex(spi_write(0x00), "    addr");
//    uart_print_hex(spi_write(0x00), "    write");
//    uart_print_hex(spi_write(0xFF), "    write");
//    uart_print_hex(spi_write(0x00), "    write");
//    uart_print_hex(spi_write(0xFF), "    write");
//    uart_print_hex(spi_write(0x00), "    write");
//    uart_print_hex(spi_write(0xFF), "    write");
//    spi_eeprom_select(false);
//
//    spi_eeprom_select(true);
//    uart_print_hex(spi_write(EEPROM_WRDI), "WRITE DISABLE");
//    spi_eeprom_select(false);
//    spi_eeprom_select(true);
//    uart_print_hex(spi_write(EEPROM_READ), "READ");
//    uart_print_hex(spi_write(0x00), "    addr");
//    uart_print_hex(spi_write(0x00), "    addr");
//    uart_print_hex(spi_read(), "    read");
//    uart_print_hex(spi_read(), "    read");
//    uart_print_hex(spi_read(), "    read");
//    uart_print_hex(spi_read(), "    read");
//    uart_print_hex(spi_read(), "    read");
//    uart_print_hex(spi_read(), "    read");
//    spi_eeprom_select(false);
//
//    spi_deselect_all();



//    spi_eeprom_select(false);

//    led_1_set_state(false);
//    led_2_set_state(false);
//    led_3_set_state(false);
//    spi_eeprom_select(false);
//    rfid_set_low_power_down(true);
//    ldo_set_state(false);



//    DDRB &= ~(1 << PB1); // Set PB1 as input
//    PORTB |= (1 << PB1);  // Enable pull-up resistor on PB1
//    PCMSK0 |= (1 << PCINT1); // Unmask PCINT9 for interrupts

// Enable Pin Change Interrupt 1
//    PCICR |= (1 << PCIE0); // Enable PCINT1 group interrupts

//    sei(); // Enable global interrupts

//    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Configure Power-down mode
//    sleep_enable(); // Enable sleep mode
//sleep_bod_disable();
//    sleep_cpu();
//    _delay_ms(250);
//    led_1_set_state(true);
// Main loop (does nothing in this case)
//    while (1) {
// The device will keep scanning the I2C bus and output to UART
//                I2C_scan();
//    }

//    return 0;
//}