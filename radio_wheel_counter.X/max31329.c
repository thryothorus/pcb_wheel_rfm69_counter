#include "max31329.h"

uint8_t data[7];
time_struct time_data;

uint8_t rtc_set_per_minute_alarm() {
    if (i2c_start((I2C_ADDR << 1) | 0x00)) return 1; // Start + Write
    i2c_write(0x13);
    i2c_write(0x80);
    i2c_write(0x80);
    i2c_write(0x80);
    i2c_stop();
    return 0;
}

uint8_t rtc_read_register(uint8_t addr) {

    if (i2c_start((I2C_ADDR << 1) | 0x00)) return 1; // Start + Write
    i2c_write(addr);


    if (i2c_start((I2C_ADDR << 1) | 0x01) != 0) { // Start + Read
        i2c_stop();
        return 1;
    }
    uint8_t var = i2c_read_nack();
    i2c_stop();
    return var;

}

uint8_t rtc_read_status_register() {
    return rtc_read_register(0x00);
}

uint8_t rtc_read_interrupt_register() {
    return rtc_read_register(0x01);
}
    

    uint8_t rtc_set_alarm_config() {
        if (i2c_start((I2C_ADDR << 1) | 0x00)) return 1; // Start + Write
        i2c_write(0x04);
        i2c_write(0x00);
        i2c_stop();
        return 0;
    }

    uint8_t rtc_enable_interrupts() {
        if (i2c_start((I2C_ADDR << 1) | 0x00)) return 1; // Start + Write
        i2c_write(0x01);
        i2c_write(0b00001010);
        i2c_stop();
        return 0;
    }

    uint8_t rtc_read_time_array(uint8_t * data) {


        if (i2c_start((I2C_ADDR << 1) | 0x00)) return 1; // Start + Write
        i2c_write(0x06);


        if (i2c_start((I2C_ADDR << 1) | 0x01) != 0) { // Start + Read
            i2c_stop();
            return 1;
        }

        for (uint8_t i = 0; i < 6; i++) {
            data[i] = i2c_read_ack(); // Read byte with ACK
        }
        data[6] = i2c_read_nack(); // Read last byte with NACK

        i2c_stop(); // Stop communication
        return 0; // Success
    }

    time_struct rtc_read_time() {

        rtc_read_time_array(data);
        time_data.Second = BCD2DEC(data[0]);
        time_data.Minute = BCD2DEC(data[1]);
        time_data.Hour = BCD2DEC(data[2] & ~(1 << 6));
        time_data.Wday = data[3];
        time_data.Day = BCD2DEC(data[4]);
        time_data.Month = BCD2DEC(data[5] & ~(1 << 7));
        time_data.Year = tmYearToY2k(BCD2DEC(data[6]));
        return time_data;
    };

    uint8_t rtc_write_time(time_struct tm) {

        if (i2c_start((I2C_ADDR << 1) | 0x00)) return 1;

        i2c_write(0x06);
        i2c_write(DEC2BCD(tm.Second));
        i2c_write(DEC2BCD(tm.Minute));
        i2c_write(DEC2BCD(tm.Hour));
        i2c_write(tm.Wday);
        i2c_write(DEC2BCD(tm.Day));
        i2c_write(DEC2BCD(tm.Month));
        i2c_write(DEC2BCD(y2kYearToTm(tm.Year)));

        i2c_stop();
        return 0;
    }

