#include "adc.h"

int8_t adc_Initialize()
{
    //REFS VAL_0x01; ADLAR disabled; MUX adc0; 
    ADMUX = 0x40;

    //ACME disabled; ADTS VAL_0x00; 
    ADCSRB = 0x00;

    //ADEN enabled; ADSC disabled; ADATE disabled; ADIF disabled; ADIE disabled; ADPS VAL_0x01; 
    ADCSRA = 0x81;

    return 0;
}

void adc_Disable()
{
	ADCSRA &= ~(1 << ADEN);
}

void adc_Enable()
{
	ADCSRA |= (1 << ADEN);
}


void adc_StartConversion(adc_0_channel_t channel)
{
    if (channel == 0)
    {
     
        ADMUX=0b01000000;
    }
    else if (channel == 14)
    {
//        ADMUX=0b01001110;
        ADMUX=(0x01 << REFS0) | (0<<ADLAR) | (0x0e << MUX0);
    }
    else
    {
	ADMUX &= ~0x0f;
	ADMUX |= channel;
    }
	ADCSRA |= (1 << ADSC);
}

bool adc_IsConversionDone()
{
	return ((ADCSRA & (1 << ADIF)));
}

adc_result_t adc_GetConversionResult(void)
{
	return (ADCL | ADCH << 8);
    
//    return (ADCL + (ADCH*256));
}

adc_result_t adc_GetConversion(adc_0_channel_t channel)
{
	adc_result_t res;

	adc_StartConversion(channel);
	while (!adc_IsConversionDone());
	res = adc_GetConversionResult();
	ADCSRA |= (1 << ADIF);
	return res;
}
