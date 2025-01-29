#include "max31329.h"
bool result;

RTC_RFM69_STATUS set_time_from_rfm69(identifier_results id_data)
{
    rfm69_init();
    _delay_ms(1);

    reset_txrx_struct(&TX_DATA);
    memcpy(TX_DATA.msg, id_data.name_str, MIN(10, id_data.name_len));
    memcpy(TX_DATA.msg + 10, id_data.diameter_str, MIN(10, id_data.diameter_len));
    TX_DATA.len = 20;
    TX_DATA.flags = MSG_REQ_CTIME;
    TX_DATA.dtype = MSG_TYPE_STRING;

    rfm69_write_msg(TX_DATA);
    result = wait_rx_payload_ready_timeout(100);

    if (result) {
        RX_DATA = rfm69_read_msg();
        if (RX_DATA.flags == 2) {

            // TIME.Second = rx_data.msg[0];
            TIME.Second = id_data.hashed;

            TIME.Minute = RX_DATA.msg[1];
            TIME.Hour = RX_DATA.msg[2];
            TIME.Day = RX_DATA.msg[3];
            TIME.Month = RX_DATA.msg[4];
            TIME.Year = RX_DATA.msg[5];
            TIME.Wday = RX_DATA.msg[6];

            rtc_write_time(TIME);
            return RTC_RFM69_SET_TIME_SUCCESS;
        }
    } else {
        // uart_sendString("Did not get RX\n");
    }
    return RTC_RFM69_SET_TIME_FAILED;
}

uint8_t rtc_set_per_minute_alarm()
{

    DATA_BUFFER_7[0] = 0x80;
    DATA_BUFFER_7[1] = 0x80;
    DATA_BUFFER_7[2] = 0x80;

    return write_n_bytes(I2C_ADDR, 0x13, DATA_BUFFER_7, 3);
}

void uart_print_rtc_time(time_struct td)
{
    char str_rtc[26];
    snprintf(
        str_rtc, sizeof(str_rtc), "%u/%02u/%02u %u:%02u:%02u", 2000 + td.Year,
        td.Month, td.Day, td.Hour, td.Minute, td.Second);
    uart_sendString(str_rtc);
    uart_sendString("\n");
}

uint8_t rtc_read_register(uint8_t addr) { return read_one_byte_no_err_register(I2C_ADDR, addr); }

uint8_t rtc_read_status_register() { return rtc_read_register(0x00); }

uint8_t rtc_read_interrupt_register() { return rtc_read_register(0x01); }

uint8_t rtc_set_alarm_config() { return write_one_byte(I2C_ADDR, 0x04, 0b00001010); }

uint8_t rtc_enable_interrupts() { return write_one_byte(I2C_ADDR, 0x01, 0b00000010); }

uint8_t rtc_read_time_array(uint8_t* data) { return read_n_bytes(I2C_ADDR, 0x06, data, 7); }

time_struct rtc_read_time()
{

    rtc_read_time_array(DATA_BUFFER_7);
    TIME.Second = BCD2DEC(DATA_BUFFER_7[0]);
    TIME.Minute = BCD2DEC(DATA_BUFFER_7[1]);
    TIME.Hour = BCD2DEC((DATA_BUFFER_7[2] & ~(1 << 6)));
    TIME.Wday = DATA_BUFFER_7[3];
    TIME.Day = BCD2DEC(DATA_BUFFER_7[4]);
    TIME.Month = BCD2DEC((DATA_BUFFER_7[5] & ~(1 << 7)));
    TIME.Year = tmYearToY2k(BCD2DEC(DATA_BUFFER_7[6]));
#if DO_UART
    uart_print_rtc_time(TIME);
#endif
    return TIME;
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
