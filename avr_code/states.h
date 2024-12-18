/* 
 * File:   states.h
 * Author: thebears
 *
 * Created on December 6, 2024, 10:01 AM
 */

#ifndef STATES_H
#define	STATES_H


#include <stdbool.h>
#include <avr/io.h>

#define SET_PIN_OUT(DDR, PIN) ((DDR) |= (1 << (PIN)))  // Set pin as output
#define SET_PIN_IN(DDR, PIN)  ((DDR) &= ~(1 << (PIN))) // Set pin as input

#define SET_PIN_HIGH(PORT, PIN)  ((PORT) |= (1 << (PIN))) // Set pin high
#define SET_PIN_LOW(PORT, PIN)   ((PORT) &= ~(1 << (PIN))) // Set pin low



#ifdef	__cplusplus
extern "C" {
#endif

    void init_spi();
        
    void led_1_set_state(bool state);

    void led_2_set_state(bool state);

    void led_3_set_state(bool state);

    void ldo_set_state(bool state);

   

#ifdef	__cplusplus
}
#endif

#endif	/* STATES_H */

