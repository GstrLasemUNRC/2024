// Formatea las etiquetas Mifare Classic como una etiqueta NDEF
// Esto fallará si la etiqueta ya está formateada como NDEF
// nfc.clean convertirá una etiqueta Mifare Classic formateada como NDEF al formato Mifare Classic

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

void setup(void) {
    Serial.begin(9600);
    Serial.println("Formateador NDEF");
    nfc.begin();
}

void loop(void) {
    
    Serial.println("\nColoque una etiqueta Mifare Classic no formateada en el lector.");
    if (nfc.tagPresent()) {

        bool success = nfc.format();
        if (success) {
          Serial.println("\nÉxito, etiqueta formateada como NDEF.");
        } else {
          Serial.println("\nFalló el formato.");
        }

    }
    delay(5000);
}