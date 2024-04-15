#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup(void) {
    Serial.begin(9600);
    Serial.println("Lector NDEF");
    nfc.begin();
}

void loop(void) {
    Serial.println("\nEscanea una etiqueta NFC\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        tag.print();
    }
    delay(1000);
}
