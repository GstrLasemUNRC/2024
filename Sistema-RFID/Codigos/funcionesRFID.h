#ifndef FUNCIONESRFID_H
#define FUNCIONESRFID_H


// Declaración de las funciones
void config_wifi();
void config_google();


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
  Serial.println("Conexion establecida!");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

// Funcion: 
void config_google(){
    // establecer una conexión HTTPS con el servidor de Google Sheets.
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Conectando ... ");
  Serial.println(host);

  //  intenta establecer la conexión con el servidor, con un máximo de 5 intentos
  bool flag = false;
  for (int i=0; i<5; i++){ 
    int retval = client->connect(host, httpsPort);
    if (retval == 1){
       flag = true;
       Serial.println("Conectado");
       break;
    }
    else
      Serial.println("Fallo la conexion. Retrying...");
  }
  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    return;
  }

}

#endif 