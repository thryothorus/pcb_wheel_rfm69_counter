/* 
 * File:   interrupts.h
 * Author: thebears
 *
 * Created on December 18, 2024, 12:48 PM
 */

#include <avr/io.h>
#include "states.h"
#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#ifdef	__cplusplus
extern "C" {
#endif



    void init_pins();
    void set_up_reed_interrupt();
    void set_debounce_timer_interrupt();

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

