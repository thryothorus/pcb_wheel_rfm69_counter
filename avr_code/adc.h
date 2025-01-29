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
typedef uint16_t adc_result_t;
typedef uint8_t adc_0_channel_t;

int8_t adc_Initialize();
void adc_Enable();
void adc_Disable();
void adc_StartConversion(adc_0_channel_t channel);
bool adc_IsConversionDone();
adc_result_t adc_GetConversionResult(void);
adc_result_t adc_GetConversion(adc_0_channel_t channel);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

