//espwroom32_v1.ino
#include <WiFi.h>
#include <WebServer.h>
#include "HX711.h"
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "red_wifi.h"
#include "balanza.h"
#include "motor.h"

// Configura los pines de salida
const int pinOutput_ENA = 18; // enciende el motor con LOW
const int pinOutput_DIR = 19; // sentido de giro
const int pinOutput_PUL = 13; // pulso,  debe tener 1000 microsegundos entre semiciclo positivo y negativo

LiquidCrystal_I2C lcd(0x27, 16, 2);

HX711 balanza;

const int zero = 2;
int DT = 4;
int CLK = 5;

int peso_calibracion = 185; // Es el peso referencial a poner, en mi caso mi celular pesa 185g (SAMSUMG A20)
long escala;

int state_zero = 0;
int last_state_zero = 0;

void handleRoot() {
  float peso_mostrar;
  peso_mostrar = balanza.get_units(10);
  server.send(200, "text/plain", "ESP32 Web Server \n Peso: " + String(peso_mostrar) + " g");
}

void handleOutputENA_f() {
  lcd.setCursor(0, 0);
  lcd.print("Motor en avance ");
  server.send(200, "text/plain", "Motor en Marcha");
  motor_marcha(pinOutput_ENA, pinOutput_DIR, pinOutput_PUL, LOW); 
}

void handleOutputENA_r() {
  lcd.setCursor(0, 0);
  lcd.print("Motor en retroceso");
  server.send(200, "text/plain", "Motor en Reversa");
  motor_marcha(pinOutput_ENA, pinOutput_DIR, pinOutput_PUL, HIGH); 
}

void setup() {
  Serial.begin(115200);

  setup_web_server(); // Configurar y conectar al WiFi con IP estática
  setup_motor(pinOutput_ENA, pinOutput_DIR, pinOutput_PUL);
  server.on("/", handleRoot);
  server.on("/ena_f", handleOutputENA_f);
  server.on("/ena_r", handleOutputENA_r);

  server.begin();
  Serial.println("HTTP server started"); //iniciando

  balanza.begin(DT, CLK);//asigana los pines para el recibir el trama del pulsos que viene del modulo
  pinMode(zero, INPUT);//declaramos el pin2 como entrada del pulsador
  pinMode(13,OUTPUT);
  lcd.init(); // Inicializamos el lcd
  lcd.backlight(); // encendemos la luz de fondo del lcd

  EEPROM.get(0, escala);//Lee el valor de la escala en la EEPROM

  if (digitalRead(zero) == 1) { 
      calibration(lcd, balanza, peso_calibracion, escala);
  }
  balanza.set_scale(escala); // Establecemos la escala
  balanza.tare(20);  //El peso actual de la base es considerado zero.

}

void loop() {
  server.handleClient();

  int state_zero = digitalRead(zero);
  float peso;
  peso = balanza.get_units(10);  //Mide el peso de la balanza

  //Muestra el peso
  lcd.setCursor(0, 1);
  lcd.print("Peso: ");
  lcd.print(peso, 0);
  lcd.print(" g        ");
  delay(500);

  lcd.setCursor(0, 0);
  lcd.print("Motor en espera ");

  //Botón de zero, esto sirve para restar el peso de un recipiente 
  if ( state_zero != last_state_zero) {
    if (state_zero == LOW) {
      balanza.tare(10);  //El peso actual es considerado zero.
    }
  }
  last_state_zero = state_zero;

  if (peso >= 500) digitalWrite(13, 1);
  else if (peso <= 500) digitalWrite(13, 0);
}