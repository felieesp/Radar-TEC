#include <Servo.h>

Servo miServo;
const int pinServo = 11;
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  miServo.attach(pinServo);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // 300ms = 0.3 segundos para el barrido completo
  moverServo(0, 180, 300); 
  moverServo(180, 0, 300);
}

void moverServo(int inicio, int fin, int tiempoMs) {
  int pasos = abs(fin - inicio);
  int delayPorPaso = tiempoMs / pasos;
  int direccion = (fin > inicio) ? 1 : -1;
  int pos = inicio;
  
  for (int i = 0; i < pasos; i++) {
    pos += direccion;
    miServo.write(pos);
    
    // Disparo del sensor
    digitalWrite(trigPin, LOW); delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duracion = pulseIn(echoPin, HIGH, 10000);
    int dist = duracion * 0.034 / 2;
    
    // Envío de datos
    Serial.print(pos);
    Serial.print(",");
    Serial.println(dist);
    
    delay(delayPorPaso);
  }
}