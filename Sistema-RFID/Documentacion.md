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
- Arduino Nano
- Llaveros RFID  

Se utiliza el modulo NFC para  realizar lecturas y escrituras, ya que es compatible con la tecnología RFID. 

**Conexion del modulo**

Se opta por una conexion I2C con ardiono nano.

Tabla  de pinout:
|Arduino |NFC      |
|--------|---------|
|GND      |GND     |
|5V       |VCC     |
|SDA (A4) |TX      |
|SCL (A5) |RX      |

La comunicacion I2C funciona de 3.3V a 24V TTL.

**Codigo para formatear**

c++: [FormatTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/FormatTag.ino)    

**Codigo para la lectura**

c++: [ReadTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/ReadTag.ino)    

**Codigo para grabar**

c++: [WriteTag.ino](https://github.com/GstrLasemUNRC/2024/blob/main/Sistema-RFID/Codigos/WriteTag.ino)    
