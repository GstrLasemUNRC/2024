function doPost(e) {
   var ss1 = SpreadsheetApp.getActiveSpreadsheet();
   var sheet = ss1.getSheets()[0];

   var fechaHora = Utilities.formatDate(new Date(), "GMT-3", "yyyy-MM-dd HH:mm:ss");
   valor = String(e.parameters.data);
   sheet.appendRow([fechaHora,valor]);
   
   return ContentService.createTextOutput("Completo");
}