#include <Arduino.h>
#include "esp_camera.h"
#include "fb_gfx.h"
#include "img_converters.h"

// Pines para la cámara AI Thinker ESP32-CAM
#define PWDN_GPIO_NUM    32
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    21
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27
#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      19
#define Y4_GPIO_NUM      18
#define Y3_GPIO_NUM      5
#define Y2_GPIO_NUM      4
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

const int LED_PIN = 33; // Define the LED pin
const int BUTTON_PIN = 0; // Define the button pin
const unsigned long MESSAGE_INTERVAL = 1000; // Intervalo en milisegundos para mostrar el mensaje

void setup() {
    // Inicializa el monitor serie a 115200 baudios
    Serial.begin(115200);

    // Configura el pin LED como salida
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT); // Configura el pin del botón como entrada
    pinMode(PWDN_GPIO_NUM, OUTPUT);

    // Resetear la cámara
    Serial.println("Reiniciando cámara...");
    digitalWrite(PWDN_GPIO_NUM, HIGH);
    delay(100);
    digitalWrite(PWDN_GPIO_NUM, LOW);
    delay(100);

    // Configura la cámara
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // Init with high specs to pre-allocate larger buffers
    if(psramFound()){
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    } else {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    // Inicializa la cámara
    Serial.println("Inicializando cámara...");
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x\n", err);
        return;
    }

    Serial.println("Cámara inicializada correctamente");

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
