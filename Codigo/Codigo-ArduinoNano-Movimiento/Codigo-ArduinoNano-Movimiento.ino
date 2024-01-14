#include <Servo.h>

// Declaraciones de constantes para los pines
const int PIN_BTNModoManual = 2;          // Botón para el modo manual
const int PIN_LEDModoManual = 7;          // LED para el modo manual
const int PIN_BTNModoAutomatico = 4;      // Botón para el modo automático
const int PIN_LEDModoAutomatico = 8;      // LED para el modo automático

// Pines del joystick KY 023 🕹️
const int PIN_JoystickX = A4;             // Pin para el eje X del joystick
const int PIN_JoystickY = A5;             // Pin para el eje Y del joystick// Pines para los sensores LDR


// Definición de los pines de las fotorresistencias 🌞
const int PIN_LDR_Arriba = A0;            // ⬆️ - Pin para el LDR de "Arriba"
const int PIN_LDR_Izquierda = A3;         // ➡️ - Pin para el LDR de "Izquierda" 
const int PIN_LDR_Abajo = A2;             // ⬇️ - Pin para el LDR de "Abajo"
const int PIN_LDR_Derecha = A1;           // ⬅️ - Pin para el LDR de "Derecha"

// Pines para los sensores de amperaje y voltaje
const int PIN_SensorAmperaje = A6;        // Pin para el sensor de amperaje
const int PIN_SensorVoltaje = A7;         // Pin para el sensor de voltaje

// Declaraciones para los servos
Servo m_servoHorizontal;
Servo m_servoVertical;

int m_ServoHorizontalPociicon 0;
int m_ServoVerticalPociicon 0;

// Variables Globales
bool modoManualActivo = true;             // Indica si el modo manual está activo

// Variables para guardar mediciones de amperaje y voltaje
float currentAmperage = 0.0;
float currentVoltage = 0.0;

// Configuración inicial
void setup() {
  Serial.begin(9600);
  inicializarPines();
  inicializarServos();
}

// Loop principal
void loop() {
  actualizarModo();
  if (modoManualActivo) {
    controlarServosConJoystick();
  } else {
    controlarServosConLDR();
  }
  leerSensores();
  mostrarDatos();
}

// Funciones de configuración y utilidad
void inicializarPines() {
  pinMode(PIN_BTNModoManual, INPUT);
  pinMode(PIN_LEDModoManual, OUTPUT);
  pinMode(PIN_BTNModoAutomatico, INPUT);
  pinMode(PIN_LEDModoAutomatico, OUTPUT);
  digitalWrite(PIN_LEDModoManual, HIGH);  // Enciende el LED del modo manual por defecto
}

void inicializarServos() {
  servoHorizontal.attach(11);             // Adjunta el servo horizontal al pin 11
  servoVertical.attach(10);               // Adjunta el servo vertical al pin 10
  servoHorizontal.write(180);             // Posición inicial del servo horizontal
  servoVertical.write(180);               // Posición inicial del servo vertical
}
// revisar 
void actualizarModo() {
  if (digitalRead(PIN_BTNModoManual) == HIGH) {
    modoManualActivo = true;
    digitalWrite(PIN_LEDModoManual, HIGH); //  ensiende led modo modo manual
    digitalWrite(PIN_LEDModoAutomatico, LOW);
  } else if (digitalRead(PIN_BTNModoAutomatico) == HIGH) {
    modoManualActivo = false;
    digitalWrite(PIN_LEDModoAutomatico, HIGH);
    digitalWrite(PIN_LEDModoManual, LOW);
  }
}

void controlarServosConJoystick() {
  // Aquí el código para mover los servos con el joystick
 

}

void moverServo(bool p_Horizontal, int p_Grado){
 
 if (p_Horizontal){
  m_servoHorizontal.write(p_Grado);
 }else{
  m_servoVertical.write(p_Grado);
 }
  

void loop() {
  if (Serial.available() > 0) {  // Chequea si hay datos disponibles para leer en la terminal serial
    angulo = Serial.parseInt();  // Lee el ángulo enviado

    // Ignora lecturas no válidas (como 0 que puede ser un carácter residual)
    if (angulo > 0 && angulo <= 180) {
      Serial.println("El angulo que ingresé fue: " + String(angulo));
      miServo.write(angulo);  // Mueve el servo al ángulo deseado
    }

    delay(1000);  // Espera un poco antes de leer el siguiente ángulo
    while (Serial.available() > 0) {
      char t = Serial.read(); // Limpia cualquier caracter residual en el buffer
    }
    Serial.println("Mueva a otro ángulo:");
  }
}
}

void controlarServosConLDR() {
  // Aquí el código para mover los servos con los sensores LDR
}

void leerSensores() {
  leerAmperaje();
  leerVoltaje();
}

void leerAmperaje() {
  int sensorValue = analogRead(PIN_SensorAmperaje);
  float voltage = (sensorValue * 5.0) / 1023.0;
  currentAmperage = (voltage - 2.5) / 0.185;
}

void leerVoltaje() {
  int sensorValue = analogRead(PIN_SensorVoltaje);
  currentVoltage = sensorValue * (5.0 / 1023.0) * 5 * 0.927;
}

void mostrarDatos() {
  Serial.print("Amperaje: ");
  Serial.print(currentAmperage);
  Serial.print(" A, Voltaje: ");
  Serial.print(currentVoltage);
  Serial.println(" V");
}

// Pued
