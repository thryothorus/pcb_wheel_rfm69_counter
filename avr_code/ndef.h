/*
 * File:   ndef.h
 * Author: thebears
 *
 * Created on January 24, 2025, 6:39 PM
 */

#ifndef NDEF_H
#define NDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "defines.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


#define NDEF_TLV 0x03
#define NDEF_SHORT_RECORD (1 << 4)
#define NDEF_ID_LEN (1 << 3)
#define NDEF_TEXT_RECORD 0x54
#define TNF_KNOWN 0x01

ndef_message readNDEFText(char *buf) ;

#ifdef __cplusplus
}
#endif

#endif /* NDEF_H */
