#include <Servo.h>

// ---- Declaraciones de constantes para los pines ----


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

// --------------------------- --- --------------------------




// ---- Variables Para trabjar con servos ----


// Objetos para controlar los servos
Servo m_servoHorizontal;
Servo m_servoVertical;

// variables para guardar la ultima posicion de los servos
int m_ServoHorizontalPosicion = 0;
int m_ServoVerticalPosicion = 0;

// Definición de constantes para la calibración y los límites de movimiento del servo
const int MIN_ANGLE = 0;
const int MAX_ANGLE = 180;
const int ANGLE_STEP = 5;

// --------------------------- --- --------------------------

// ---- Variables para trabajar con el modo de uso ----

// Variable para guardar el modo de usos seleccionado
bool modoManualActivo = false;  // MOdo de uso LDR activado por defect\

// --------------------------- --- --------------------------


// --------- variables para trabajar con los sensores Amperaje Voltaje

// Variables para guardar mediciones de amperaje y voltaje
float currentAmperage = 0.0;
float currentVoltage = 0.0;

// --------------------------- --- --------------------------



// Función para mover el servomotor verticalmente
// Si 'direction' es positivo, mueve el servo hacia arriba; si es negativo, hacia abajo.
void moveVertical(int direction) {
  // Calcula la nueva posición vertical del servomotor,
  // asegurándose de que esté dentro de los límites permitidos.
  // 'm_ServoVerticalPosicion' es la posición actual del servomotor.
  // 'direction' indica la dirección y magnitud del cambio de posición.
  // 'ANGLE_STEP' es la cantidad de grados que el servo debe moverse por cada unidad de 'direction'.
  // 'MIN_ANGLE' y 'MAX_ANGLE' son los límites mínimos y máximos, respectivamente,
  // dentro de los cuales el servomotor puede moverse.
  int newVerticalPosition = constrain(m_ServoVerticalPosicion + direction * ANGLE_STEP, MIN_ANGLE, MAX_ANGLE);

  // Mueve el servomotor a la nueva posición calculada.
  m_servoVertical.write(newVerticalPosition);

  // Actualiza la posición actual del servomotor con la nueva posición.
  m_ServoVerticalPosicion = newVerticalPosition;

  // Imprime la nueva posición del servomotor vertical en el monitor serial para depuración y monitoreo.
  Serial.print("Servo Vertical: ");
  Serial.println(newVerticalPosition);
}


// Función para mover el servomotor horizontalmente
// Si es positgivbo lo mueve acia la derecha si es negativo ase lo controario Esto lo entendi bien chatgptr 
void moveHorcizontal(int direction) {
  
  // Calcula la nueva posición horizontal del servomotor,
  // asegurándose de que esté dentro de los límites permitidos.
  // 'm_ServoHorizontalPosicion' es la posición actual del servomotor.
  // 'direction' indica la dirección y magnitud del cambio de posición.
  // 'ANGLE_STEP' es la cantidad de grados que el servo debe moverse por cada unidad de 'direction'.
  // 'MIN_ANGLE' y 'MAX_ANGLE' son los límites mínimos y máximos, respectivamente, dentro de los cuales el servomotor puede moverse.
  int newHorizontalPosition = constrain(m_ServoHorizontalPosicion + direction * ANGLE_STEP, MIN_ANGLE, MAX_ANGLE);
   
  // Mueve el servomotor a la nueva posición calculada.
  m_servoHorizontal.write(newHorizontalPosition);
  
  // Actualiza la posición actual del servomotor con la nueva posición.
  m_ServoHorizontalPosicion = newHorizontalPosition;
  
  // Imprime la nueva posición del servomotor horizontal en el monitor serial para depuración y monitoreo.
  Serial.print("Servo Horizontal: ");
  Serial.println(newHorizontalPosition);
}




// // ------------------- Codigo Obsoleto -------------------


// // Mueve el servo Vertical
// void moveVertical(int direction) {
//   // Calcula la nueva posición vertical del servomotor, asegurándose de que esté dentro de los límites permitidos
//   int newVerticalPosition = constrain(m_ServoVerticalPosicion + direction * ANGLE_STEP, MIN_ANGLE, MAX_ANGLE);
//   m_servoVertical.write(newVerticalPosition);
//   m_ServoVerticalPosicion = newVerticalPosition;
//   Serial.print("Servo Vertical: ");
//   Serial.println(newVerticalPosition);
// }

// // ------------------- --- -------------------


// ------------------- Codigo Obsoleto -------------------

// // Función para mover el servomotor horizontalmente
// void moveHorizontal(int direction) {
  
//   // Calcula la nueva posición horisontal del servomotor, 
//   // asegurándose de que esté dentro de los límites permitidos
  
