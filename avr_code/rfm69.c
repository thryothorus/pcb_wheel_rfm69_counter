#include "rfm69.h"

int8_t rssi;
uint8_t i;
uint8_t len_payload;
tx_rx_data_struct tx_rx_data;
tx_rx_data_struct rfm69_rx_data;
uint32_t msg_hash;
uint8_t p_hash_1;
uint8_t p_hash_2;
uint8_t p_hash_3;

uint8_t c_hash_1;
uint8_t c_hash_2;
uint8_t c_hash_3;

bool cond_1;
bool cond_2;
bool cond_3;
bool cond_4;
bool cond_5;

DATA_SEND_STATUS send_message(tx_rx_data_struct tx_data)
{
    // uart_print_tx_rx_data(tx_data);
    rfm69_write_msg(tx_data);

    p_hash_1 = tx_data.msg[57];
    p_hash_2 = tx_data.msg[58];
    p_hash_3 = tx_data.msg[59];

    for (uint8_t i = 0; i < 10; i++) {
        bool result = wait_rx_payload_ready_timeout(250);
        if (result) {
//            uart_sendString("MESSAGE RECV\r\n");
            rfm69_rx_data = rfm69_read_msg();
//            uart_print_tx_rx_data(rfm69_rx_data);
            c_hash_1 = rfm69_rx_data.msg[0];
            c_hash_2 = rfm69_rx_data.msg[1];
            c_hash_3 = rfm69_rx_data.msg[2];

            cond_1 = (p_hash_1 == c_hash_1) && (p_hash_2 == c_hash_2) && (p_hash_3 == c_hash_3);
            cond_2 = (tx_data.from == rfm69_rx_data.to) && (tx_data.to == rfm69_rx_data.from);
            cond_3 = cond_1 && cond_2;
            
            if (cond_3 && (rfm69_rx_data.flags == MSG_RECV_COUNTS_SUCCESS)
                && (rfm69_rx_data.msg[3] == 0xFF)) {
                return DATA_SEND_SUCCESS;
                break;
            } else if (
                cond_3 && (rfm69_rx_data.flags == MSG_RECV_COUNTS_FAIL)
                && (rfm69_rx_data.msg[3] == 0x00)) {
                
            } else {
            }

        } else {
        }
    }
    return DATA_NOT_SENT;
}

void uart_print_tx_rx_data(tx_rx_data_struct tx_rx_print)
{

    uart_print_uint8(tx_rx_print.len, "LENGTH");
    uart_print_uint8(tx_rx_print.to, "TO");
    uart_print_uint8(tx_rx_print.from, "FROM");
    uart_print_uint8(tx_rx_print.dtype, "DTYPE");
    uart_print_uint8(tx_rx_print.flags, "FLAGS");
    //       uart_sendStringArray(tx_rx_print.msg, tx_rx_print.len);
    uart_print_uint8_array(tx_rx_print.msg, tx_rx_print.len, "AS NUMBER");
    //       uart_sendString("\r\n");
}

void rfm69_write_msg(tx_rx_data_struct txrxd)
{
    set_rfm69_rx_mode();
    set_rfm69_tx_mode();
    spi_rfm69_select(true);
    spi_write(REG_FIFO | RFM69_SPI_WRITE);
    if (txrxd.len > (60)) {
        txrxd.len = 60;
    }

    spi_write(txrxd.len + 4);
    spi_write(txrxd.to);
    spi_write(txrxd.from);
    spi_write(txrxd.dtype);
    spi_write(txrxd.flags);
    for (uint8_t x = 0; x < txrxd.len; x++) {
        spi_write(txrxd.msg[x]);
    }
    spi_rfm69_select(false);

    wait_tx_sent();
    set_rfm69_rx_mode();
}

tx_rx_data_struct rfm69_read_msg()
{
    memset(tx_rx_data.msg, ' ', sizeof(tx_rx_data.msg));
    spi_rfm69_select(true);
    spi_write(REG_FIFO);

    tx_rx_data.len = spi_read() - 4;
    tx_rx_data.to = spi_read();
    tx_rx_data.from = spi_read();
    tx_rx_data.dtype = spi_read();
    tx_rx_data.flags = spi_read();
    uint8_t len_f = tx_rx_data.len;

    for (uint8_t idx_f = 0; idx_f < len_f; idx_f++) {
        tx_rx_data.msg[idx_f] = spi_read();
    }
    spi_rfm69_select(false);
    set_rfm69_idle();

    return tx_rx_data;
}

void rfm69_set_state(bool state)
{
    SET_PIN_OUT(DDRC, DDC2);
    if (!state) {
        SET_PIN_HIGH(PORTC, PC2);
    } else {
        SET_PIN_LOW(PORTC, PC2);
    }
}

