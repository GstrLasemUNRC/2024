# Sistema RFID para la Identificación y Seguimiento de Animales

## RESUMEN DEL PROYECTO
El proyecto "Sistema RFID para la Identificación y Seguimiento de Animales" es una solución innovadora que busca mejorar la gestión de refugios y hogares de animales. La idea principal es utilizar tecnología RFID (Radio-Frequency Identification) para crear un registro completo de los animales que ingresan al refugio. Cada animal recibe un llavero RFID con un número de identificación único. Cuando los llaveros que llevan los animales son escaneados por los lectores RFID, se registra automáticamente su entrada y salida en una base de datos centralizada.
También incorpora funciones avanzadas, como alarmas que alertan cuando un animal necesita revisión médica o cuidados especiales. Además, permite agregar datos detallados de los adoptantes, lo que facilita la administración de adopciones y el seguimiento de la historia de cada animal.
Se empleará un sistema de visualización y gestión de datos. Esto garantizará la accesibilidad y la flexibilidad en la administración de la información.
Este sistema RFID no solo simplifica la identificación y seguimiento de animales, sino que también mejora la atención y el cuidado de los mismos en refugios y hogares, contribuyendo así al bienestar de los animales y a una gestión más eficiente de las instalaciones.

### Diseño del sistema
El sistema cuenta con tres partes fundamentales :
- Modulo RFID (permite leer y grabar los códigos RFID).
- Base de datos (base de datos en donde se guardarán todos los registros de las identidades de los animales).
- Aplicación Web (aplicación que permite a los usuarios verificar si un animal está registrado o no, así como realizar el registro y monitoreo de la información).


### Desarrollo de Prototipo

#### Modulo RFID

El  modulo RFID es el encargado de  realizar la lectura y grabacion de los codigos RFID. Los elementos esenciales son:
- Modulo NFC
- Lolin wemos D1 mini pro
- Llaveros RFID  

Se utiliza el modulo NFC para  realizar lecturas y escrituras, ya que es compatible con la tecnología RFID. 

**Conexion del modulo**

Se opta por una conexion I2C con Lolin wemos D1 mini pro.

Tabla  de pinout:
|Lolin |NFC      |
|--------|---------|
|GND      |GND     |
|5V       |VCC     |
|SDA (GPIO 4) |TX      |
|SCL (GPIO 5) |RX      |

La comunicacion I2C funciona de 3.3V a 24V TTL.

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

**Codigo para formatear tarjeta**

c++: [FormatTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/FormatTag.ino)    

**Codigo para la lectura de la tarjeta**

c++: [ReadTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/ReadTag.ino)    

**Codigo para grabar tarjeta**

c++: [WriteTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/WriteTag.ino)    


**Google Sheet**

https://www.gsampallo.com/2019/10/22/esp8266-y-google-spreadsheets/ 

Pasos  para integrar ESP8266 y Google Spreadsheets:
1. Crear o buscar una hoja de cálculo en Google Drive.
2. Extensiones → App Script.
3. Nombrar el proyecto "modificarHoja"
4. Copiar el código modificarHoja.gs y pegarlo en el editor de scripts: Código.gs.
5. Establecer permisos y accesos sobre el script. Ingresar a Implementar → Nueva implementación → Aplicación Web. Debemos elegir que se ejecute como nuestro usuario y que cualquier persona incluso los anónimos tengan acceso a la aplicación; luego confirmamos las opciones que se nos presenta.

Id de implementación: AKfycbzlKrX1HpVaIELflssnzJEMn0PbvIMzhorwMtnpKtn9bTy-zBl-2_3fMXCHOHWGQZxVDQ

Aplicación web URL
https://script.google.com/macros/s/AKfycbzlKrX1HpVaIELflssnzJEMn0PbvIMzhorwMtnpKtn9bTy-zBl-2_3fMXCHOHWGQZxVDQ/exec 

6. en el variable script reemplazamos XXXXXXXXXXXXXXXXXXXXX por la correspondiente que nos otorgo Google Script.