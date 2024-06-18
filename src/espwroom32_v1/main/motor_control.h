// motor.h
#ifndef MOTOR_H
#define MOTOR_H

void setup_motor(int pinOutput_ENA, int pinOutput_DIR, int pinOutput_PUL) {
  // Configura los pines de salida
  pinMode(pinOutput_ENA, OUTPUT);
  pinMode(pinOutput_DIR, OUTPUT);
  pinMode(pinOutput_PUL, OUTPUT);

  // Configura los pines en estado inicial
  digitalWrite(pinOutput_ENA, HIGH); // El motor está apagado inicialmente
  digitalWrite(pinOutput_DIR, LOW); // El sentido de giro es hacia adelante inicialmente
  digitalWrite(pinOutput_PUL, LOW); // El pulso está en estado bajo inicialmente
}

void runMotor(int pinOutput_ENA, int pinOutput_DIR, int pinOutput_PUL, int direction) {
  digitalWrite(pinOutput_ENA, LOW); // ENA se enciende con LOW
  digitalWrite(pinOutput_DIR, direction); // Direccion del motor
  for (int i = 0; i < 200; i++) {
    digitalWrite(pinOutput_PUL, HIGH);
    delayMicroseconds(1000);
    digitalWrite(pinOutput_PUL, LOW);
    delayMicroseconds(1000);
  }
}

#endif
