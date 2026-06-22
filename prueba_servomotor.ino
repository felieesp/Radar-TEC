#include <Servo.h>

Servo miServo360;

void setup() {
  // Conecta el cable de señal (generalmente naranja o blanco) al pin 11
  miServo360.attach(11); 
}

void loop() {
  // 1. Girar hacia un lado a máxima velocidad por 3 segundos
  miServo360.write(0);
  delay(3000);

  // 2. Detener el motor por 2 segundos
  miServo360.write(90);
  delay(2000);

  // 3. Girar hacia el lado contrario a máxima velocidad por 3 segundos
  miServo360.write(180);
  delay(3000);

  // 4. Detener de nuevo por 2 segundos antes de reiniciar el ciclo
  miServo360.write(90);
  delay(2000);
}