//   int newHorizontalPosition = constrain
//   (m_ServoHorizontalPosicion + direction * 
//   ANGLE_STEP, MIN_ANGLE, MAX_ANGLE);
   
//   m_servoHorizontal.write(newHorizontalPosition);
//   m_ServoHorizontalPosicion = newHorizontalPosition;
  
   
//   Serial.print("Servo Horizontal: ");
//   Serial.println(newHorizontalPosition);
// }
// ------------------- --- -------------------






// Metodo utilizado para verificar los sentidos Del Sensor LDR 
void verificarSensoresLDR() {
  // Leer los valores analógicos de los sensores LDR
  int valorLDRArriba = analogRead(PIN_LDR_Arriba);
  int valorLDRDerecha = analogRead(PIN_LDR_Derecha);
  int valorLDRAbajo = analogRead(PIN_LDR_Abajo);
  int valorLDRIzquierda = analogRead(PIN_LDR_Izquierda);
  
  // Imprimir los valores leídos - Imprime: "LDR Up: valor, Right: valor, Down: valor, Left: valor"
  Serial.print("LDR Up: " + String(valorLDRArriba) + ", ");
  Serial.print("Right: " + String(valorLDRDerecha) + ", ");
  Serial.print("Down: " + String(valorLDRAbajo) + ", ");
  Serial.println("Left: " + String(valorLDRIzquierda));


  //Esperar 3 segundos
  delay(1000);
}



//  ------------------- Metodos de Inicialisacion componentes -------------------


// Funciones de configuración y utilidad
void inicializarPinesModoUso() {
  pinMode(PIN_BTNModoManual, INPUT);
  pinMode(PIN_LEDModoManual, OUTPUT);
  pinMode(PIN_BTNModoAutomatico, INPUT);
  pinMode(PIN_LEDModoAutomatico, OUTPUT);

  // digitalWrite(PIN_LEDModoManual, HIGH);  // Enciende el LED del modo manual por defecto
  digitalWrite(PIN_LEDModoAutomatico, HIGH);
}

// Función para inicializar los servos
void inicializarServos() {
  m_servoHorizontal.attach(PIN_ServoHorizontal);             // Adjunta el servo horizontal al pin 11
  m_servoVertical.attach(PIN_BTNModoAutomatico);               // Adjunta el servo vertical al pin 10
 
  moveHorizontal(10);
  // Estableser Posición inicial de los servos
  // m_servoHorizontal.write(180);             // Posición inicial del servo horizontal
  // m_servoVertical.write(180);               // Posición inicial del servo vertical
}

// Metodo para iniciar el sensor LDR 
void iniciarSensorLDR() {
  pinMode(PIN_LDR_Arriba, INPUT);
  pinMode(PIN_LDR_Izquierda, INPUT);
  pinMode(PIN_LDR_Abajo, INPUT);
  pinMode(PIN_LDR_Derecha, INPUT);
}


// ------------------- --- ------------------- 


// // ------------------- Codigo Obsoleto -------------------
// // Metodo para que revisa que no se alla precionado lagun boton 
// // par los moteods de uso y si es asi actualiza el modo de uso selecionado por boton 
// void actualizarModo() {
//   if (digitalRead(PIN_BTNModoManual) == HIGH) {
//     modoManualActivo = true;
//     digitalWrite(PIN_LEDModoManual, HIGH); //  ensiende led modo modo manual
//     digitalWrite(PIN_LEDModoAutomatico, LOW);
//   } else if (digitalRead(PIN_BTNModoAutomatico) == HIGH) {
//     modoManualActivo = false;
//     digitalWrite(PIN_LEDModoAutomatico, HIGH);
//     digitalWrite(PIN_LEDModoManual, LOW);
//   }
// }
// // ------------------- --- -------------------


/**
 * Actualiza el modo de operación basado en la entrada del usuario.
 * Este método verifica si alguno de los botones de modo ha sido presionado.
 * Si se detecta un botón presionado, el sistema actualiza el modo de uso
 * y cambia la indicación LED correspondiente.
 */
void actualizarModo() {
  
  // Verifica si el botón para el modo manual ha sido presionado.
  if (digitalRead(PIN_BTNModoManual) == HIGH) {
    // Si el botón de modo manual está presionado, activa el modo manual.
    modoManualActivo = true;

    // Enciende el LED indicador del modo manual.
    digitalWrite(PIN_LEDModoManual, HIGH);

    // Apaga el LED indicador del modo automático.
    digitalWrite(PIN_LEDModoAutomatico, LOW);
  } // fin if modo manual


  // Verifica si el botón para el modo automático ha sido presionado.
  else if (digitalRead(PIN_BTNModoAutomatico) == HIGH) {
    // Si el botón de modo automático está presionado, desactiva el modo manual.
    modoManualActivo = false;

    // Enciende el LED indicador del modo automático.
    digitalWrite(PIN_LEDModoAutomatico, HIGH);

    // Apaga el LED indicador del modo manual.
    digitalWrite(PIN_LEDModoManual, LOW);
  } // fin if modo automatico


} // Fin de la función 'actualizarModo'
    



