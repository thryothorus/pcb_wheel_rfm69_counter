
#include "interrupts.h"

void init_pins() {

    // Set reed switch interrupt pin
    SET_PIN_IN(DDRD, DDD3);
    SET_PIN_LOW(PORTD, PD3);
}

void set_up_reed_interrupt() {
    // Falling edge interrupt
    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);

    // Enable INT1 interrupt
    EIMSK |= (1 << INT1);
}

void set_up_minute_interrupt() {
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Enable INT1 interrupt
    EIMSK |= (1 << INT0);
}

void wdt_isr_enable() {
    cli();
    wdt_reset();

    WDTCSR |= (1 << WDCE) | (1 << WDE);

    WDTCSR = (1 << WDP2) | (1 << WDP0); // WDP[3:0] = 0b101 (2 seconds)
    WDTCSR |= (1 << WDIE); // Enable WDT Interrupt mode
    sei();
}

void wdt_isr_disable() {

    cli();

    WDTCSR |= (1 << WDCE) | (1 << WDE);
    WDTCSR = 0x00; 

    sei(); 
}
//
//void set_debounce_timer_interrupt() {
//    TCCR0A = 0;
//    TCCR0B = (1 << CS01) | (1 << CS00);
//    TIMSK0 = (1 << TOIE0);
//    TCNT0 = 0;
//}
