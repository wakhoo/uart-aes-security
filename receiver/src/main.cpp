#include <Arduino.h>
#include <AESLib.h>

AESLib aesLib;

/*
    * [AES-128 Key]
    * 16 bytes = 128 bits
    * Sender and Receiver must share the exact same key.
    * WARNING: Hardcoded key is not safe for production.
    * Consider storing in EEPROM instead.
 */
byte key[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
               0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

/*
    * [IV - Initialization Vector]
    * Used in CBC mode (Cipher Block Chaining) : XORed with the first plaintext block before encryption.
    * Same IV must be used on both sender and receiver side.
 */
// byte iv[]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

byte iv_received[16];
byte encrypted[16];
byte decrypted[16];

void setup()
{
    Serial.begin(9600);
    aesLib.set_paddingmode((paddingMode)0);
}
/*
     * paddingMode 0 = No padding
     * Input data must be exactly 16 bytes (one AES block).
 */

void loop()
{
    if (Serial.available() >= 32) {

        for (int i = 0; i < 16; i++) {
            iv_received[i] = Serial.read();
        }

        for (int i = 0; i < 16; i++) {
            encrypted[i] = Serial.read();
        }

        byte iv_tmp[16];
        memcpy(iv_tmp, iv_received, 16);
        aesLib.decrypt(encrypted, 16, decrypted, key, 128, iv_tmp);

        Serial.print("[IV]  ");
        for (int i = 0; i < 16; i++) {
            if (iv_received[i] < 0x10) Serial.print("0");
            Serial.print(iv_received[i], HEX);
            Serial.print(" ");
        }

        Serial.print("\n[ENC] ");
        for (int i = 0; i < 16; i++) {
            if (encrypted[i] < 0x10) Serial.print("0");
            Serial.print(encrypted[i], HEX);
            Serial.print(" ");
        }

        Serial.print("\n[DEC] ");
        Serial.println((char*)decrypted);
        Serial.println("---");
    }
}

/*
    memcpy(iv_tmp, iv, 16);
    * [IV Copy]
    * aesLib.decrypt() modifies the IV internally during CBC decryption.
    * To keep the original iv[] intact for the next iteration,
    * we pass a temporary copy iv_tmp instead.

    aesLib.decrypt(input, length, output, key, key_bits, iv);
*/