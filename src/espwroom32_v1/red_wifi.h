//red_wifi.ino
#include <WiFi.h>

// Configura el SSID y la contraseña de tu red WiFi
const char* ssid = "Aula tecnica";
const char* password = "Madygraf32";

WebServer server(80); // Puerto 80 para el servidor web

void setup_web_server() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

  // Imprime la dirección IP obtenida
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}