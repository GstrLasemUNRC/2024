# Sistema RFID para la Identificación y Seguimiento de Animales

## RESUMEN DEL PROYECTO
El proyecto "Sistema RFID para la Identificación y Seguimiento de Animales" es una solución innovadora que busca mejorar la gestión de refugios y hogares de animales. La idea principal es utilizar tecnología RFID (Radio-Frequency Identification) para crear un registro completo de los animales que ingresan al refugio. Cada animal recibe un llavero RFID con un número de identificación único. Cuando los llaveros que llevan los animales son escaneados por los lectores RFID, se registra automáticamente su entrada y salida en una base de datos centralizada.
También incorpora funciones avanzadas, como alarmas que alertan cuando un animal necesita revisión médica o cuidados especiales. Además, permite agregar datos detallados de los adoptantes, lo que facilita la administración de adopciones y el seguimiento de la historia de cada animal.
Se empleará un sistema de visualización y gestión de datos. Esto garantizará la accesibilidad y la flexibilidad en la administración de la información.
Este sistema RFID no solo simplifica la identificación y seguimiento de animales, sino que también mejora la atención y el cuidado de los mismos en refugios y hogares, contribuyendo así al bienestar de los animales y a una gestión más eficiente de las instalaciones.

## Diseño del sistema
El sistema cuenta con tres partes fundamentales :
- módulo RFID (permite leer y grabar los códigos RFID).
- Base de datos (base de datos en donde se guardarán todos los registros de las identidades de los animales).
- Aplicación Web (aplicación que permite a los usuarios verificar si un animal está registrado o no, así como realizar el registro y monitoreo de la información).


## Desarrollo de Prototipo

### Módulo RFID

El  módulo RFID es el encargado de  realizar la lectura y grabacion de los codigos RFID. Los elementos esenciales son:
- módulo NFC
- Lolin wemos D1 mini pro
- Llaveros RFID  

Se utiliza el módulo NFC para  realizar lecturas y escrituras, ya que es compatible con la tecnología RFID. 

**Funcionamiento del módulo RFID**

1. Leer la tarjeta RFID.
2. Acceder a la hoja de datos de Google.
3. Comparar el UID  de la tarjeta leida con el almacenado en la base de datos.

5. Si coincide, extraer los datos de las celdas que contengas el nombre y edad del animal.
6. Guardar estos datos en una variable temporal.
7. Mostrar por pantalla los datos del animal.
4. Mostrar en la pantalla OLED los datos escenciales si hay coincidencia. De lo contrario solo mostrar el UID de la tarjeta leida.

#### Implementación del módulo RFID
**Conexion del módulo**

Se opta por una conexion I2C con Lolin wemos D1 mini pro.

Tabla  de pinout:
|Lolin |NFC      |
|--------|---------|
|GND      |GND     |
|5V       |VCC     |
|SDA (GPIO 4) |TX      |
|SCL (GPIO 5) |RX      |

La comunicacion I2C funciona de 3.3V a 24V TTL.

**Programación del módulo RFID**

Se procede  a programar el microcontrolador ESP8266 utilizando Arduino IDE. Se instalan las librerias  necesarias para trabajar y se incluyen en los scripts correspondientes.   

Se inicia con la conexión a la red WiFi, seguido de la conexión al módulo PN532 para la interfaz I2C y la lectura del UID de las tarjetas. Luego se procede a conectarse a la base de datos de Google Sheets.  Esto se realiza para enviar una solicitud HTTP a tu script de Google Apps Script para obtener los datos de la hoja de cálculo que contienen los UIDtag.

**Codigo para la lectura del UID de la tarjeta RFID**

c++: [ReadUIDtag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/ReadUIDtag.ino) 

**Conexión con Google Sheet**

Pasos  para integrar ESP8266 y Google Spreadsheets:
1. Crear o buscar una hoja de cálculo en Google Drive.
2. Extensiones → App Script.
3. Nombrar el proyecto "leerHoja"
4. Copiar el código leerHoja.gs y pegarlo en el editor de scripts: Código.gs.
5. Establecer permisos y accesos sobre el script. Ingresar a Implementar → Nueva implementación → Aplicación Web. Debemos elegir que se ejecute como nuestro usuario y que cualquier persona incluso los anónimos tengan acceso a la aplicación; luego confirmamos las opciones que se nos presenta.

>Id de implementación: AKfycbwklDiRjiD4TtwZpoXpT1uNreuo9u5Tkq48w536LjiPOmEEz60xfOu3a1fhb51yFcks3g

