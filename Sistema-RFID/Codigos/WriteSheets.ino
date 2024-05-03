#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

#include "ConstantesRFID.h"
#include "funcionesRFID.h"

//variables publicadas en Google Sheets
int value0 = 0;
int value1 = 0;
int value2 = 0;

void setup() {

  Serial.begin(9600);        
  delay(10);
  Serial.println('\n');
  
  // Conexion WiFi
  config_wifi();
  // Conexion con Google Sheets
  config_google();


}


void loop() {

  // SECCION :  ENVIAR DATOS A Google Sheets.
  // se generan valores de prueba
  value0 ++;
  value1 = random(0,1000);
  value2 = random(0,100000);

  // Se construye una cadena JSON payload que contiene los valores
  snprintf(payload, sizeof(payload), "%s\"%d\",\"%d\",\"%d\"}", payload_base, value0, value1, value2); //  "%s\"%d,%d,%d\"}"
  
  // Publicacion de datos en Google Sheets
  Serial.println("Publicando datos...");
  Serial.println(payload);
  if(client->POST(url, host, payload)){ 
    // si la publicación fue exitosa ...
    Serial.println("Publicación exitosa");
  }
  else{
    Serial.println("Error al publicar datos");
  }
  // se requiere un retraso de varios segundos antes de volver a publicar   
  delay(5000);

  // FIN DE LA SECCION :  ENVIAR DATOS A Google Sheets.
}