
#include "rfm69.h"


    void rfm69_set_state(bool state) {
        SET_PIN_OUT(DDRC, DDC2);
        if (!state) {
            SET_PIN_HIGH(PORTC, PC2);
        } else {
            SET_PIN_LOW(PORTC, PC2);
        }
    }

void spi_rfm69_select(bool state)
{
    SET_PIN_OUT(DDRE, DDE2);
    if (!state)
    {
        SET_PIN_HIGH(PORTE, PE2);
    }
    else
    {
        SET_PIN_LOW(PORTE, PE2);
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
    spi_write(reg | 0x80);
    uint8_t data_read = spi_write(val);
    spi_rfm69_select(false);
    return data_read;
}

uint8_t spi_write_rfm69_multiple_rt(uint8_t reg, const char *vals, uint8_t len)
{
    spi_rfm69_select(true);
    uint8_t data_init = spi_write(reg | 0x80);
    while (len--)
        spi_write(*vals++);

    spi_rfm69_select(false);
    return data_init;
}

void stuff()
{
    // Set the frequency to be 424.0
    spi_write_rfm69_rt(REG_FREQ_MSB, VAL_FREQ_MSB);
    spi_write_rfm69_rt(REG_FREQ_MIDDLE_SB, VAL_FREQ_MIDDLE_SB);
    spi_write_rfm69_rt(REG_FREQ_LSB, VAL_FREQ_LSB);

    set_rfm69_idle();

    spi_write_rfm69_rt(0x3c, 0x80 | 0x0f); // TX condition
    spi_write_rfm69_rt(0x6f, 0x30);        // Fading margin improvement

    char sync_words[] = {0x2d, 0xd4};
    spi_write_rfm69_multiple_rt(0x2f, sync_words, 2);
    spi_write_rfm69_rt(0x2e, 0b10001000);

    spi_write_rfm69_rt(0x01, 0b00000100); // Start standby mode
    wait_rfm69_mode_ready();

    spi_write_rfm69_rt(0x02, 0b00000001); // RegDataModul
    spi_write_rfm69_rt(0x03, 0x00);       // RegBitrateMSB
    spi_write_rfm69_rt(0x04, 0x80);       // RegbBitrateLSB
    spi_write_rfm69_rt(0x05, 0x10);       // RegFdevMSB
    spi_write_rfm69_rt(0x06, 0x00);       // RegFdevLSB

    spi_write_rfm69_rt(0x19, 0xE0); // RegRxBw
    spi_write_rfm69_rt(0x1A, 0xE0); // RegAfcBw

    spi_write_rfm69_rt(0x37, 0b11010000); // RegPacketConfig1

    spi_write_rfm69_rt(0x2c, 0x00); // RegPreambleMSB
    spi_write_rfm69_rt(0x2d, 0x04); // RegPreambleLSB

    spi_write_rfm69_rt(0x11, 0b01111111); // RegPaLevel

    spi_write_rfm69_rt(0x55, 0x70);
    spi_write_rfm69_rt(0x5d, 0x7c);

    spi_write_rfm69_rt(0x25, 0x40);

    uint8_t op_mode = spi_read_rfm69_rt(0x01);
    op_mode &= ~0x1c;
    op_mode |= (0x10 & 0x1c);
    spi_write_rfm69_rt(0x01, op_mode); // Start standby mode
    while (!(spi_read_rfm69_rt(0x27) & 0x80))
        ;

    set_rfm69_idle();
    // set_rfm69_tx();
    //             set_rfm69_tx_mode();

    set_rfm69_rx_mode();
    while (1)
    {
        //        uart_print_binary(spi_read_rfm69_rt(0x28),"RFF");
        if ((spi_read_rfm69_rt(0x28) & 0x04) == 0x04)
        {
            //        if (true) {
            rssi = -(int8_t)(spi_read_rfm69_rt(0x24) >> 1); // RSSI is in 0.5db steps
            //
            spi_rfm69_select(true);
            //
            spi_write(0x00);
            len_payload = spi_read();
            // uart_print_uint8(len_payload, "payload size");
            for (uint8_t f = 0; f < len_payload; f++)
            {
                // USART0_sendChar(spi_read());
            }
            // USART0_sendString("\r\n");
            spi_rfm69_select(false);

            set_rfm69_idle();

            spi_rfm69_select(true);

            uint8_t len = 30;
            spi_write(0x00 | 0x80);
            spi_write(len);
            spi_write('j');
            spi_write('k');
            spi_write('l');
            spi_write('m');
            spi_write('a');
            spi_write('b');
            spi_write('c');
            spi_write('d');
            spi_write('e');
            spi_write('f');
            spi_write('g');
            spi_write('h');
            spi_write('z');
            spi_write('y');
            spi_write('a');
            spi_write('b');
            spi_write('c');
            spi_write('d');
            spi_write('e');
            spi_write('f');
            spi_write('g');
            spi_write('h');
            spi_write('z');
            spi_write('y');
            spi_write('a');
            spi_write('b');
            spi_write('c');
            spi_write('d');
            spi_write('e');
            spi_write('f');
            spi_rfm69_select(false);
            set_rfm69_tx();
            spi_write_rfm69_rt(0x25, 0x00);
            set_rfm69_tx_mode();
            // uart_print_binary(spi_read_rfm69_rt(0x28), "#3 is packet sent-A");
            while (!(spi_read_rfm69_rt(0x28) & 0x08))
                ;
            // uart_print_binary(spi_read_rfm69_rt(0x28), "#3 is packet sent-B");
            set_rfm69_rx_mode();
        };
        //        uart_print_binary(spi_read_rfm69_rt(0x28),"IS FULL");
        //        _delay_ms(10);
        //        uart_print_binary(spi_read_rfm69_rt(0x00),"Hey");
        //        spi_rfm69_select(true);
        //        spi_write(0x00);
        //        uart_print_uint8(spi_read(0xFF),"NUM_CHARS");
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        //        USART0_sendChar(spi_read(0xFF));
        spi_rfm69_select(false);
    }
}