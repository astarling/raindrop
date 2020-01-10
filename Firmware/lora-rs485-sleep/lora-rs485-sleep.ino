/*******************************************************************************
 * The Things Network - Sensor Data Example
 * 
 * Example of sending a valid LoRaWAN packet with DHT22 temperature and
 * humidity data to The Things Networ using a Feather M0 LoRa.
 * 
 * Learn Guide: https://learn.adafruit.com/the-things-network-for-feather
 * 
 * Copyright (c) 2015 Thomas Telkamp and Matthijs Kooijman
 * Copyright (c) 2018 Terry Moore, MCCI
 * Copyright (c) 2018 Brent Rubell, Adafruit Industries
 * 
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *******************************************************************************/
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <ModbusMaster.h>
#include <RTCZero.h>

ModbusMaster sensor;


#define DE 0
#define RE 1

#define LED_WAN 18
#define LED_SENSOR 17
#define LED_BATT 16
#define RS_485_EN 2


RTCZero rtc;

void alarmMatch() {
}

void preTransmission() {
  digitalWrite(RE, HIGH);
  digitalWrite(DE, HIGH);
}

void postTransmission() {
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
}

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
static const u1_t PROGMEM APPEUI[8] = { 0x67, 0x29, 0x02, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 };
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}

// This should also be in little endian format, see above.
static const u1_t PROGMEM DEVEUI[8] = { 0x92, 0x6A, 0xA0, 0xC2, 0xAF, 0x2D, 0x7D, 0x00 };
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}

// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from the TTN console can be copied as-is.
static const u1_t PROGMEM APPKEY[16] = { 0x22, 0xB0, 0x7C, 0x46, 0x58, 0xD3, 0x55, 0xD9, 0x4C, 0x57, 0x5C, 0xB0, 0x29, 0x26, 0x87, 0x4E };
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

// payload to send to TTN gateway
static uint8_t payload[5];
static osjob_t sendjob;





// Schedule TX every this many seconds (might become longer due to duty
// cycle limitations).
const unsigned TX_INTERVAL = 1;



const lmic_pinmap lmic_pins = {
  .nss = 8,                // Internal connected
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 4,                // Internal connected
  .dio = {3, 9, LMIC_UNUSED_PIN},    // Connect "i01" to "5"
                    // Connect "D2" to "6"
  .rxtx_rx_active = 0,
  .rssi_cal = 8,              // LBT cal for the Adafruit Feather M0 LoRa, in dB
  .spi_freq = 8000000,
};

void goToSleep() {

    LMIC_shutdown();
    SPI.end();

    pinMode(22, INPUT_DISCONNECTED);
    pinMode(23, INPUT_PULLUP);
    pinMode(24, INPUT_PULLUP);
    
    pinMode(4, INPUT_DISCONNECTED);
    pinMode(8, INPUT_PULLUP);
    pinMode(3, INPUT_DISCONNECTED);
    pinMode(9, INPUT_DISCONNECTED);

    pinMode(LED_WAN, INPUT_DISCONNECTED);
    pinMode(LED_SENSOR, INPUT_DISCONNECTED);
    pinMode(LED_BATT, INPUT_DISCONNECTED);
    pinMode(RS_485_EN, INPUT_DISCONNECTED);

    pinMode(RE, INPUT_DISCONNECTED);
    pinMode(DE, INPUT_DISCONNECTED);
        
    
    rtc.setAlarmEpoch(rtc.getEpoch() + TX_INTERVAL);
    rtc.standbyMode();
    
    pinMode(LED_WAN, OUTPUT);
    pinMode(LED_SENSOR, OUTPUT);
    pinMode(LED_BATT, OUTPUT);
    
    pinMode(RS_485_EN, OUTPUT);

    digitalWrite(LED_BATT, HIGH);
    delay(1000);
    digitalWrite(LED_BATT, LOW);

}

