/* 
 * File:   adc.h
 * Author: thebears
 *
 * Created on December 10, 2021, 10:13 PM
 */

#ifndef ADC_H
#define	ADC_H
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif


int8_t adc_Initialize();
void adc_Enable();
void adc_Disable();
void adc_StartConversion(uint8_t channel);
bool adc_IsConversionDone();
uint16_t adc_GetConversionResult(void);
uint16_t adc_GetConversion(uint8_t channel);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

