//red_wifi.ino
#include <WiFi.h>

// Configura el SSID y la contraseña de tu red WiFi
const char* ssid = "Aula tecnica";
const char* password = "Madygraf32";

// Configura la IP estática
IPAddress local_IP(192, 168, 1, 184); // La IP que quieres asignar
IPAddress gateway(192, 168, 1, 1);    // La IP del gateway, generalmente la IP del router
IPAddress subnet(255, 255, 255, 0);   // La máscara de subred
IPAddress primaryDNS(8, 8, 8, 8);     // DNS primario, puedes usar el de Google
IPAddress secondaryDNS(8, 8, 4, 4);   // DNS secundario, puedes usar el de Google

WebServer server(80); // Puerto 80 para el servidor web

void setup_web_server() {
  // Configura la IP estática con los DNS
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Falló la configuración de IP estática");
  }

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