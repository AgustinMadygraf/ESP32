# ESP32 Motor Control Web Interface

Este proyecto proporciona una interfaz web simple para controlar un motor utilizando un ESP32. La aplicación incluye una página HTML con botones para controlar el motor, estilos CSS para la presentación y un script PHP para manejar la subida de imágenes desde el ESP32.

## Estructura del Proyecto

```
ESP32/
    DOCS/
    esp32cam/
    esp32wroom/
    public/
        index.html
        upload.php
        assets/
            main.css
            scripts.js
        uploads/
```

- `public/index.html`: Página principal con la interfaz de control del motor.
- `public/upload.php`: Script PHP para manejar la subida de imágenes.
- `public/assets/main.css`: Archivo CSS principal para los estilos.
- `public/assets/scripts.js`: Archivo JavaScript para la lógica de los botones (debes crear este archivo si no existe).
- `public/uploads/`: Carpeta para almacenar las imágenes subidas.
- `DOCS/`, `esp32cam/`, `esp32wroom/`: Carpetas adicionales para documentación y otros proyectos relacionados con ESP32.

## Configuración

1. Clona el repositorio en tu servidor local.
2. Asegúrate de tener instalado un servidor web (como Apache) con soporte para PHP.
3. Coloca la carpeta `ESP32/public` en la raíz de tu servidor web.

## Uso

### Página de Control del Motor

1. Abre `index.html` en tu navegador web visitando `http://localhost/ESP32/public/index.html`.
2. Usa los botones "Forward" y "Reverse" para controlar el motor.

### Subida de Imágenes

El script `upload.php` se utiliza para subir imágenes desde el ESP32. Sigue estos pasos para realizar la subida:

1. Configura tu ESP32 para capturar imágenes y enviarlas a `http://localhost/ESP32/public/upload.php`.
2. Asegúrate de que las imágenes se guarden en la carpeta `uploads` con un nombre único basado en la fecha y hora.

## Ejemplo de Código para el ESP32

Aquí tienes un ejemplo de cómo configurar el ESP32 para enviar una imagen al servidor:

```cpp
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP32HTTPClient.h>

// Configura tu red WiFi y la URL del servidor
const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
const char* serverName = "http://localhost/ESP32/public/upload.php";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Captura la imagen y súbela al servidor
    captureAndUploadImage();
}

void captureAndUploadImage() {
    // Captura de imagen no mostrada aquí
    // Supón que la imagen se guarda en un archivo llamado "image.jpg"
    
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverName);
        http.addHeader("Content-Type", "multipart/form-data");

        File imageFile = SPIFFS.open("/image.jpg", "r");
        if (!imageFile) {
            Serial.println("Failed to open image file");
            return;
        }

        int httpResponseCode = http.POST(imageFile);
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        http.end();
        imageFile.close();
    } else {
        Serial.println("WiFi not connected");
    }
}

void loop() {
    // No es necesario hacer nada aquí
}
```

## Contribuciones

Si deseas contribuir a este proyecto, por favor crea un fork del repositorio y envía un pull request con tus cambios.

## Licencia

Este proyecto está licenciado bajo la MIT License. Para más detalles, consulta el archivo `LICENSE`.
