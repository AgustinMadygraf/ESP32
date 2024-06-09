#include <Arduino.h> // Include the necessary header file

#define LED_PIN 4

void setup() {
    pinMode(LED_PIN, OUTPUT); // Configura el pin como salida
    Serial.begin(115200);
}

void loop() {
    digitalWrite(LED_PIN, HIGH); // Enciende el LED
    delay(1000); // Espera un segundo
    digitalWrite(LED_PIN, LOW); // Apaga el LED
    delay(1000); // Espera un segundo
    Serial.println("Hola mundo");
}