uint8_t spi_read_rfm69_rt(uint8_t reg)
{
    spi_rfm69_select(true);
    spi_write(reg);
    uint8_t data_read = spi_read(0xFF);
    spi_rfm69_select(false);
    return data_read;
}

uint8_t spi_write_rfm69_rt(uint8_t reg, uint8_t val)
{
    spi_rfm69_select(true);
    spi_write(reg | RFM69_SPI_WRITE);
    uint8_t data_read = spi_write(val);
    spi_rfm69_select(false);
    return data_read;
}

uint8_t spi_write_rfm69_multiple_rt(uint8_t reg, const char* vals, uint8_t len)
{
    spi_rfm69_select(true);
    uint8_t data_init = spi_write(reg | RFM69_SPI_WRITE);
    while (len--)
        spi_write(*vals++);

    spi_rfm69_select(false);
    return data_init;
}

// name (max 10),           10
// diameter (max 10),       20
// battery_value 16-bit,    22
// time_reading (min)       23
// time_reading (hour)      24
// time_reading (day)       25
// time_reading (month)     26
// time_reading (year)      27
// 15 * per-min  +30        57
// three byte hash check     3

tx_rx_data_struct generate_wheel_counts_message(
    identifier_results idd, time_struct time, uint16_t battery_value, volatile uint16_t counts[15])
{

    reset_txrx_struct(&tx_rx_data);
    memcpy(tx_rx_data.msg, idd.name_str, MIN(10, idd.name_len));
    memcpy(tx_rx_data.msg + 10, idd.diameter_str, MIN(10, idd.diameter_len));

    tx_rx_data.msg[20] = battery_value & 0xFF;
    tx_rx_data.msg[21] = (battery_value >> 8) & 0xFF;

    tx_rx_data.msg[22] = time.Minute;
    tx_rx_data.msg[23] = time.Hour;
    tx_rx_data.msg[24] = time.Day;
    tx_rx_data.msg[25] = time.Month;
    tx_rx_data.msg[26] = time.Year;

    for (uint8_t idx = 0; idx < 15; idx++) {
        tx_rx_data.msg[26 + (2 * idx + 1)] = counts[idx] & 0xFF; // LSB first
        tx_rx_data.msg[26 + (2 * idx + 2)] = (counts[idx] >> 8) & 0xFF; // MSB second
    }

    msg_hash = hash_3bytes(tx_rx_data.msg, 57);
    tx_rx_data.msg[57] = msg_hash & 0xFF;
    tx_rx_data.msg[58] = (msg_hash >> 8) & 0xFF;
    tx_rx_data.msg[59] = (msg_hash >> 16) & 0xFF;

    tx_rx_data.len = sizeof(tx_rx_data.msg);
    tx_rx_data.flags = MSG_SEND_COUNTS;
    tx_rx_data.from = idd.hashed;
    tx_rx_data.to = 255;
    tx_rx_data.dtype = MSG_TYPE_BINARY;
    return tx_rx_data;
}

uint32_t hash_3bytes(const char* str, uint8_t str_len)
{
    uint32_t hash = 0;

    for (i = 0; i < str_len; i++) {
        hash = (hash * 31 + str[i]) % 0xFFFFFF;
    }
    return hash;
}

void set_rfm69_power_amp_boost()
{
    spi_write_rfm69_rt(REG_TEST_PA1, VAL_TEST_PA1_BOOST);
    spi_write_rfm69_rt(REG_TEST_PA2, VAL_TEST_PA2_BOOST);
}

void set_rfm69_power_amp_normal()
{
    spi_write_rfm69_rt(REG_TEST_PA1, VAL_TEST_PA1_NORMAL);
    spi_write_rfm69_rt(REG_TEST_PA2, VAL_TEST_PA2_NORMAL);
};

void reset_txrx_struct(tx_rx_data_struct* s)
{
    s->len = 0;
    s->to = 255;
    s->from = 255;
    s->dtype = 0;
    s->flags = 0;
    memset(s->msg, ' ', 60);
}

void set_rfm69_mode(uint8_t target_mode)
{

    uint8_t mode = spi_read_rfm69_rt(REG_OP_MODE);
    mode &= ~VAL_OPMODE_MASK;
    mode |= (target_mode & VAL_OPMODE_MASK);
    spi_write_rfm69_rt(REG_OP_MODE, mode);
}

void wait_tx_sent()
{
    while (TX_NOT_SENT)
        ;
}

uint8_t hash(const char* str, uint8_t min, uint8_t max)
{
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + (unsigned char)(*str);
        str++;
    }

    unsigned int range = max - min + 1;
    return (hash % range) + min;
}

