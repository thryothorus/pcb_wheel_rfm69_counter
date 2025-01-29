import os
import pickle
import struct


with open('packet_dump','rb') as ff:
    packet = pickle.load(ff)

def get_3byte_hash(packet):
    hashed = 0;
    for x in packet:
        hashed = (hashed*31 + x)  % 0xFFFFFF

    return hashed

def get_bytes(value):
    return list(value.to_bytes(4, byteorder='little'))
    
to_id = packet[0]
from_id = packet[1]
msg_format = packet[2]
msg_type = packet[3]


name = packet[4:14]
wheel_diameter = packet[14:24]
battery_reading = struct.unpack('<' + 'H', packet[24:26])[0]
time_reading = struct.unpack('<'+'B'*5, packet[26:31])
wheel_counts = struct.unpack('<'+'H'*15, packet[31:61])
b1, b2, b3 = struct.unpack('<BBB',packet[61:64])
hash_from_msg = b1 | b2<<8 | b3<<16
hash_calculated = get_hash(packet[4:61])


if hash_calculated == hash_from_msg:
    print('Hashes match!')

else:
    print("Hashes do not match")




