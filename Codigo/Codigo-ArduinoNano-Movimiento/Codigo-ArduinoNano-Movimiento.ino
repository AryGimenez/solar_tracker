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

const int PIN_ServoHorizontal = 11;       // Pin para el servo horizontal
const int PIN_ServoVertical = 10;         // Pin para el servo vertical


Servo m_servoHorizontal;
Servo m_servoVertical;

int m_ServoHorizontalPociicon = 0;
int m_ServoVerticalPociicon = 0;



// Variables Globales
bool modoManualActivo = true;             // Indica si el modo manual está activo

// Variables para guardar mediciones de amperaje y voltaje
float currentAmperage = 0.0;
float currentVoltage = 0.0;


void controlarServosConLDR() {
  // Aquí el código para mover los servos con los sensores LDR
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
  m_servoHorizontal.attach(PIN_ServoHorizontal);             // Adjunta el servo horizontal al pin 11
  m_servoVertical.attach(PIN_BTNModoAutomatico);               // Adjunta el servo vertical al pin 10
 
  // Estableser Posición inicial de los servos
  // m_servoHorizontal.write(180);             // Posición inicial del servo horizontal
  // m_servoVertical.write(180);               // Posición inicial del servo vertical
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




    int valorX = analogRead(PIN_JoystickX); // Lee el valor del eje X del joystick
    int valorY = analogRead(PIN_JoystickY); // Lee el valor del eje Y del joystick

      // Umbrales para el movimiento del joystick
    int umbralInferior = 400; // Valor debajo del cual se mueve el servo hacia un extremo
    int umbralSuperior = 600; // Valor por encima del cual se mueve el servo hacia el otro extremo



    // Definir topes de movimiento para los servos !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Movimiento Horizontal
    if (valorX < umbralInferior) {
        m_ServoHorizontalPociicon--; // Mueve hacia la izquierda
    } else if (valorX > umbralSuperior) {
        m_ServoHorizontalPociicon++; // Mueve hacia la derecha
    }





    // Movimiento Vertical
    if (valorY < umbralInferior) {
        m_ServoVerticalPociicon--; // Mueve hacia abajo
    } else if (valorY > umbralSuperior) {
        m_ServoVerticalPociicon++; // Mueve hacia arriba
    }


    // Prefiero Corroborarlo ante Eliminar

    // // Restringe los valores de los servos a su rango permitido
    // m_ServoHorizontalPociicon = constrain(m_ServoHorizontalPociicon, 0, 180);
    // m_ServoVerticalPociicon = constrain(m_ServoVerticalPociicon, 0, 180);

    // Mueve los servos a las nuevas posiciones
    m_servoHorizontal.write(m_ServoHorizontalPociicon);
    m_servoVertical.write(m_ServoVerticalPociicon);

}

void moverServo(){
  m_servoHorizontal.write(m_ServoHorizontalPociicon);
  m_servoVertical.write(m_ServoVerticalPociicon);
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



// Pued
