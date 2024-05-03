 
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
  // lee el UID y almacena los primeros 4 bytes es una variable uint8_t firstFourBytes[NUM_BYTES_TO_COPY]  
  leerUIDTarjetaRFID();


}