// Metodo para mover servos con Joystick 
void controlarServosConJoystick() {
    int valorX = analogRead(PIN_JoystickX); // Lee el valor del eje X del joystick
    int valorY = analogRead(PIN_JoystickY); // Lee el valor del eje Y del joystick

      // Umbrales para el movimiento del joystick
    int umbralInferior = 400; // Valor debajo del cual se mueve el servo hacia un extremo
    int umbralSuperior = 600; // Valor por encima del cual se mueve el servo hacia el otro extremo



    // Definir topes de movimiento para los servos !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Movimiento Horizontal
    if (valorX < umbralInferior) {
        m_ServoHorizontalPosicion--; // Mueve hacia la izquierda
    } else if (valorX > umbralSuperior) {
        m_ServoHorizontalPosicion++; // Mueve hacia la derecha
    }

    // Movimiento Vertical
    if (valorY < umbralInferior) {
        m_ServoVerticalPosicion--; // Mueve hacia abajo
    } else if (valorY > umbralSuperior) {
        m_ServoVerticalPosicion++; // Mueve hacia arriba
    }

    // Modificar Movimiento Vertical




    // Restringe los valores de los servos a su rango permitido

    // Velocidad de movimiento de eje Vertical En este caso se mueve cada 5 grados \
    int m_velocidadMovimiento = 5;
    m_ServoHorizontalPosicion = m_ServoHorizontalPosicion * m_velocidadMovimiento;





     m_ServoHorizontalPosicion = constrain(m_ServoHorizontalPosicion, 0, 180);
    // m_ServoVerticalPosicion = constrain(m_ServoVerticalPosicion, 0, 180);

    // Mueve los servos a las nuevas posiciones
    m_servoHorizontal.write(m_ServoHorizontalPosicion);
    m_servoVertical.write(m_ServoVerticalPosicion);



}


// Metodo para controlar servos con el sensor LDR
void controlarServosConLDR() {
  // Aquí el código para mover los servos con los sensores LDR
  int valorLDRArriba = analogRead(PIN_LDR_Arriba);
  int valorLDRDerecha = analogRead(PIN_LDR_Derecha);
  int valorLDRAbajo = analogRead(PIN_LDR_Abajo);
  int valorLDRIzquierda = analogRead(PIN_LDR_Izquierda);
  
    // Determinar la dirección de la luz más intensa de lado vertical
  if (valorLDRArriba > valorLDRAbajo 
      && valorLDRArriba > valorLDRDerecha  
      && valorLDRArriba > valorLDRIzquierda) {
    moveVertical(-1); // Mover hacia arriba

  } else if (valorLDRAbajo > valorLDRArriba 
              && valorLDRAbajo > valorLDRDerecha 
              && valorLDRAbajo > valorLDRIzquierda) {
    moveVertical(1); // Mover hacia abajo

  } else if (valorLDRDerecha > valorLDRArriba  
             && valorLDRDerecha > valorLDRAbajo 
             && valorLDRDerecha > valorLDRIzquierda) {              
    moveHorizontal(1); // Mover hacia la derecha

  } else if (valorLDRIzquierda > valorLDRArriba 
              && valorLDRIzquierda > valorLDRAbajo 
              && valorLDRIzquierda > valorLDRDerecha) {
    moveHorizontal(-1); // Mover hacia la izquierda
  
  }
}


// Lee los valores de los sensores de amperaje y voltaje
void leerSensores() {
  leerAmperaje();
  leerVoltaje();
}

// lee el amperaje del sensor de amperaje
void leerAmperaje() {
  int sensorValue = analogRead(PIN_SensorAmperaje);
  float voltage = (sensorValue * 5.0) / 1023.0;
  currentAmperage = (voltage - 2.5) / 0.185;
}
// lee el voltaje del sensor de voltaje
void leerVoltaje() {
  int sensorValue = analogRead(PIN_SensorVoltaje);
  currentVoltage = sensorValue * (5.0 / 1023.0) * 5 * 0.927;
}


// Muestra datos de los datos de los sensores de 
// amperaje y voltaje en el monitor serial
// Amperaje: 0.00 A, Voltaje: 0.00 V
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
  inicializarPinesModoUso();
  inicializarServos();
  iniciarSensorLDR(); 
  // mostrarDatos();
}


// Loop principal
void loop() {
  // Metodo para Ferificar si los Sensores LDR estan bine
  // es decir si los pines corresponden a las ubicaciones 
  // up Dwon lert joint

  // verificarSensoresLDR();
  
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
