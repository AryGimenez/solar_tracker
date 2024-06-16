#include <Servo.h>

Servo miServo;

// ⬆️⬇️ 10 Pin Vertical 
// ⬅️➡️ 11 Pin Hotizontal
// PIN Servo
int PIN_Servo = 10;



int angulo = 0;  // Variable para almacenar la "angulo"



// Ajustar estos valores basados en las pruebas con el servo
int pwmMin = 300;  // Valor PWM mínimo (ajustar según el servo) Defecto 600 
int pwmMax = 2400; // Valor PWM máximo (ajustar según el servo)

int angMin = 0;   // Angulo minimo 
int angMax = 180; // Angulo Max 



void setup() {
  Serial.begin(9600);  // Inicia la comunicación serial
  miServo.attach(PIN_Servo);  // Adjunta el servo Pin
  Serial.println("Ingrese la angulo (0 a 180) y presione enviar:");
}

void loop() {
  // moverServoAutomatico();
  moverServoManual();
}

void moverServoAutomatico(){

  int xVelocidad = 1000;
  int xIncrementador = 5;

  // Mueve el servo del grado  0 a 180
  for (int i = 0; i <= 180; i += xIncrementador){
    movServo(i);
    delay(xVelocidad);
  }

  // Mueve el servo del grado 180 a 0
  for (int i = 180; i >= 0; i -= xIncrementador){
    movServo(i);
    delay(xVelocidad);
  }

}

void moverServoManual (){
    if (Serial.available() > 0) {  // Chequea si hay datos disponibles para leer en la terminal serial
    
    int anguloTEM = Serial.parseInt();  // Lee la "angulo" enviada

    movServo(anguloTEM);

    // Limpia el buffer serial para la próxima lectura
    while (Serial.available() > 0) {
      Serial.read();
    }

    Serial.println("Ingrese la próxima angulo:");
  }
}

void movServo (int pAngulo){
  // Corrobora que el angulo este en el rango deseado
  if (pAngulo >= angMin && pAngulo <= angMax){
    angulo = pAngulo;
    // Convierte el "angulo" a un valor de microsegundos
    int valorPWM = map(angulo, angMin, angMax, pwmMin, pwmMax);
    miServo.writeMicroseconds(valorPWM);
    Serial.print("El ángulo ingresado es: ");
    Serial.println(pAngulo);
  } else {
    Serial.println("El ángulo está fuera de rango, ingresa un ángulo entre los 0 y 180");
  }
}