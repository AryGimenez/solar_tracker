#include <Servo.h>

Servo miServo;
int velocidad = 0;  // Variable para almacenar la "velocidad"

void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial
  miServo.attach(10);  // Adjunta el servo al pin D11
  Serial.println("Ingrese la velocidad (-90 a 90) y presione enviar:");
}

void loop() {
  if (Serial.available() > 0) {  // Chequea si hay datos disponibles para leer en la terminal serial
    velocidad = Serial.parseInt();  // Lee la "velocidad" enviada

    // Convierte la "velocidad" a un valor de microsegundos
    int valorPWM = map(velocidad, -90, 90, 1000, 2000);
    miServo.writeMicroseconds(valorPWM);

    Serial.println("Ingrese la próxima velocidad:");
    Serial.flush();  // Limpia el buffer serial para la próxima lectura
  }
}