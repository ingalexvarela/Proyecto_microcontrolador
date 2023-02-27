// Modificación del ejemplo de boceto de prueba para varios sensores de temperatura/humedad DHT
// escrito por ladyada, public domain.

// REQUIERE las siguientes bibliotecas de Arduino:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

// librerias sensor
#include "DHT.h"

// Variables para lectura del DHT 22
float t; // Guarda temperatura grados
float h; // Guarda Humedad relativa

// Declaraciones parametros para el sensor
#define DHTPIN 14     // PinD5 digital conectado al sensor DHT22
#define DHTTYPE DHT11 // DHT 11  

DHT dht(DHTPIN, DHTTYPE); // Objeto recibe 2 parametros pin datos, modelo de sensor

void setup()
{
  Serial.begin(115200); // Velocidad de comunicación puerto serial en baudios
  dht.begin();          // Iniciamos objeto
}

void loop()
{
  LecturaTyH();
}

// FUNCIONES

// funcion de lectura de temperatura y humedad del sensor
void LecturaTyH()
{
  h = dht.readHumidity();
  t = dht.readTemperature();

  // Comprobar si alguna lectura falló y salir antes (para volver a intentarlo).
  if (isnan(h) || isnan(t))
  {
    Serial.print("\t\t\t");
    Serial.println(F("¡Error al leer datos del sensor DHT22!")); // imprimir mensaje
    return;
  }
  // Imprimir por el puerto serial tempertaura y humedad
  Serial.print(F("% Humedad: "));
  Serial.print(h);
  Serial.print("\t"); // da espacio
  Serial.print(F("Temperatura: "));
  Serial.print(t);
  Serial.println(F("°C "));
  delay(10000); // espera 10s
}
