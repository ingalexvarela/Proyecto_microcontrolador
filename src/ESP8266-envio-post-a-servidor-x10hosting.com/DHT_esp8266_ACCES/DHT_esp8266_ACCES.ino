// Librerías conexión WiFi - cliente ESP8266
#include <ESP8266HTTPClient.h> // Incluye la librería HTTPClient para realizar solicitudes HTTP.
#include <ESP8266WiFiMulti.h>  // Incluye la librería WiFiMulti para gestionar conexiones WiFi.
#include <WiFiClient.h>        // Incluye la librería WiFiClient para crear clientes WiFi.

// Defino credenciales de la red WiFi
const char *ssid = "Rincon Violeta 3F";     // Define el nombre de la red WiFi a la que se conectará el dispositivo.
const char *password = "rinconvioleta2392"; // Define la contraseña de la red WiFi.

// Variables para lectura del DHT 11
float t; // Variable para almacenar la temperatura.
float h; // Variable para almacenar la humedad.

// Librerías sensor DHT
#include "DHT.h" // Incluye la librería DHT para gestionar el sensor de temperatura y humedad.

#define DHTPIN 14     // Define el pin digital en el que está conectado el sensor.
#define DHTTYPE DHT11 // Define el modelo de sensor que se está utilizando.

DHT dht(DHTPIN, DHTTYPE); // Crea un objeto de la clase DHT que se utilizará para leer los datos del sensor.
WiFiClient client;        // Crea un objeto de la clase WiFiClient que se utilizará para conectar con la red WiFi.

void setup()
{
  Serial.begin(115200); // Inicia la comunicación serial a 115200 baudios.
  dht.begin();          // Inicializa el objeto DHT.

  // Configura la conexión WiFi
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
    Serial.println(F("Error en la lectura del DHT sensor!")); // Mensaje en el monitor serial indicando que ha habido un error
    return;
  }
}

// Función de rutina de envío de datos por POST
void EnvioDatos()
{
  if (WiFi.status() == WL_CONNECTED) // Verifica si el ESP8266 está conectado a una red WiFi
  {
    HTTPClient http; // Crea un objeto de la clase HTTPClient

    // Crea un string con los datos a enviar en formato de formulario
    String datos_a_enviar = "temperatura=" + String(t) + "&humedad=" + String(h);

    // Asegúrate de que la URL sea http o https según lo requerido (verifica manualmente)
    http.begin(client, "http://esp328266.elementfx.com/EspPost.php"); // Cambiado a http

    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Especifica el tipo de contenido

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
      else if (codigo_respuesta == 301 || codigo_respuesta == 302)
      {
        Serial.println("Redireccionado. Verifica la URL o usa https.");
      }
    }
    // Si el código de respuesta es menor o igual a 0, se imprime un mensaje de error
    else
    {
      Serial.print("Error enviado POST, código: ");
      Serial.println(codigo_respuesta);
      Serial.println(http.errorToString(codigo_respuesta)); // Mostrar el error en texto
    }

    // Termina la comunicación HTTP y libera los recursos utilizados
    http.end();
  }
  else
  {
    // Si no está conectado a una red WiFi, se imprime un mensaje de error
    Serial.println("Error en la conexión WIFI");
  }

  // Espera 60 segundos antes de volver a enviar datos
  delay(60000);
}
