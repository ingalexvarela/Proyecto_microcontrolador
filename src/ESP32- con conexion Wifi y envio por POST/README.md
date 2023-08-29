# Estación Meteorológica con IoT para el Laboratorio de Telecomunicaciones

Este proyecto es la adaptación de un trabajo realizado con la ESP8266, para el uso en la placa ESP32


- [Sitio web del proyecto](https://esp32omega.000webhostapp.com/)
## Tabla de contenidos

- [Instalación](#instalación)
- [Uso](#Uso)
- [Licencia](#licencia)
- [Contacto](#contacto)

## Instalación

REQUIERE las siguientes bibliotecas de Arduino:
- DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
- Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

REQUIERE Instalar Plugin del ESP32 para Arduino.
- ir a archivo>Preferencias y en la casilla  “Gestor de URLs Adicionales de Tarjetas”
- agregamos: https://dl.espressif.com/dl/package_esp32_index.json  https://resource.heltec.cn/download/package_heltec_esp32_index.json

REQUIERE Instalar controladores del puerto COM virtual (VCP) del puente USB a UART CP210x
necesarios para el funcionamiento del dispositivo como un puerto COM virtual
se puede bajar de: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
o con el enlace directo: https://github.com/nodemcu/nodemcu-devkit/raw/master/Drivers/CH341SER_WINDOWS.zip

## Uso 

Cargar desde ArduinoIDE a la placa ESP32, y abrir desde cualquier navegador con internet el sitio web: https://esp32omega.000webhostapp.com/

## Licencia

Creative Commons Legal Code CC0 1.0 Universal, Consulte la licencia para más detalles: https://creativecommons.org/publicdomain/zero/1.0/

## Contacto

correo: alex.varela@ucr.ac.cr tel: +50685525005

[![iconopeque.jpg](https://i.postimg.cc/hvtdRL0p/iconopeque.jpg)](https://postimg.cc/k6L4xtzb)