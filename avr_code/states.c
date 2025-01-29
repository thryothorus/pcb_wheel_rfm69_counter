#include "states.h"

    void init_spi() {
        SET_PIN_OUT(DDRC, DDC1);  // SCK
        SET_PIN_OUT(DDRE, DDE3);  // MOSI
        SET_PIN_IN(DDRC, DDC0); // MISO_RFM69
        SET_PIN_HIGH(PORTC, PC0);
        SPCR1= (1<<SPE1) | (1<<MSTR1);  // Enable, Master, f_osc/16
    }
    
    
    void rfm69_reset_state(bool state) {
        SET_PIN_OUT(DDRC, DDC2);
        if (state) {
            SET_PIN_HIGH(PORTC, PC2);
        } else {
            SET_PIN_LOW(PORTC, PC2);
        }
    }

    void led_1_set_state(bool state) {
        SET_PIN_OUT(DDRD, DDD4);
        if (state) {
            SET_PIN_HIGH(PORTD, PD4);
        } else {
            SET_PIN_LOW(PORTD, PD4);
        }
    }

    void led_2_set_state(bool state) {
        SET_PIN_OUT(DDRD, DDD6);
        if (state) {
            SET_PIN_HIGH(PORTD, PD6);
        } else {
            SET_PIN_LOW(PORTD, PD6);
        }
    }

    void led_3_set_state(bool state) {
        SET_PIN_OUT(DDRD, DDD7);
        if (state) {
            SET_PIN_HIGH(PORTD, PD7);
        } else {
            SET_PIN_LOW(PORTD, PD7);
        }
    }

    void ldo_set_state(bool state) {
        SET_PIN_OUT(DDRC, DDC3);
        if (state) {
            SET_PIN_HIGH(PORTC, PC3);
        } else {
            SET_PIN_LOW(PORTC, PC3);
        }
    }
