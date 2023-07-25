#include "ServoSolarTrak.h"

// Constructor de la clase, que inicializa los pines de los servomotores
ServoSolarTrak::ServoSolarTrak(int verticalPin, int horizontalPin)
{
    _servoVerticalPin = verticalPin;
    _servoHorizontalPin = horizontalPin;
}

// Inicialización de los pines de los servomotores
void ServoSolarTrak::attach()
{
    _servoVertical.attach(_servoVerticalPin);
    _servoHorizontal.attach(_servoHorizontalPin);
}

// Detiene los Servomotores
void ServoSolarTrak::detach()
{
    _servoVertical.detach();
    _servoHorizontal.detach();
}

// Establece el ángulo del servomotor vertical
void ServoSolarTrak::setVerticalAngle(int angle)
{
    angle = constrain(angle, 0, 180);
    _servoVertical.write(angle);
}

// Establece el ángulo del servomotor horizontal
void ServoSolarTrak::setHorizontalAngle(int angle)
{
    angle = constrain(angle, 0, 180);
    _servoHorizontal.write(angle);
}

void ServoSolarTrak::setModoUso(unsigned char modoFuncionamiento) {
    // Validar el valor del modo de funcionamiento
    // Solo permitir los valores 1, 2 o 3
    if (modoFuncionamiento >= 1 && modoFuncionamiento <= 3) {
        _modoFuncionamiento = modoFuncionamiento;
    } else {
        _modoFuncionamiento = 3; // Si mandan un numero que no es igual a 3 que seria detenido
    }
}

// Actuializa el estado de los servos 
void ServoSolarTrak::upgradeServo() {
    
    if (_modoFuncionamiento == 1) {
        // Modo Manual: Ajustar los ángulos según la configuración deseada
        setVerticalAngle(90); // Por ejemplo, ángulo vertical a 90 grados
        setHorizontalAngle(180); // Por ejemplo, ángulo horizontal a 180 grados
    } else if (_modoFuncionamiento == 2) {


    switch (_modoFuncionamiento) {
        case 1: // Modo Manual





        // Leer los valores analógicos de los sensores KY-023
        int verticalValue = analogRead(VERTICAL_PIN);
        int horizontalValue = analogRead(HORIZONTAL_PIN);

        // Mapear los valores leídos a ángulos para los servos
        int verticalAngle = map(verticalValue, 0, 1023, VERTICAL_MIN_ANGLE, VERTICAL_MAX_ANGLE);
        int horizontalAngle = map(horizontalValue, 0, 1023, HORIZONTAL_MIN_ANGLE, HORIZONTAL_MAX_ANGLE);

        // Mover los servos a los ángulos calculados
        servoVertical.write(verticalAngle);
        servoHorizontal.write(horizontalAngle);

        // Esperar un breve tiempo antes de leer nuevamente los valores
        delay(100);





        break;
        case 2: // Modo Motor Horizontal


            // Realizar el seguimiento automático en el eje horizontal
            int ldrRightValue = analogRead(LDR_RIGHT_PIN);
            int ldrLeftValue = analogRead(LDR_LEFT_PIN);

            int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

            servoHorizontal.write(horizontalAngle);        
        break;
        case 3: // Modo Automatico

            // Realizar el seguimiento automático en ambos ejes
            int ldrUpValue = analogRead(LDR_UP_PIN);
            int ldrDownValue = analogRead(LDR_DOWN_PIN);
            int ldrRightValue = analogRead(LDR_RIGHT_PIN);
            int ldrLeftValue = analogRead(LDR_LEFT_PIN);

            int verticalAngle = map(ldrUpValue - ldrDownValue, -_LDR_MAX, _LDR_MAX, _VERTICAL_MIN_ANGLE, _VERTICAL_MAX_ANGLE);
            int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

            servoVertical.write(verticalAngle);
            servoHorizontal.write(horizontalAngle);
            break
    }







    } else if (_modoFuncionamiento == 3) {
        // Modo Automático: Ajustar los ángulos automáticamente según el seguimiento solar
        // Aquí puedes implementar la lógica para el seguimiento solar automático
    }
} 