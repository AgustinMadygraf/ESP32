#include <Arduino.h> // Include the necessary header file
#include <FS.h>
#include <SPIFFS.h>  

#define LED_PIN 4

void setup() {
    pinMode(LED_PIN, OUTPUT); // Configura el pin como salida
}

void loop() {
    digitalWrite(LED_PIN, HIGH); // Enciende el LED
    delay(100); // Espera un segundo
    digitalWrite(LED_PIN, LOW); // Apaga el LED
    delay(100); // Espera un segundo
}

