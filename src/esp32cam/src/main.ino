#include <Arduino.h>
#include "camera_setup.h" // Incluye el archivo de configuración de la cámara

const int LED_PIN = 33; // Define the LED pin
const int BUTTON_PIN = 0; // Define the button pin
const unsigned long MESSAGE_INTERVAL = 1000; // Intervalo en milisegundos para mostrar el mensaje

void setup() {
    // Inicializa el monitor serie a 115200 baudios
    Serial.begin(115200);

    // Configura el pin LED como salida
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT); // Configura el pin del botón como entrada

    // Inicializa la cámara
    if (!setupCamera()) {
        Serial.println("Fallo al inicializar la cámara");
        while (true) {} // Detiene el programa si la cámara no se inicializa correctamente
    }

    unsigned long previousMillis = 0; // Variable para almacenar el tiempo anterior

    // Espera a que se presione el botón para continuar
    while (digitalRead(BUTTON_PIN) == HIGH) {
        unsigned long currentMillis = millis();

        // Enviar el mensaje cada MESSAGE_INTERVAL milisegundos
        if (currentMillis - previousMillis >= MESSAGE_INTERVAL) {
            previousMillis = currentMillis;
            Serial.println("Presiona el botón IO0 para continuar...");
        }
    }

    // Mensaje de inicialización
    Serial.println("Inicializando...");
}

void loop() {
    // Enciende el LED si el pin 0 está en estado bajo
    if (digitalRead(BUTTON_PIN) == LOW) {
        Serial.println("Botón presionado");
        digitalWrite(LED_PIN, HIGH);

        // Tomar una foto
        camera_fb_t * fb = esp_camera_fb_get();
        if (!fb) {
            Serial.println("Fallo al capturar la foto");
            return;
        }

        // Guardar la imagen en el sistema de archivos o enviarla por red
        // Aquí puedes agregar el código para guardar o procesar la imagen
        esp_camera_fb_return(fb);

        delay(1000); // Espera un segundo antes de permitir otra captura
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}
