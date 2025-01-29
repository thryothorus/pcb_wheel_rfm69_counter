#include "max31329.h"

uint8_t data[7];
time_struct time_data;
tx_rx_data_struct tx_rtc_data;
tx_rx_data_struct rx_rtc_data;

RTC_RFM69_STATUS set_time_from_rfm69(identifier_results id_data)
{
    time_struct td; 
   
    reset_txrx_struct(&tx_rtc_data);
    memcpy(tx_rtc_data.msg, id_data.name_str, MIN(10, id_data.name_len));
    memcpy(tx_rtc_data.msg + 10, id_data.diameter_str, MIN(10, id_data.diameter_len));
    tx_rtc_data.len = 20;
    tx_rtc_data.flags = MSG_REQ_CTIME;
    tx_rtc_data.dtype = MSG_TYPE_STRING;

    rfm69_write_msg(tx_rtc_data);

    bool result = wait_rx_payload_ready_timeout(100);

    if (result) {
        rx_rtc_data = rfm69_read_msg();
        if (rx_rtc_data.flags == 2) {
//            uart_print_tx_rx_data(rx_rtc_data);

            // td.Second = rx_data.msg[0];
            td.Second = id_data.hashed;

            td.Minute = rx_rtc_data.msg[1];
            td.Hour = rx_rtc_data.msg[2];
            td.Day = rx_rtc_data.msg[3];
            td.Month = rx_rtc_data.msg[4];
            td.Year = rx_rtc_data.msg[5];
            td.Wday = rx_rtc_data.msg[6];

            rtc_write_time(td);
            return RTC_RFM69_SET_TIME_SUCCESS;
        }
    } else {
//        uart_sendString("Did not get RX\r\n");;
    }
    return RTC_RFM69_SET_TIME_FAILED;
}

uint8_t rtc_set_per_minute_alarm()
{
    uint8_t data[3];
    data[0] = 0x80;
    data[1] = 0x80;
    data[2] = 0x80;

    return write_n_bytes(I2C_ADDR, 0x13, data, 3);
    // if (i2c_start((I2C_ADDR << 1) | 0x00))
    //     return 1; // Start + Write
    // i2c_write(0x13);
    // i2c_write(0x80);
    // i2c_write(0x80);
    // i2c_write(0x80);
    // i2c_stop();
    // return 0;
}

void uart_print_rtc_time(time_struct td)
{
    char buffer[20];
    snprintf(
        buffer, sizeof(buffer), "%u/%02u/%02u %u:%02u:%02u", 2000 + td.Year, td.Month, td.Day,
        td.Hour, td.Minute, td.Second);
    uart_sendString(buffer);
    uart_sendString("\r\n");
}

uint8_t rtc_read_register(uint8_t addr)
{
    return read_one_byte_no_err_register(I2C_ADDR, addr);
    // if (i2c_start((I2C_ADDR << 1) | 0x00))
    //     return 1; // Start + Write
    // i2c_write(addr);

    // if (i2c_start((I2C_ADDR << 1) | 0x01) != 0) { // Start + Read
    //     i2c_stop();
    //     return 1;
    // }
    // uint8_t var = i2c_read_nack();
    // i2c_stop();
    // return var;
}

uint8_t rtc_read_status_register() { return rtc_read_register(0x00); }

uint8_t rtc_read_interrupt_register() { return rtc_read_register(0x01); }

uint8_t rtc_set_alarm_config()
{

    return write_one_byte(I2C_ADDR, 0x04, 0b00001010);
    // if (i2c_start((I2C_ADDR << 1) | 0x00))
    //     return 1; // Start + Write
    // i2c_write(0x04);
    // i2c_write(0x00);
    // i2c_stop();
    // return 0;
}

uint8_t rtc_enable_interrupts()
{
    //    return write_one_byte(I2C_ADDR, 0x01, 0b00001010);
    return write_one_byte(I2C_ADDR, 0x01, 0b00000010);
    // if (i2c_start((I2C_ADDR << 1) | 0x00))
    //     return 1; // Start + Write
    // i2c_write(0x01);
    // i2c_write(0b00001010);
    // i2c_stop();
    // return 0;
}

uint8_t rtc_read_time_array(uint8_t* data)
{

    return read_n_bytes(I2C_ADDR, 0x06, data, 7);

    // if (i2c_start((I2C_ADDR << 1) | 0x00))
    //     return 1; // Start + Write
    // i2c_write(0x06);

    // if (i2c_start((I2C_ADDR << 1) | 0x01) != 0) { // Start + Read
    //     i2c_stop();
    //     return 1;
    // }

    // for (uint8_t i = 0; i < 6; i++) {
    //     data[i] = i2c_read_ack(); // Read byte with ACK
    // }
    // data[6] = i2c_read_nack(); // Read last byte with NACK

    // i2c_stop(); // Stop communication
    // return 0; // Success
}

time_struct rtc_read_time()
{

    rtc_read_time_array(data);
    time_data.Second = BCD2DEC(data[0]);
    time_data.Minute = BCD2DEC(data[1]);
    time_data.Hour = BCD2DEC((data[2] & ~(1 << 6)));
    time_data.Wday = data[3];
    time_data.Day = BCD2DEC(data[4]);
    time_data.Month = BCD2DEC((data[5] & ~(1 << 7)));
    time_data.Year = tmYearToY2k(BCD2DEC(data[6]));
    return time_data;
};

uint8_t rtc_write_time(time_struct tm)
{

    if (i2c_start((I2C_ADDR << 1) | 0x00))
        return 1;

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
