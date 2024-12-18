#include <stdbool.h>
#include "states.h"
#ifndef ST25DV_H
#define ST25DV_H

void rfid_set_low_power_down(bool state);
void rfid_set_i2c_power(bool state);


#endif