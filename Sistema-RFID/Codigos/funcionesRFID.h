#ifndef FUNCIONESRFID_H
#define FUNCIONESRFID_H


// Declaración de las funciones
void config_wifi();
void config_google();
void config_moduloNFC();
void leerUIDTarjetaRFID();


// Funcion: Configuracion de la conexion WiFi
void config_wifi(){
  delay(10);
  WiFi.begin(ssid, password);
  Serial.println("Conectando WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    
  }
  Serial.println('\n');
  Serial.println("Conexion WiFi establecida!");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

// Funcion: Configuracion de la conexion con el modulo NFC PN532
// Inicializa el módulo PN532 para la interfaz I2C
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);
void config_moduloNFC(){
 
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("No se encontró la placa PN53x");
    while (1); // Detener si no se encuentra el módulo
  }
  
  // Configura el PN532 para leer tarjetas RFID con un rango de 2 cm (nfc.DIRECTIVE_MAX_RESPONSE_TIME_MS)
  nfc.SAMConfig();
  
  Serial.println("Esperando una tarjeta RFID...");

}

// Funcion: media
uint8_t customMin(uint8_t a, uint8_t b) {
  return a < b ? a : b;
}

// Funcion: Lectura del UID de las tarjetas con el modulo NFC PN532
void leerUIDTarjetaRFID(){
  
  uint8_t success;
  uidLength = sizeof(uid); // Inicializa la longitud del UID
  
  // Espera a que se detecte una tarjeta y actualiza uidLength con la longitud real del UID
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  // Imprimir y almacenar los primeros 4 bytes del UID
  if (success) {
    Serial.println("Se encontró una tarjeta RFID!");
    //Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID Value (first 4 bytes): ");
    for (uint8_t i = 0; i < customMin(uidLength, NUM_BYTES_TO_COPY); i++) {
      firstFourBytes[i] = uid[i];
      Serial.print(firstFourBytes[i], HEX); // Imprimir el byte en hexadecimal
      Serial.print(" ");
    }
    Serial.println("");

    delay(500); // Espera medio segundo antes de leer la próxima tarjeta
  }

}

// Funcion: Configuración para establecer conexión con Google Sheets.
void config_google(){
    // establecer una conexión HTTPS con el servidor de Google Sheets.
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Conectando al servidor de Google Sheets... ");
  Serial.println(host);

  //  intenta establecer la conexión con el servidor, con un máximo de 5 intentos
  bool flag = false;
  for (int i=0; i<5; i++){ 
    int retval = client->connect(host, httpsPort);
    if (retval == 1){
       flag = true;
       Serial.println("Conectado a Google Sheets");
       break;
    }
    else
      Serial.println("Fallo la conexion al servidor de Google Sheets. Retrying...");
  }
  if (!flag){
    Serial.print("No se pudo conectar al servidor: ");
    Serial.println(host);
    return;
  }

}







#endif 