// rf69 demo tx rx.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client
// with the RH_RF69 class. RH_RF69 class does not provide for addressing
// or reliability, so you should only use RH_RF69 if you do not need the
// higher level messaging abilities.
// It is designed to work with the other example RadioHead69_RawDemo_RX.
// Demonstrates the use of AES encryption, setting the frequency and
// modem configuration.

#include <SPI.h>
#include <RH_RF69.h>

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 434.0

// First 3 here are boards w/radio BUILT-IN. Boards using FeatherWing follow.
#if defined (__AVR_ATmega32U4__)  // Feather 32u4 w/Radio
  #define RFM69_CS    8
  #define RFM69_INT   7
  #define RFM69_RST   4
  #define LED        13

#elif defined(ADAFRUIT_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0_EXPRESS) || defined(ARDUINO_SAMD_FEATHER_M0)  // Feather M0 w/Radio
  #define RFM69_CS    8
  #define RFM69_INT   3
  #define RFM69_RST   4
  #define LED        13

#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)  // Feather RP2040 w/Radio
  #define RFM69_CS   16
  #define RFM69_INT  21
  #define RFM69_RST  17
  #define LED        LED_BUILTIN

#elif defined (__AVR_ATmega328P__)  // Feather 328P w/wing
  #define RFM69_CS    4  //
  #define RFM69_INT   3  //
  #define RFM69_RST   2  // "A"
  #define LED        13

#elif defined(ESP8266)  // ESP8266 feather w/wing
  #define RFM69_CS    2  // "E"
  #define RFM69_INT  15  // "B"
  #define RFM69_RST  16  // "D"
  #define LED         0

#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2) || defined(ARDUINO_NRF52840_FEATHER) || defined(ARDUINO_NRF52840_FEATHER_SENSE)
  #define RFM69_CS   10  // "B"
  #define RFM69_INT   9  // "A"
  #define RFM69_RST  11  // "C"
  #define LED        13

#elif defined(ESP32)  // ESP32 feather w/wing
  #define RFM69_CS   33  // "B"
  #define RFM69_INT  27  // "A"
  #define RFM69_RST  13  // same as LED
  #define LED        13

#elif defined(ARDUINO_NRF52832_FEATHER)  // nRF52832 feather w/wing
  #define RFM69_CS   11  // "B"
  #define RFM69_INT  31  // "C"
  #define RFM69_RST   7  // "A"
  #define LED        17

#endif

/* Teensy 3.x w/wing
#define RFM69_CS     10  // "B"
#define RFM69_INT     4  // "C"
#define RFM69_RST     9  // "A"
#define RFM69_IRQN   digitalPinToInterrupt(RFM69_INT)
*/

/* WICED Feather w/wing
#define RFM69_CS     PB4  // "B"
#define RFM69_INT    PA15 // "C"
#define RFM69_RST    PA4  // "A"
#define RFM69_IRQN   RFM69_INT
*/

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

int16_t packetnum = 0;  // packet counter, we increment per xmission

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1); // Wait for Serial Console (comment out line if no computer)

  pinMode(LED, OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather RFM69 TX Test!");
  Serial.println();

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(NULL);
  rf69.setPromiscuous(true);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}


char HexLookUp[] = "0123456789abcdef";

void bytes2hex(unsigned char *src, char *out, int len) {
    while (len--) {
        *out++ = HexLookUp[*src >> 4];
        *out++ = HexLookUp[*src & 0x0F];
        src++;
    }
    *out = 0;
}


void loop2()
{
  Serial.println("=============STARTING");
  for (int i = 0; i<254; i++) {
    unsigned char addr = i;

    char vin = rf69.spiRead(addr);
    char binary_string[9];

    binary_string[8] = '\0'; // Null-terminate the string

    for (int i = 0; i < 8; i++) {
        binary_string[7 - i] = (vin & (1 << i)) ? '1' : '0';
    }
    Serial.print("    ");
    Serial.print(binary_string);
    Serial.print(" ");
  


     char hex_buff[3];
    bytes2hex(&addr, hex_buff, sizeof (addr));
    Serial.print("0x");
    Serial.println(hex_buff);

  }
delay(2500);
}

void loopx() {

}
void loop() {
  delay(1000);  // Wait 1 second between transmits, could also 'sleep' here!

  char radiopacket[20];
  strncpy(radiopacket,"_",sizeof(radiopacket));
  strncpy(radiopacket, "Hello World #", sizeof("Hello World #"));
  //  "Hello World #";
  itoa(packetnum++, radiopacket+13, 10);
  Serial.print("Sending "); Serial.println(radiopacket);

  // Send a message!
  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  rf69.waitPacketSent();

  // Now wait for a reply
  uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);


}

void Blink(byte pin, byte delay_ms, byte loops) {
  while (loops--) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
  }
}