void onEvent (ev_t ev) {
    Serial.print(os_getTime());
    Serial.print(": ");
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            // TTN uses SF9 for its RX2 window.
            LMIC.dn2Dr = EU868_DR_SF9;
            break;
        case EV_JOIN_TXCOMPLETE:
            Serial.println(F("EV_JOIN_TXCOMPLETE"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            {
              u4_t netid = 0;
              devaddr_t devaddr = 0;
              u1_t nwkKey[16];
              u1_t artKey[16];
              LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);
              Serial.print("netid: ");
              Serial.println(netid, DEC);
              Serial.print("devaddr: ");
              Serial.println(devaddr, HEX);
              Serial.print("artKey: ");
              for (int i=0; i<sizeof(artKey); ++i) {
                if (i != 0)
                  Serial.print("-");
                Serial.print(artKey[i], HEX);
              }
              Serial.println("");
              Serial.print("nwkKey: ");
              for (int i=0; i<sizeof(nwkKey); ++i) {
                      if (i != 0)
                              Serial.print("-");
                      Serial.print(nwkKey[i], HEX);
              }
              Serial.println("");
            }
            // Disable link check validation (automatically enabled
            // during join, but because slow data rates change max TX
      // size, we don't use it in this example.
            LMIC_setLinkCheckMode(0);
            break;
        case EV_RFU1:
             Serial.println(F("EV_RFU1"));
             break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
            break;
        case EV_TXCOMPLETE:            
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            digitalWrite(LED_WAN, LOW);
            
            if (LMIC.txrxFlags & TXRX_ACK)
              Serial.println(F("Received ack"));
            if (LMIC.dataLen) {
              Serial.println(F("Received "));
              Serial.println(LMIC.dataLen);
              Serial.println(F(" bytes of payload"));
            }
          
            goToSleep();
                              
            //os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            do_send(&sendjob);
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
        case EV_SCAN_FOUND:
            Serial.println(F("EV_SCAN_FOUND"));
            break;
        
        case EV_TXSTART:
            Serial.println(F("EV_TXSTART"));
            digitalWrite(LED_WAN, HIGH);
            break;
        default:
            Serial.print(F("Unknown event: "));
            Serial.println((unsigned) ev);
            LMIC_reset();
            do_send(&sendjob);
            break;
    }
}

void do_send(osjob_t* j){
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        LMIC_setTxData2(1, payload, 0, 0);
    }
    // Next TX is scheduled after TX_COMPLETE event.
}


void setup() {
    pinMode(DE, OUTPUT);//de
    pinMode(RE, OUTPUT);//~re
    pinMode(LED_WAN, OUTPUT);
    pinMode(LED_SENSOR, OUTPUT);
    pinMode(LED_BATT, OUTPUT);
    
    pinMode(RS_485_EN, OUTPUT);
    digitalWrite(RS_485_EN, HIGH);

    digitalWrite(RE, LOW);
    digitalWrite(DE, HIGH);
    delay(1000);
    digitalWrite(RE, HIGH);
    digitalWrite(DE, LOW);

    digitalWrite(LED_WAN, HIGH);
    digitalWrite(LED_SENSOR, HIGH);
    digitalWrite(LED_BATT, HIGH);
    delay(1000);
    digitalWrite(LED_WAN, LOW);
    digitalWrite(LED_SENSOR, LOW);
    digitalWrite(LED_BATT, LOW);
    delay(1000);
        
    Serial1.begin(19200);
    Serial.begin(115200);
    rtc.begin();
    rtc.setEpoch(0);
    rtc.enableAlarm(rtc.MATCH_YYMMDDHHMMSS);
    rtc.attachInterrupt(alarmMatch);
    
    sensor.begin(1, Serial1);
    sensor.preTransmission(preTransmission);
    sensor.postTransmission(postTransmission);

    Serial.println(F("Starting"));


    os_init();
    LMIC_reset(); 
    LMIC_setLinkCheckMode(0);
    LMIC_setDrTxpow(EU868_DR_SF9, 14);

    digitalWrite(RS_485_EN, LOW);

    // Start job (sending automatically starts OTAA too)
//    do_send(&sendjob);
    goToSleep();
}

void loop() {
  // we call the LMIC's runloop processor. This will cause things to happen based on events and time. One
  // of the things that will happen is callbacks for transmission complete or received messages. We also
  // use this loop to queue periodic data transmissions.  You can put other things here in the `loop()` routine,
  // but beware that LoRaWAN timing is pretty tight, so if you do more than a few milliseconds of work, you
  // will want to call `os_runloop_once()` every so often, to keep the radio running.
  os_runloop_once();
}