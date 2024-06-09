#include <Arduino.h> // Include the necessary header file

#define LED_PIN 4 // Define the LED pin
#define BUTTON_PIN 0 // Define the button pin

void setup() {
    // Inicializa el monitor serie a 115200 baudios
    Serial.begin(115200);
    
    // Espera 2 segundos para dar tiempo a que la conexión serie se establezca
    delay(2000);

    // Configura el pin LED como salida
    pinMode(LED_PIN, OUTPUT); 
    pinMode(BUTTON_PIN, INPUT); // Configura el pin del botón como entrada
    while (digitalRead(BUTTON_PIN) == HIGH) {
        delay(1000);
        Serial.println("Presiona el botón IO0 para continuar...");
    }

    // Mensaje de inicialización
    Serial.println("Inicializando...");
}

void loop() {
    // Enciende el LED si el pin 0 está en estado bajo
    if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
    
}
