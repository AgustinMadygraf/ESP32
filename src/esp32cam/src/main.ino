//main.ino
#include "wifi_setup.h"
#include "camera_setup.h"


void setup() {
  connectToWiFi();
  initCamera();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= timerInterval) {
    Serial.printf("Memoria libre antes de capturar la imagen: %u bytes\n", esp_get_free_heap_size());
    sendPhoto();
    Serial.printf("Memoria libre después de capturar la imagen: %u bytes\n", esp_get_free_heap_size());
    previousMillis = currentMillis;
  }
}
