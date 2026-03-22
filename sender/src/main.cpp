#include <Arduino.h>
#include <AESLib.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

AESLib aesLib;

byte key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
               0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

// byte iv[]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//For test - iv

char msg[] = "HELLO";
byte encrypted[16];

void generateIV(byte* iv) {
    for (int i = 0; i < 16; i++) {
        iv[i] = random(0, 256);
    }
}

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
    aesLib.set_paddingmode((paddingMode)0);
    randomSeed(analogRead(0));
}

void loop()
{
    byte iv[16];
    generateIV(iv);

    byte iv_tmp[16];
    memcpy(iv_tmp, iv, 16);

    aesLib.encrypt((byte*)msg, sizeof(msg), encrypted, key, 128, iv_tmp);

    mySerial.write(iv, 16);
    mySerial.write(encrypted, 16);
    
Serial.print("[IV]  ");
    for (int i = 0; i < 16; i++) {
        if (iv[i] < 0x10) Serial.print("0");
        Serial.print(iv[i], HEX);
        Serial.print(" ");
    }
    Serial.print("\n[ENC] ");
    for (int i = 0; i < 16; i++) {
        if (encrypted[i] < 0x10) Serial.print("0");
        Serial.print(encrypted[i], HEX);
        Serial.print(" ");
    }
    Serial.println("\n---");

    delay(2000);
}