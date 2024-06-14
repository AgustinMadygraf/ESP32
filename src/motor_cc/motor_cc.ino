const int potPin = A0;  // Pin del potenciómetro conectado a A0
const int pwmPin = 2;   // Pin de salida PWM conectado al pin 9

// Número de lecturas a promediar para suavizar el valor
const int numReadings = 10;
int readings[numReadings];  // Matriz para almacenar las lecturas
int readIndex = 0;          // Índice de la lectura actual
int total = 0;              // Suma total de las lecturas
int average = 0;            // Promedio de las lecturas

void setup() {
  // Configura el pin pwmPin como salida
  pinMode(pwmPin, OUTPUT);

  // Configura el pin potPin como entrada
  pinMode(potPin, INPUT);

  // Inicializa todas las lecturas a 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Restar la lectura anterior del total
  total = total - readings[readIndex];

  // Leer el nuevo valor del potenciómetro
  readings[readIndex] = analogRead(potPin);

  // Añadir la nueva lectura al total
  total = total + readings[readIndex];

  // Avanzar al siguiente índice de la matriz
  readIndex = readIndex + 1;

  // Si llegamos al final de la matriz, volver al principio
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calcular el promedio de las lecturas
  average = total / numReadings;

  // Ajustar la curva de respuesta con una función exponencial
  float normalizedValue = average / 1023.0;
  float adjustedValue = pow(normalizedValue, 2.0);  // Ajuste exponencial

  // Mapea el valor ajustado a un rango de 0 a 255
  int pwmValue = adjustedValue * 255;

  // Escribe el valor PWM al pin de salida
  analogWrite(pwmPin, pwmValue);

  // Pequeño retraso para estabilizar la lectura
  delay(10);
}