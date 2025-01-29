# SPDX-FileCopyrightText: 2018 Brent Rubell for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""
Example for using the RFM69HCW Radio with Raspberry Pi.

Learn Guide: https://learn.adafruit.com/lora-and-lorawan-for-raspberry-pi
Author: Brent Rubell for Adafruit Industries
"""
from datetime import datetime
# Import Python System Libraries
import time
from datetime import datetime
# Import Blinka Libraries
import busio
from digitalio import DigitalInOut, Direction, Pull
import board
# Import the SSD1306 module.
# import adafruit_ssd1306
# Import the RFM69 radio module.
import adafruit_rfm69
# import numpy as np
import ctypes
import struct
import pickle
import os
# # Button A
# btnA = DigitalInOut(board.D5)
# btnA.direction = Direction.INPUT
# btnA.pull = Pull.UP

# # Button B
# btnB = DigitalInOut(board.D6)
# btnB.direction = Direction.INPUT
# btnB.pull = Pull.UP

# # Button C
# btnC = DigitalInOut(board.D12)
# btnC.direction = Direction.INPUT
# btnC.pull = Pull.UP

# # Create the I2C interface.
# i2c = busio.I2C(board.SCL, board.SDA)

# # 128x32 OLED Display
# reset_pin = DigitalInOut(board.D4)
# display = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c, reset=reset_pin)
# # Clear the display.
# display.fill(0)
# display.show()
# width = display.width
# height = display.height

# Configure Packet Radio
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
rfm69 = adafruit_rfm69.RFM69(spi, CS, RESET, 434.0, high_power=True)
prev_packet = None
# Optionally set an encryption key (16 byte AES key). MUST match both
# on the transmitter and receiver (or be set to None to disable/the default).
# rfm69.encryption_key = b'\x01\x02\x03\x04\x05\x06\x07\x08\x01\x02\x03\x04\x05\x06\x07\x08'
rfm69.encryption_key = None;
rfm69.tx_power=20;

def unpack_uint8(m):
    return struct.unpack('B'*len(m), m)

def send_now():
    rfm69.idle()

    n = datetime.now()
    add_this = [n.second,n.minute,n.hour,n.day,n.month,n.year-2000,n.isoweekday()]
    b_ar = bytearray();
    for x in add_this:
        b_ar += ctypes.c_uint8(x)
    msg_send = b_ar;
    
    for i in range(3):
        rfm69.send(msg_send, flags=2, keep_listening = True);  # Date time return request
        time.sleep(0.05);

    print('SENT:\t\t',unpack_uint8(msg_send))
    # print("Sent!", add_this);


send_now();
while True:
    # send_now();
    packet = None
    packet = rfm69.receive(with_header = True)
    if packet is not None:
        #  = packet
        print('====================================')
        print('RECEIVED:\t',unpack_uint8(packet))

        packet_flag = packet[3]
        print('FLAG:\t',packet_flag)
        if packet_flag == 1:
            send_now();

        if packet_flag == 31:
            if not os.path.exists('packet_dump'):
                pickle.dump(packet, open('packet_dump','wb'));

        # print(packet_flag, prev_packet);
        # packet_text = str(prev_packet[4:], "utf-8")
        # print(packet_text)
    # time.sleep(0.01)

