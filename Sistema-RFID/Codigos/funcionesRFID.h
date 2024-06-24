#ifndef FUNCIONESRFID_H
#define FUNCIONESRFID_H


// Declaración de funciones
void config_oled();
void config_wifi();
void config_google();
void config_moduloNFC();
String leerUIDTarjetaRFID();
void leer_columnaUIDtag(String uidString);
void leer_sheet(int rowIndex, int colIndex);
void displayoled(String mensaje, String mensaje2);
void pantalla(String uid, String id, String nombre);


// Funcion 1: Configuracion de la conexion WiFi
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

// Funcion 2: Configuracion de la conexion con el modulo NFC PN532
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

// Funcion 3: media
uint8_t customMin(uint8_t a, uint8_t b) {
  return a < b ? a : b;
}

// Funcion 4: Lectura del UID de las tarjetas con el modulo NFC PN532
String leerUIDTarjetaRFID(){
  String uidString = ""; // Inicializa un String vacío para almacenar el UID
  
  uint8_t success;
  uidLength = sizeof(uid); // Inicializa la longitud del UID
  
  // Espera a que se detecte una tarjeta y actualiza uidLength con la longitud real del UID
  displayoled("Esperando","Tag....");
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  // Imprimir y almacenar los primeros 4 bytes del UID
  if (success) {
    Serial.println("Se encontró una tarjeta RFID!");
    //Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID Value (first 4 bytes): ");
    for (uint8_t i = 0; i < customMin(uidLength, NUM_BYTES_TO_COPY); i++) {
      //firstFourBytes[i] = uid[i];
      Serial.print(uid[i], HEX); // Imprimir el byte en hexadecimal
      Serial.print(" ");

      uidString += String(uid[i], HEX); // Agrega cada byte del UID al String
      //uidString += String(uid[i]);
      uidString += "";
    }
    Serial.println("");
    delay(100); // Espera medio segundo antes de leer la próxima tarjeta
  }

  return uidString; // Devuelve el String con el UID leído

}

// Funcion 5: Configuración para establecer conexión con Google Sheets.
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


// Funcion 6: leer la hoja de datos y buscar coincidencia en la columna UIDtag. Solicitud POST.
void leer_columnaUIDtag(String uidString){
  Serial.print("valor de uidStrig en funcion leer_columna: ");
  Serial.println(uidString);
  // Realizar una solicitud HTTP POST al script de Google Apps Script.
  String url = String("/macros/s/") + GScriptId + "/exec"; 
  Serial.print("url en funcion leer_columna: ");
  Serial.println(url);

  // Crear el cuerpo de la solicitud POST
  String postData = "uid=" + uidString;

  // Realizar la solicitud POST
  client->POST(url, host, postData);

  // Leer y procesar la respuesta recibida.
  String response = client->getResponseBody();
  Serial.println("Respuesta del servidor: ");
  Serial.println(response);

  if (response.indexOf(uidString) != -1) {
    Serial.println("El string coincide con los datos de la columna 'UIDtag'");

    // Encontrar la posición de uidString en response
    int index = response.indexOf(uidString);

    // Analizar la estructura de la matriz para determinar la fila correspondiente
    int rowCount = 0;
    int pos = 0;
    while (pos != -1 && pos < index) {
      pos = response.indexOf("[", pos + 1);
      rowCount++;
    }
    int row = rowCount - 1; // Restar 1 para obtener el índice de la fila correcto

    // Imprimir la fila correspondiente
    Serial.print("La coincidencia se encuentra en la fila: ");
    Serial.println(row);
    fila=row; // variable utilizada en la funcion leer_sheet

  } else {
    Serial.println("El string no coincide con los datos de la columna 'UIDtag'");
    fila= -1;
  }

  uidString = ""; 
}


// Funcion 7: Leer en una celda puntual. Se le ingresa la fila donde se encontró la coincidencia del UID. Solicitud GET.
void leer_sheet(int rowIndex, int colIndex) {

  String url = String("/macros/s/") + GScriptId + "/exec?rowIndex=" + String(rowIndex) + "&colIndex=" + String(colIndex);
  // Serial.print("url: ");
  // Serial.print(url);
  client->GET(url, host);
  // Leer y procesar la respuesta recibida.
  String response = client->getResponseBody();
  // Serial.print("Valor en la fila ");
  // Serial.print(rowIndex);
  // Serial.print(" y columna ");
  // Serial.print(colIndex);
  // Serial.print(": ");
  // Serial.println(response);

  // Guardar el valor obtenido
  valorLeido = response;
}

// Funcion 8: Configuracion de la conexion Oled.
void config_oled(){
  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  Serial.println("OLED begun");
 
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  Serial.println("IO test");
  display.setCursor(0,0);
  display.display(); 
}


// Funcion 9: muestra el resultado de la coincidencia del UIDtag.
void pantalla(String uid, String id, String nombre) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(35, 16);
  display.println("UIDtag:");
  display.setCursor(35, 26);
  display.println(uid);
  display.setCursor(35, 36);
  display.println("IDdog:");
  display.setCursor(75, 36);
  display.println(id);
  display.setCursor(35, 46);
  display.println("Nombre:");
  display.setCursor(35, 56);
  display.println(nombre);
  display.display();
  
}

// Funcion 9: visualiza mensajes en la pantalla oled.
void displayoled(String mensaje, String mensaje2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(36, 36);
  display.println(mensaje);
  display.setCursor(36, 46);
  display.println(mensaje2);
  display.display();
}

#endif 