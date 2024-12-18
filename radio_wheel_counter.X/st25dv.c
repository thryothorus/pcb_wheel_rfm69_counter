#include "st25dv.h"

 void rfid_set_low_power_down(bool state) {
        SET_PIN_OUT(DDRD, DDD5);
        if (state) {
            SET_PIN_HIGH(PORTD, PD5);
        } else {
            SET_PIN_LOW(PORTD, PD5);
        }
    }

    void rfid_set_i2c_power(bool state) {

        SET_PIN_OUT(DDRE, DDE0);
        if (state) {
            SET_PIN_HIGH(PORTE, PE0);
        } else {
            SET_PIN_LOW(PORTE, PE0);
        }
    }
    