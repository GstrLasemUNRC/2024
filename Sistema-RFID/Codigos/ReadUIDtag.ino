#include <Wire.h>
#include <Adafruit_PN532.h>

#define PN532_IRQ   (2)
#define PN532_RESET (3) 

// Inicializa el módulo PN532 para la interfaz I2C
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

// Pines del LED
const int ledPin = 13;

// UID de tus tarjetas
#define NUM_TARJETAS 2
#define TARJETA_1 {0x11, 0x22, 0x33, 0x44}
#define TARJETA_2 {0x1D, 0x70, 0xC6, 0xDB}

#define MAX_UID_LENGTH 4 // Suponiendo una longitud máxima de UID de 7 bytes

uint8_t uid[MAX_UID_LENGTH]; // Declarar uid como un arreglo de uint8_t
uint8_t uidLength; // Longitud del UID leído


uint8_t tarjetas[NUM_TARJETAS][4] = {TARJETA_1, TARJETA_2};

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  pinMode(ledPin, OUTPUT);
  
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // Detener si no se encuentra el módulo
  }
  
  // Configura el PN532 para leer tarjetas RFID con un rango de 2 cm (nfc.DIRECTIVE_MAX_RESPONSE_TIME_MS)
  nfc.SAMConfig();
  
  Serial.println("Waiting for an RFID card...");
}

uint8_t customMin(uint8_t a, uint8_t b) {
  return a < b ? a : b;
}

void loop(void) {
  uint8_t success;
  uidLength = sizeof(uid); // Inicializa la longitud del UID

  // Espera a que se detecte una tarjeta y actualiza uidLength con la longitud real del UID
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found an RFID card!");
    Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID Value (first 4 bytes): ");
    for (uint8_t i = 0; i < customMin(uidLength, 4); i++) {
      Serial.print(uid[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");

    // Compara el UID leído con los UID de tus tarjetas
    for (uint8_t i = 0; i < NUM_TARJETAS; i++) {
      if (memcmp(uid, tarjetas[i], customMin(uidLength, 4)) == 0) {
        Serial.println("Tarjeta válida!");
        digitalWrite(ledPin, HIGH); // Enciende el LED
        delay(1000); // Mantén el LED encendido por un segundo
        digitalWrite(ledPin, LOW); // Apaga el LED
      }
    }

    delay(500); // Espera medio segundo antes de leer la próxima tarjeta
  }
}
