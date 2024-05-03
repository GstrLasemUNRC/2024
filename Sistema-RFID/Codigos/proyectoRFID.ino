#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PN532.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

#include "ConstantesRFID.h"
#include "funcionesRFID.h"


void setup() {

  Serial.begin(9600);        
  delay(10);
  Serial.println('\n');
  
  pinMode(ledPin, OUTPUT);

  // Conexion WiFi
  config_wifi();
  // Conexion con el modulo P5N3
  config_moduloNFC();
  // Conexion con Google Sheets
  config_google();

}


void loop() {
  // Leer UID de la tarjeta RFID
  String uidString = leerUIDTarjetaRFID();
  Serial.println("UIDleido: ");
  Serial.println(uidString);
  
  // Leer Sheets y buscar una coincidencia en la columna UIDtag
  leer_columnaUIDtag(uidString);
  
  // Leer en una celda puntual
  
  leer_sheet(fila, Nombredog);
  Serial.println("Nombre: ");
  Serial.println(valorLeido);
  
  leer_sheet(fila, Edaddog);
  Serial.println("Edad (Años): ");
  Serial.println(valorLeido);

}
