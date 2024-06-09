#include <Arduino.h> // Include the necessary header file

#define LED_PIN 4 // Define the LED pin

void setup() {
    // Inicializa el monitor serie a 115200 baudios
    Serial.begin(115200);
    
    // Espera 2 segundos para dar tiempo a que la conexión serie se establezca
    delay(2000);

    // Configura el pin LED como salida
    pinMode(LED_PIN, OUTPUT); 

    // Mensaje de inicialización
    Serial.println("Inicializando...");
}

void loop() {
    // Enciende el LED
    digitalWrite(LED_PIN, HIGH); 
    // Mensaje indicando que el LED está encendido
    Serial.println("LED encendido");
    // Espera un segundo
    delay(1000); 

    // Apaga el LED
    digitalWrite(LED_PIN, LOW); 
    // Mensaje indicando que el LED está apagado
    Serial.println("LED apagado");
    // Espera un segundo
    delay(1000); 
}
