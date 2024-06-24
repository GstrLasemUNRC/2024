#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display = Adafruit_SSD1306(128,64, &Wire); // 128,64 //64 32

#include <Adafruit_PN532.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

#include "ConstantesRFID.h"
#include "funcionesRFID.h"

void setup() {
  // Comunicacion serial
  Serial.begin(9600);        
  delay(10);
  Serial.println('\n');
  
  // Conexion Oled
  config_oled();
  displayoled("Inicializando","...");
 

  // Conexion WiFi
  displayoled("Conectando", "WiFi...");
  config_wifi();
  // Conexion con el modulo P5N3
  displayoled("Conectando", "NFC...");
  config_moduloNFC();
  // Conexion con Google Sheets
  displayoled("Conectando", "Sheets...");
  config_google();

  displayoled("Esperando", "Tag...");

 

}


void loop() {
  // Leer UID de la tarjeta RFID
  String uidString = leerUIDTarjetaRFID();
  Serial.println("UIDleido: ");
  Serial.println(uidString);

  if (uidString != "") {
    // Leer Sheets y buscar una coincidencia en la columna UIDtag
    displayoled("BuscandoID", uidString);
    leer_columnaUIDtag(uidString);
    
    // Si se encontró una coincidencia
    if (fila > 0) {
      // Leer en una celda puntual
      leer_sheet(fila, dogID);
      Serial.println("ID dog: ");
      Serial.println(valorLeido);
      valorLeido2=valorLeido;
  
      leer_sheet(fila, Nombredog);
      Serial.println("Nombre: ");
      Serial.println(valorLeido);
  
      pantalla(uidString, valorLeido2, valorLeido);
      delay(9000);
    } else {
      displayoled("Tag no ", "encontrado");
      delay(2000);
      displayoled("UIDleido: ", uidString);
      delay(3000);
    }
  } else {
    displayoled("Esperando","Tag...");
  }

  delay(1000); // Espera antes de leer la proxima tarjeta

  String valorLeido = "";
  String valorLeido2 = "";


}


