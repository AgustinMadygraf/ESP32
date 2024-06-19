#include <Arduino.h> // Include the necessary header file

const int LED_PIN = 4; // Define the LED pin
const int BUTTON_PIN = 0; // Define the button pin
const int BUTTON1_PIN = 2;
const int BUTTON2_PIN = 4;
const int SENSOR1_PIN = 13;
const int SENSOR2_PIN = 14;
const unsigned long MESSAGE_INTERVAL = 1000; // Intervalo en milisegundos para mostrar el mensaje


void setup() {
    // Inicializa el monitor serie a 115200 baudios
    Serial.begin(115200);
    
    // Configura el pin LED como salida
    pinMode(LED_PIN, OUTPUT); 
    pinMode(BUTTON_PIN, INPUT); // Configura el pin del botón como entrada
    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(SENSOR1_PIN, INPUT);
    pinMode(SENSOR2_PIN, INPUT);    
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
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Botón presionado");
    } else {
        digitalWrite(LED_PIN, LOW);
    }

    // Leer el estado de los pulsadores

    int button1State = digitalRead(BUTTON1_PIN);
    int button2State = digitalRead(BUTTON2_PIN);

    // Leer el estado de los sensores inductivos
    int sensor1State = digitalRead(SENSOR1_PIN);
    int sensor2State = digitalRead(SENSOR2_PIN);
}