
// Función para procesar solicitudes POST
function doPost(e) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName('Hoja1'); // Reemplaza 'Hoja1' por el nombre de tu hoja de cálculo

  // Obtener el valor enviado desde Arduino
  var uid = e.parameter.uid; // Asegúrate de que 'uid' coincida con el nombre del parámetro enviado desde Arduino

  // Realizar la comparación con los datos en la columna 'UIDtag'
  var data = sheet.getRange('A:A').getValues(); // Asume que los UID están en la columna A
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