bool wait_rx_payload_ready_timeout(uint16_t attempts)
{
    set_rfm69_rx_mode();
    uint16_t counter = 0;
    while (1) {
        _delay_ms(1);
        WHILE_BREAK(counter, attempts);
        if (RX_PAYLOAD_READY) {
            return true;
            break;
        }
    }
    return false;

    ;
}

void wait_rx_payload_ready()
{

    while (RX_PAYLOAD_NOT_READY) { };
}

void wait_rfm69_mode_ready()
{
    while (MODE_NOT_READY)
        ;
}

void set_rfm69_tx_mode()
{
    set_rfm69_power_amp_boost();
    set_rfm69_mode(VAL_OPMODE_TX);
    wait_rfm69_mode_ready();
};

void set_rfm69_rx_mode()
{
    set_rfm69_power_amp_normal();
    set_rfm69_mode(VAL_OPMODE_RX);
    wait_rfm69_mode_ready();
};

void set_rfm69_standby()
{
    set_rfm69_power_amp_normal();
    set_rfm69_mode(VAL_OPMODE_STDBY);
    wait_rfm69_mode_ready();
}

void set_rfm69_sleep()
{
    set_rfm69_power_amp_normal();
    set_rfm69_mode(VAL_OPMODE_SLEEP);
    wait_rfm69_mode_ready();
}

void set_rfm69_idle()
{
    set_rfm69_power_amp_normal();
    set_rfm69_mode(VAL_OPMODE_STDBY);
    wait_rfm69_mode_ready();
}

void reset_rfm69()
{
    rfm69_reset_state(true);
    _delay_ms(10);
    rfm69_reset_state(false);
    _delay_ms(10);
}

void set_rfm69_tx_power()
{
    uint8_t PA_LEVEL_SET
        = VAL_PALEVEL_PA1_ON | VAL_PALEVEL_PA2_ON | ((20 + 14) & VAL_PALEVEL_PA1_OUTPUTPOWER);
    spi_write_rfm69_rt(REG_PA_LEVEL, PA_LEVEL_SET);
}

void rfm69_init()
{
    reset_rfm69();
    _delay_ms(100);
    set_rfm69_idle();
    spi_write_rfm69_rt(REG_FREQ_MSB, VAL_FREQ_433MHz_MSB);
    spi_write_rfm69_rt(REG_FREQ_MIDDLE_SB, VAL_FREQ_433MHz_MID_SB);
    spi_write_rfm69_rt(REG_FREQ_LSB, VAL_FREQ_433MHz_LSB);

    spi_write_rfm69_rt(REG_FREQ_DEV_MSB, VAL_FREQ_DEV_MSB);

    spi_write_rfm69_rt(
        REG_FIFO_THRESH,
        VAL_TX_START_FIFO_NOT_EMPTY | VAL_FIFO_LEVEL_INTERRUPT); // TX condition
    spi_write_rfm69_rt(REG_TEST_DAGC,
                       VAL_TEST_DAGC_DEFAULT); // Fading margin improvement

    char sync_words[] = { 0x2d, 0xd4 };
    spi_write_rfm69_multiple_rt(REG_SYNC_VALUE_1, sync_words, 2);
    spi_write_rfm69_rt(REG_SYNC_CONFIG, VAL_SYNCWORDS_ON | VAL_SYNCWORDS_SIZE_2_BYTES);

    spi_write_rfm69_rt(REG_DATA_MODUL,
                       VAL_DATA_PACKET_MODE | VAL_DATA_MODUL_OOK); // RegDataModul

    spi_write_rfm69_rt(REG_BITRATE_MSB,
                       VAL_BITRATE_250kbps_MSB); // RegBitrateMSB
    spi_write_rfm69_rt(REG_BITRATE_LSB,
                       VAL_BITRATE_250kbps_LSB); // RegbBitrateLSB
    spi_write_rfm69_rt(REG_FDEV_MSB, 0x10); // RegFdevMSB
    spi_write_rfm69_rt(REG_FDEV_LSB, 0x00); // RegFdevLSB

    spi_write_rfm69_rt(REG_RX_BW, 0xE0); // RegRxBw
    spi_write_rfm69_rt(REG_AFC_BW, 0xE0); // RegAfcBw

    spi_write_rfm69_rt(
        REG_PACKET_CONFIG_1,
        VAL_PACKET_VARIABLE_LENGTH | VAL_PACKET_WHITENING | VAL_PACKET_CRCON); // RegPacketConfig1

    spi_write_rfm69_rt(REG_PREAMBLE_MSB, 0x00); // RegPreambleMSB
    spi_write_rfm69_rt(REG_PREAMBLE_LSB, 0x04); // RegPreambleLSB

    spi_write_rfm69_rt(REG_PA_LEVEL,
                       VAL_PA_PA1_ON | VAL_PA_PA2_ON | VAL_PA_20dB); // RegPaLevel
}
