#include "power_mgmt.h"

void shutdown_all_peripherals() {
    
    power_adc_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_timer3_disable();
    power_usart0_disable();
    power_usart1_disable();
}
