

#include "ndef.h"
ndef_message ndef_msg;
ndef_message readNDEFText(char *buf) {
    int addr = 0;
    ndef_msg.success = 0;

    if (buf[0] != NDEF_TLV) {
        ndef_msg.success = 1;
        return ndef_msg;
    }

    if (buf[1] == 0xFF) {
        ndef_msg.success = 2;
        return ndef_msg;
    };

    int len_field = buf[1];
    addr = 2;

    bool is_short_record = (buf[addr] & NDEF_SHORT_RECORD) == NDEF_SHORT_RECORD;
    bool has_id_length = (buf[addr] & NDEF_ID_LEN) == NDEF_ID_LEN;
    uint8_t tnf = buf[addr] & 0x7;
    addr += 1; // 3

    uint8_t type_length = buf[addr];
    addr += 1; // 4

    uint8_t payload_length = buf[addr];
    addr += 1; // 5

    uint8_t id_length = 0;
    if (has_id_length) {
        id_length = buf[addr];
        addr += 1;
    }

    uint8_t type_value[type_length + 1];
    for (uint8_t i; i < type_length; i++) {
        type_value[i] = buf[addr];
        addr += 1; // 6
    }

    type_value[type_length] = 0;
    if (type_value[0] != NDEF_TEXT_RECORD) {
        ndef_msg.success = 11;
        return ndef_msg;
    };
    if (tnf != TNF_KNOWN) {
        ndef_msg.success = 12;
        return ndef_msg;
    };

    if (has_id_length && (id_length > 0)) {
        addr += id_length;
    }

    uint8_t lang_str_len = buf[addr];
    addr += lang_str_len;
    addr += 1;
    payload_length -= lang_str_len;     // Language string
    payload_length -= 1;                //  The byte that says how long the language string is
    uint8_t payload[payload_length];
    for (uint8_t i; i < (payload_length); i++) {
        ndef_msg.payload[i] = buf[addr];
        addr += 1;
    }

    // ndef_msg.payload = payload;
    ndef_msg.payload_len = payload_length;

    return ndef_msg;
};