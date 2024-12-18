
#include "states.h"

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

void set_debounce_timer_interrupt() {
    TCCR0A = 0;
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << TOIE0);
    TCNT0 = 0;
}
