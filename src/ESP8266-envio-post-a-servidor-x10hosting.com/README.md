# Estación Meteorológica con IoT

Este proyecto configura el uso de la ESP8266, Un sensor DHT11 y un servidor web.


- [Sitio web del proyecto](https://esp328266.elementfx.com/)
## Tabla de contenidos

- [Investigación](#investigación)
- [Instalación](#instalación)
- [Uso](#Uso)
- [Licencia](#licencia)
- [Contacto](#contacto)
- [Información](#Información)

## Investigación
** Etapa 2: ESP8266 conectado a red Wi-Fi, lectura de temperatura y humedad del DHT11 y envió 
de datos a un servidor web gratis x10hosting.com utilizando un método POST.  **       

Esta es la etapa 2 del proyecto diseñado para el curso IE-0624 Laboratorio de Microcontroladores.
Acá se configura el uso de la placa ESP8266 para que se conecte a red Wi-Fi, se leen los valores de 
temperatura y humedad y se hace envió de datos a un servidor web gratis 000webhost.com utilizando 
el método POST.

El código implementado para la lectura de datos del sensor digital DHT11 a travez de un solo pin de datos fue tomado de un ejemplo proporcionado por la la biblioteca DHT #include "DHT.h" para 
conectarse al sensor, dicho ejemplo fue escrito por ladyada, y es de dominio público. 

El código implementado para que la placa ESP8266 se conecte a red Wi-Fi, utiliza 
las bibliotecas:

ESP8266HTTPClient.h: permite enviar solicitudes HTTP a un servidor y recibir respuestas utilizando 
el protocolo HTTP. La librería se encarga de manejar la conexión y la transmisión de datos a través 
de la red WiFi

ESP8266WiFiMulti.h: permite la gestión de múltiples redes WiFi, busca redes WiFi en orden de 
preferencia y se conecta automáticamente a la primera red disponible.

WiFiClient.h: proporciona métodos para crear un cliente que puede comunicarse con un servidor. 

El código para esta nueva etapa del proyecto incluye una función llamada void EnvioDatos() 
para el envió de los datos de temperatura y humedad a un servidor web gratis x10hosting.com utilizando el método POST. 


** Etapa 3: creación de archivos php que configuren el uso del servidor web gratis x10hosting.com: ** 

El servidor web gratis empleado es: https://x10hosting.com/

Nombre de los archivos y explicación de los mismos: 

* La dirección de los mismos en el servidor web es la carpeta /public_html/
 
- conexion.php: crea una conexión a una base de datos MySQL utilizando la extensión mysqli_connect().
  y establece 4 variables: nombre de usuario, contraseña, nombre del servidor y nombre de la base de datos 
  a la que se quiere conectar.  

- EspPost.php:  código PHP que utiliza una conexión a una base de datos MySQL para insertar registros en una 
  tabla. Si se han enviado los datos, se construye una consulta SQL utilizando la función mysqli_query() para
  insertar los valores de temperatura, humedad y fecha actual en la tabla TB_DHT11. 

- index.php: código que configura una página HTML. La página tiene varios elementos HTML y estilos CSS para 
  mostrar la medición de temperatura y humedad. También se incluye un script PHP para recuperar datos de la
  base de datos y calcular el ángulo correspondiente para los valores de temperatura y humedad en una escala
  de 0° a 180° para mostrar gráficamente los valores en barras de progreso circular diseñadas con estilos CSS.

Todo lo anterior configura el uso de la placa ESP8266 conectada a una red Wi-Fi, que además hace la toma
de lecturas de temperatura y humedad del DHT11 y realiza el envió de dichos datos a un servidor web gratis 
000webhost.com utilizando un método POST, donde se alberga una base de datos que recopila los datos y donde
se configuraron los archivos php para realizar consultas SQL a la base de datos y presentar los datos que 
están siendo registrados en una pagina web configurada previamente.   

## Instalación

Modificación del ejemplo de boceto de prueba para varios sensores de temperatura/humedad DHT
escrito por ladyada, public domain.

REQUIERE las siguientes bibliotecas de Arduino:
- DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
- Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

REQUIERE Instalar Plugin del ESP8266 para Arduino.
- ir a archivo>Preferencias y en la casilla  “Gestor de URLs Adicionales de Tarjetas”
- agregamos: http://arduino.esp8266.com/stable/package_esp8266com_index.json

REQUIERE Instalar controladores del puerto COM virtual (VCP) del puente USB a UART CP210x
necesarios para el funcionamiento del dispositivo como un puerto COM virtual
se puede bajar de: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
o con el enlace directo: https://github.com/nodemcu/nodemcu-devkit/raw/master/Drivers/CH341SER_WINDOWS.zip


## Uso 

Cargar desde ArduinoIDE a la placa esp8266 y abrir desde cualquier navegador con internet el sitio web: https://esp328266.elementfx.com/
## Licencia

Creative Commons Legal Code CC0 1.0 Universal, Consulte la licencia para más detalles: https://creativecommons.org/publicdomain/zero/1.0/

## Contacto

correo: alex.varela@ucr.ac.cr tel: +50685525005

[![iconopeque.jpg](https://i.postimg.cc/hvtdRL0p/iconopeque.jpg)](https://postimg.cc/k6L4xtzb)

## Información
- alexvareq@gmail.com
- Soles1XX2.