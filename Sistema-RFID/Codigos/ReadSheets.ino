


// Funcion 6: leer la hoja de datos y buscar coincidencia en la columna UIDtag. Solicitud POST.
void leer_columnaUIDtag(String uidString){

  // Realizar una solicitud HTTP POST al script de Google Apps Script.
  String url = String("/macros/s/") + GScriptId + "/exec"; 

  // Crear el cuerpo de la solicitud POST
  String postData = "uid=" + uidString;

  // Realizar la solicitud POST
  client->POST(url, host, postData);

  // Leer y procesar la respuesta recibida.
  String response = client->getResponseBody();
  // Serial.println("Respuesta del servidor: ");
  // Serial.println(response);

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
