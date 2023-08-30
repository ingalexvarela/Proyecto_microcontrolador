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

// Librerias conexion Wifi - cliente ESp8266
#include <HTTPClient.h> // Incluye la librería HTTPClient para realizar solicitudes HTTP.
#include <WiFiMulti.h>  // Incluye la librería WiFiMulti para gestionar conexiones WiFi.
#include <WiFiClient.h>        // Incluye la librería WiFiClient para crear clientes WiFi.

// defino credenciales de la red wifi
const char *ssid = "Rincon Violeta 2F";     // Define el nombre de la red WiFi a la que se conectará el dispositivo.
const char *password = "rinconvioleta2392"; // Define la contraseña de la red WiFi.

// Variables para lectura del DHT 11
float t; // Variable para almacenar la temperatura.
float h; // Variable para almacenar la humedad.

// librerias sensor
#include "DHT.h" // Incluye la librería DHT para gestionar el sensor de temperatura y humedad.

#define DHTPIN 14     // Define el pin digital en el que está conectado el sensor.
#define DHTTYPE DHT11 // Define el modelo de sensor que se está utilizando.

DHT dht(DHTPIN, DHTTYPE); // Crea un objeto de la clase DHT que se utilizará para leer los datos del sensor.
WiFiClient client;        // Crea un objeto de la clase WiFiClient que se utilizará para conectar con la red WiFi.

void setup()
{
  Serial.begin(115200); // Inicia la comunicación serial a 115200 baudios.
  dht.begin();          // Inicializa el objeto DHT.

  // Configura la conexión wifi
  WiFi.begin(ssid, password); // Intenta conectar a la red WiFi utilizando las credenciales definidas.
  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) // Espera a que se establezca la conexión.
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión OK!"); // Muestra un mensaje en el monitor serial indicando que la conexión se ha establecido correctamente.
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP()); // Muestra la dirección IP local asignada al dispositivo.
}

void loop()
{
  LecturaTH();  // Llama a la función LecturaTH para leer los datos del sensor.
  EnvioDatos(); // Llama a la función EnvioDatos para enviar los datos al servidor web.
}

// FUNCIONES

// Función de lectura de temperatura y humedad
void LecturaTH()
{
  h = dht.readHumidity();    // Lee la humedad del sensor y la almacena en la variable h.
  t = dht.readTemperature(); // Lee la temperatura del sensor y la almacena en la variable t.

  // Comprueba que las lecturas del sensor sean válidas.
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Error en la lectura del DHT sensor!")); // mensaje en el monitor serial indicando que ha habido un error
    return;
  }
}

// funcion de rutina de envio de datos por POST
void EnvioDatos()
{
  if (WiFi.status() == WL_CONNECTED) // Verifica si el ESP8266 está conectado a una red WiFi
  {
    HTTPClient http; // Crea un objeto de la clase HTTPClient

    // Crea un string con los datos a enviar en formato de formulario
    String datos_a_enviar = "temperatura=" + String(t) + "&humedad=" + String(h);

    // Inicia la comunicación HTTP con la URL indicada y especifica que se usará texto plano
    http.begin(client, "http://esp32omega.000webhostapp.com/EspPost.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Envía los datos al servidor web utilizando el método POST y almacena el código de respuesta HTTP
    int codigo_respuesta = http.POST(datos_a_enviar);

    // Si el código de respuesta es mayor a 0, se procesa la respuesta del servidor web
    if (codigo_respuesta > 0)
    {
      Serial.println("Código HTTP: " + String(codigo_respuesta));

      // Si el código de respuesta es 200, se obtiene el cuerpo de la respuesta HTTP
      if (codigo_respuesta == 200)
      {
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió: ");
        Serial.println(cuerpo_respuesta);
      }
    }
    // Si el código de respuesta es menor o igual a 0, se imprime un mensaje de error
    else
    {
      Serial.print("Error enviado POST, código: ");
      Serial.println(codigo_respuesta);
    }

    // Termina la comunicación HTTP y libera los recursos utilizados
    http.end();
  }
  else
  {
    // Si no está conectado a una red WiFi, se imprime un mensaje de error
    Serial.println("Error en la conexion WIFI");
  }

  // Espera 60 segundos antes de volver a enviar datos
  delay(60000);
}