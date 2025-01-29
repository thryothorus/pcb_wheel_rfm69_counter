/* 
 * File:   power_mgmt.h
 * Author: thebears
 *
 * Created on December 20, 2024, 3:54 PM
 */
#include <avr/power.h>
#ifndef POWER_MGMT_H
#define	POWER_MGMT_H

#ifdef	__cplusplus
extern "C" {
#endif


    void shutdown_all_peripherals();

#ifdef	__cplusplus
}
#endif

#endif	/* POWER_MGMT_H */

