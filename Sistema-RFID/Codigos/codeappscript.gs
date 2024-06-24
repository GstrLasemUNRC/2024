// Funciones vinculadas al sheet. Contempla funciones que interactuan con la lolin y otras con la app.


// Función para procesar solicitudes POST
function doPost(e) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName('Hoja1'); // Reemplaza 'Hoja1' por el nombre de tu hoja de cálculo

  // Obtener el valor enviado desde Arduino
  var uid = e.parameter.uid; // Asegúrate de que 'uid' coincida con el nombre del parámetro enviado desde Arduino

  // Realizar la comparación con los datos en la columna 'UIDtag'
  var data = sheet.getRange('B:B').getValues(); // Asume que los UID están en la columna A
  var coincidencia = false;
  for (var i = 0; i < data.length; i++) {
    if (data[i][0] == uid) { // Asume que los UID en la hoja de cálculo están en formato de texto
      coincidencia = true;
      break;
    }
  }

  // Devolver una respuesta al dispositivo Arduino
  if (coincidencia) {
    return ContentService.createTextOutput("Coincidencia encontrada");
  } else {
   //return ContentService.createTextOutput("No se encontró coincidencia");
    return ContentService.createTextOutput(JSON.stringify(data)).setMimeType(ContentService.MimeType.JSON);

  }
}

// Función para procesar solicitudes GET y devolver el valor de una celda específica
function doGet(e) {
  var rowIndex = e.parameter.rowIndex; // Obtener el índice de fila de la solicitud
  var colIndex = e.parameter.colIndex; // Obtener el índice de columna de la solicitud

  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName('Hoja1'); // Reemplaza 'Hoja1' por el nombre de tu hoja de cálculo

  var valorCelda = sheet.getRange(rowIndex, colIndex).getValue(); // Obtener el valor de la celda en la fila y columna especificadas

  return ContentService.createTextOutput(valorCelda); // Devolver el valor de la celda como texto
}

// Función para borrar o modificar filas
function BorrarFila(Vcasilla) {
  var ValorId    = Vcasilla.values[1];// En esta variable se almacena el valor del UIDtag que se introduce en el campo de texto
  
  var tarea = Vcasilla.values[17];     // En esta variable se almacena el valor del nuevo campo BORRAR
  
  var HojaCalculo  = SpreadsheetApp.getActiveSheet(); // Almacena en esta variable el Id de la pagina excel de Google
  
  var values = HojaCalculo.getDataRange().getValues(); // Esta variable almacena todos los datos de la hoja 
  
  Logger.clear();
  Logger.log('tarea=' + tarea);// Recoge el valor temporalmente de la casilla tarea.

  if (tarea == "BORRAR"){ //Si el valor de tarea es borrar
    
      Logger.log('BORRAR ' + ValorId);  // Recoge el valor temporalmente de BORRAR y el valor de la casilla 1 (ValorId).
    
  for(var row = values.length -1; row >= 0; --row){ //Un bucle For que mira desde la ultima fila generada hasta la ultima o 0
    
    if (values[row][1] == ValorId){ // En cada fila comprueba que el valor de la casilla Id es igual al valor de la variable (ValorId)
      
      HojaCalculo.deleteRow(parseInt(row)+1); // Si la condición anteriormente evaluada es cierta entonces borra la fila
    }
  } 
    
  }else{// Si el valor de tarea no es borrar
  var lastRow = values.length - 1;

  // Borra desde la columna 18
  HojaCalculo.getRange(parseInt(lastRow)+1, 18).clear();

  // Borra todas las entradas
  for(var row = lastRow - 1; row >= 0; --row){
    if (values[row][1] == ValorId){
      HojaCalculo.deleteRow(parseInt(row)+1); 

}