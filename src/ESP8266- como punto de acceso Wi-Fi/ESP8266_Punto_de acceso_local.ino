// Modificación del ejemplo de boceto de prueba para varios sensores de temperatura/humedad DHT
// escrito por ladyada, public domain.

// REQUIERE las siguientes bibliotecas de Arduino:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

// REQUIERE Instalar Plugin del ESP8266 para Arduino.
// - ir a archivo>Preferencias y en la casilla  “Gestor de URLs Adicionales de Tarjetas” 
// - agregamos: http://arduino.esp8266.com/stable/package_esp8266com_index.json

// REQUIERE Instalar controladores del puerto COM virtual (VCP) del puente USB a UART CP210x
/* necesarios para el funcionamiento del dispositivo como un puerto COM virtual
se puede bajar de: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads 
o con el enlace directo: https://github.com/nodemcu/nodemcu-devkit/raw/master/Drivers/CH341SER_WINDOWS.zip */

// librerias modulo Wifi Acces Point
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// librerias sensor
#include "DHT.h"

// Definir las credenciales de acceso
const char *ssid = "ESTACION-IoT";  // Nombre de la red
const char *password = "998877665"; // Contraseña

// Variables para lectura del DHT 22
float t; // Guarda temperatura grados
float h; // Guarda Humedad relativa

ESP8266WebServer server(80); // habilita el puerto 80 para servidor

// Declaraciones parametros para el sensor
#define DHTPIN 14     // Pin14 digital conectado al sensor DHT11
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE); // Objeto recibe 2 parametros pin datos, modelo de sensor

void setup()
{
  Serial.begin(115200); // Velocidad de comunicación puerto serial en baudios
  dht.begin();          // Iniciamos objeto

  // configuramo el modo acces Point función softAP
  WiFi.softAP(ssid, password);      // recibe nombre red y contraseña
  server.on("/", handleRoot);       // al realizar petición llama función handleRoot
  server.begin();                   // Iniciamos servidor
  IPAddress myIP = WiFi.softAPIP(); // crea la IP con la función WiFi.softAPIP
}

void loop()
{
  LecturaTyH();
  server.handleClient(); // monitorea presencia de cliente y envia respuesta de handleRoot
}

// FUNCIONES
void handleRoot() // creamos la funcion Estructura HTML envio lineas (datos) al cliente
{
  server.send(200, "text/html", "<html><head><meta name='viewport' content='width=device-width, user-scalable=no'>"
                                "<meta http-equiv='refresh' content='5' charset='UTF-8'><title>Estación Meteorológica con IoT</title>"
                                "<style>body {font-family: monospace; background-color: rgb(4, 2, 7);}"
                                "h1 {color: white; margin: 5px; text-align: center; margin: 50px; font-size: 18px;}"
                                ".barraTemp {height: 200px; width: 200px; background-color: yellow; margin: auto;"
                                "border-radius: 50%; overflow: hidden;}.cont {height: 100px; width: 200px;}"
                                ".CirculoCentro { height: 150px; width: 150px; background-color: rgb(4, 2, 7); "
                                "border-radius: 50%; margin: auto; position: relative; margin: -175px auto 50px;}"
                                ".Rectangulo {height: 100px; width: 200px; background-color: rgb(4, 2, 7);"
                                "position: relative; margin: -125px auto 50px;}</style></head><Body>"
                                "<h1>Mini Estación Meteorológica automática con IoT</h1>"
                                "<h1>Temperatura</h1>" 
                                "<div class='barraTemp' style='transform: rotate("+String(map(t, 0, 100, 0, 180))+"deg);'>" // Control de barra de progreso
                                "<div class='cont' style='background-color: rgb(143, 136, 136);'> </div>"
                                "<div class='cont' style='background-color: rgb(253, 114, 0, 0.986);'> </div>"
                                "</div><div class=' CirculoCentro '></div><div class=' Rectangulo '></div>"
                                "<h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"+String(t)+" °C</h1>"
                                "<h1>Humedad Relativa</h1>"
                                "<div class='barraTemp' style='transform: rotate("+String(map(h, 0, 100, 0, 180))+"deg);'>" // Control de barra de progreso
                                "<div class='cont' style='background-color: rgb(143, 136, 136);'> </div>"
                                "<div class='cont' style='background-color: rgb(23, 218, 224);'> </div>"
                                "</div><div class='CirculoCentro'></div><div class='Rectangulo'></div>"
                                "<h1 style='font-size: 22px; position: relative; margin: -125px auto 50px;'>"+String(h)+" %</h1>"
                                "</Body></html>");
}

// funcion de lectura de temperatura y humedad del sensor
void LecturaTyH()
{
  h = dht.readHumidity();
  t = dht.readTemperature();

  // Comprobar si alguna lectura falló y salir antes (para volver a intentarlo).
  if (isnan(h) || isnan(t))
  {
    Serial.print("\t\t\t");
    Serial.print(WiFi.softAPIP());
    Serial.println(F("¡Error al leer datos del sensor DHT22!")); // imprimir mensaje
    return;
  }
  // Imprimir por el puerto serial tempertaura y humedad
  Serial.print(F("% Humedad: "));
  Serial.print(h);
  Serial.print("\t");  // da espacio
  Serial.print(F("Temperatura: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print("\t");
  Serial.print(F("IP Local creada: "));   
  Serial.println(WiFi.softAPIP()); // Imprimir IP y da salto de linea para imprimir el siguiente ciclo de datos
  delay(10000); // espera 10s  
}
