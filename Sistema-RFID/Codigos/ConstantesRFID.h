// RED WIFI
// credenciales
const char* ssid     = "nombredelared";
const char* password = "contraseña";

// Pines del LED
const int ledPin = 13;

// modulo NFC

#define PN532_IRQ   (2)
#define PN532_RESET (3) 

const int NUM_BYTES_TO_COPY = 4; // utilizado para imprimir y almacenar los primeros 4 bytes del UID
uint8_t firstFourBytes[NUM_BYTES_TO_COPY];
#define MAX_UID_LENGTH 4 // Suponiendo una longitud máxima de UID de 7 bytes
uint8_t uid[MAX_UID_LENGTH]; // Declarar uid como un arreglo de uint8_t
uint8_t uidLength; // Longitud del UID leído




// Google Script Deployment ID:
const char *GScriptId = "AKfycbzlKrX1HpVaIELflssnzJEMn0PbvIMzhorwMtnpKtn9bTy-zBl-2_3fMXCHOHWGQZxVDQ";

// Enter command (insert_row or append_row) and your Google Sheets sheet name (default is Sheet1):
const char* payload_base = "{\"command\": \"insert_row\", \"datosPerros\": \"Hoja1\", \"UIDtag\", \"IDdog\", \"Nombre\": ";
char payload[256];

// Google Sheets setup (do not edit)
const char* host = "script.google.com";
const int httpsPort = 443;
const char* fingerprint = "";
const String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

