
// RED WIFI
// credenciales
const char* ssid     = "2.4GHz_EXT_Lu";
const char* password = "3B77A4D830";

// Google Script Deployment ID:
const char *GScriptId = "AKfycbzlKrX1HpVaIELflssnzJEMn0PbvIMzhorwMtnpKtn9bTy-zBl-2_3fMXCHOHWGQZxVDQ";

// Enter command (insert_row or append_row) and your Google Sheets sheet name (default is Sheet1):
const char* payload_base = "{\"command\": \"insert_row\", \"datosPerros\": \"Hoja1\", \"value0\", \"value1\", \"value2\": ";
char payload[256];

// Google Sheets setup (do not edit)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
const String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

//variables publicadas en Google Sheets
int value0 = 0;
int value1 = 0;
int value2 = 0;