

#include "ndef.h"
ndef_message readNDEFText(unsigned char *buf) {
    int addr = 0;
    NDEF_MSG.success = 0;

    if (buf[0] != NDEF_TLV) {
        NDEF_MSG.success = 1;
        return NDEF_MSG;
    }

    if (buf[1] == 0xFF) {
        NDEF_MSG.success = 2;
        return NDEF_MSG;
    };

    // int len_field = buf[1];
    addr = 2;

    // bool is_short_record = (buf[addr] & NDEF_SHORT_RECORD) == NDEF_SHORT_RECORD;
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
    for (uint8_t i = 0; i < type_length; i++) {
        type_value[i] = buf[addr];
        addr += 1; // 6
    }

    type_value[type_length] = 0;
    if (type_value[0] != NDEF_TEXT_RECORD) {
        NDEF_MSG.success = 11;
        return NDEF_MSG;
    };
    if (tnf != TNF_KNOWN) {
        NDEF_MSG.success = 12;
        return NDEF_MSG;
    };

    if (has_id_length && (id_length > 0)) {
        addr += id_length;
    }

    uint8_t lang_str_len = buf[addr];
    addr += lang_str_len;
    addr += 1;
    payload_length -= lang_str_len;     // Language string
    payload_length -= 1;                //  The byte that says how long the language string is
    for (uint8_t i = 0; i < (payload_length); i++) {
        NDEF_MSG.payload[i] = buf[addr];
        addr += 1;
    }

    // NDEF_MSG.payload = payload;
    NDEF_MSG.payload_len = payload_length;
    #if DO_UART
    uart_sendString(NDEF_MSG.payload);
    uart_sendString("\n");
    #endif

    return NDEF_MSG;
};