#include <Arduino.h> // Include the necessary header file

const int LED_PIN = 4; // Define the LED pin
const int BUTTON_PIN = 0; // Define the button pin
const unsigned long MESSAGE_INTERVAL = 1000; // Intervalo en milisegundos para mostrar el mensaje


void setup() {
    // Inicializa el monitor serie a 115200 baudios
    Serial.begin(115200);
    
    // Configura el pin LED como salida
    pinMode(LED_PIN, OUTPUT); 
    pinMode(BUTTON_PIN, INPUT); // Configura el pin del botón como entrada
    
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
        //tomar una foto
        
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}