>Aplicación web URL
https://script.google.com/macros/s/AKfycbwklDiRjiD4TtwZpoXpT1uNreuo9u5Tkq48w536LjiPOmEEz60xfOu3a1fhb51yFcks3g/exec

6. en el variable script .ino reemplazamos XXXXXXXXXXXXXXXXXXXXX por la correspondiente que nos otorgo Google Script.

**Codigo para leer datos en Google Sheets**

c++: [ReadSheets.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/ReadSheets.ino) 

**Codigo para mostrar datos en la pantalla OLED**
Nota: La función debe respetar el ingreso de los siguientes argumentos.

void mostrar_datos(String uidString, String Nombre, String Edad) { }


c++: [pantallaOLED.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/pantallaOLED.ino) 



**Codigo general del módulo RFID**

c++: [proyectoRFID.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/proyectoRFID.ino) 

Notas: Faltaria contemplar el hecho de que si NO tiene coincidencia, ademas de mostrar un mensaje, no realice la peticion de las celdas, si no que solo muestre en pantalla el UID leido con un mensaje de que no esta en la base de datos.

## Resultados

En la siguiente imagen se observa en el monitor serial el proceso de conexión a la red WiFi, seguido por la interacción con una tarjeta RFID y la comunicación con el servidor de Google Sheets. Como en este ejemplo que inserto una tarjeta que coincide su UID con el de la base de datos, se extrae tanto el nombre como la edad asociados a esa coincidencia.

![Imagen 0](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Imagenes/imagen_0.png)

![Video 0](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Imagenes/gif_0.gif)



## ANEXO

**Formato NDEF**

El formato NDEF (NFC Data Exchange Format) es un estándar utilizado en la tecnología NFC (Near Field Communication) para intercambiar datos entre dispositivos compatibles con NFC, como teléfonos inteligentes, tarjetas NFC y lectores NFC.

Los elementos principales del formato NDEF:

- Mensaje NDEF (NDEF Message): Es la unidad básica de datos en el formato NDEF. Un mensaje NDEF puede contener uno o más registros NDEF.

- Registro NDEF (NDEF Record): Es una estructura de datos que contiene información específica. Cada registro NDEF consta de varios campos:
- - TNF (Type Name Format): Especifica el formato del tipo de registro.
- - Tipo (Type): Indica el tipo de datos contenidos en el registro.
- - ID: Identificador opcional para el registro.
- - Carga útil (Payload): Los datos reales que se transfieren entre dispositivos NFC.  
- Tipos de registros NDEF comunes:
- - Well Known (Conocido): Utilizado para tipos de registros ampliamente conocidos, como texto, URI (Identificador de Recurso Uniforme) y MIME.
- - URI (Identificador de Recurso Uniforme): Contiene una URL.
- - Texto: Contiene texto legible por humanos, junto con un código de idioma.
- - MIME (Multipurpose Internet Mail Extensions): Utilizado para tipos de datos específicos, como imágenes, audio y video.

En este proyecto, se opta por utilizar el formato NDEF para la escritura en las tarjetas RFID. Los registros NDEF de tipo texto se utilizan para almacenar información relacionada con los animales, como su identificación y detalles relevantes.

**Codigo para formatear tarjeta RFID**

c++: [FormatTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/FormatTag.ino)    

**Codigo para la lectura de la tarjeta RFID**

c++: [ReadTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/ReadTag.ino)    

**Codigo para grabar tarjeta RFID**

c++: [WriteTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/WriteTag.ino)  

**Codigo para escribir datos a Google Sheets**

c++: [WriteSheets.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/WriteSheets.ino) 

junto con el codigo modificarHoja.gs

Notas: 
POST: Se utiliza para enviar el UID de la tarjeta RFID desde el dispositivo Arduino al script de Google Apps Script para que se pueda comparar con los datos almacenados en Google Sheets.  En una solicitud POST, los datos se envían al servidor en el cuerpo del mensaje HTTP. Esto significa que los datos se envían de manera "oculta" al usuario, ya que no aparecen en la URL.  
GET: Es opcional y se puede utilizar para recuperar todos los datos de la hoja de cálculo como respuesta a una solicitud GET. En este caso, se puede usar para obtener los datos de la hoja de cálculo si fuese necesario procesarlos en el Arduino. En una solicitud GET, los datos se envían al servidor a través de la URL como parámetros de consulta. Estos parámetros son visibles en la barra de direcciones del navegador.







## Bibliografía

**Google Sheet**  
https://www.gsampallo.com/2019/10/22/esp8266-y-google-spreadsheets/   
https://github.com/StorageB/Google-Sheets-Logging 
