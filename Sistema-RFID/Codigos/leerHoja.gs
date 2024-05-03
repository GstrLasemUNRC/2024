// Función para procesar solicitudes POST
function doPost(e) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName('Hoja1'); // Reemplaza 'Hoja1' por el nombre de tu hoja de cálculo

  // Obtener el valor enviado desde Arduino
  var valor = e.parameter.valor; // Asegúrate de que 'valor' coincida con el nombre del parámetro enviado desde Arduino

  // Realizar la comparación con los datos en la columna 'UIDtag'
  var data = sheet.getRange('A:A').getValues(); // Asume que los UID están en la columna A
  var coincidencia = false;
  for (var i = 0; i < data.length; i++) {
    if (data[i][0] == valor) { // Asume que los UID en la hoja de cálculo están en formato de texto
      coincidencia = true;
      break;
    }
  }

  // Devolver una respuesta al dispositivo Arduino
  if (coincidencia) {
    return ContentService.createTextOutput("Coincidencia encontrada");
  } else {
    return ContentService.createTextOutput("No se encontró coincidencia");
  }
}

// Función para procesar solicitudes GET (opcional)
function doGet(e) {
  var ss = SpreadsheetApp.getActiveSpreadsheet();
  var sheet = ss.getSheetByName('Hoja1'); // Reemplaza 'Hoja1' por el nombre de tu hoja de cálculo

  // Obtener todos los datos de la hoja de cálculo y devolverlos como JSON
  var data = sheet.getDataRange().getValues();
  return ContentService.createTextOutput(JSON.stringify(data)).setMimeType(ContentService.MimeType.JSON);
}
