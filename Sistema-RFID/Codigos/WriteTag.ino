#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup() {
    Serial.begin(9600);
    Serial.println("Escritor NDEF");
    nfc.begin();
}

void loop() {
    Serial.println("\nColoque una etiqueta NFC Mifare Classic formateada en el lector.");
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        //message.addUriRecord("http://arduino.cc");
        message.addTextRecord("Hola, este es un mensaje personalizado.");

        bool success = nfc.write(message);
        if (success) {
          Serial.println("Éxito. Intente leer esta etiqueta con su teléfono.");        
        } else {
          Serial.println("Fallo al escribir.");
        }
    }
    delay(5000);
}