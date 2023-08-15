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

void ServoSolarTrak::setModoUso(unsigned char modoFuncionamiento)
{
    // Validar el valor del modo de funcionamiento
    // Solo permitir los valores 1, 2 o 3
    if (modoFuncionamiento >= 1 && modoFuncionamiento <= 3)
    {
        _modoFuncionamiento = modoFuncionamiento;
    }
    else
    {
        _modoFuncionamiento = 3; // Si mandan un numero que no es igual a 3 que seria detenido
    }
}

// Actualiza el estado de los servos
void ServoSolarTrak::upgradeServo()
{
    switch (_modoFuncionamiento)
    {
    case 1: // Modo Manual
        ServoSolarTrak::_upgradeJoystick();
        break;
    case 2: // Modo Motor Horizontal
        ServoSolarTrak::_upgradeJoystickVertical();
        ServoSolarTrak::_upgradeLDRH();
        break;
    case 3: // Modo Automatico
        ServoSolarTrak::_upgradeLDRH();
        break
    }
}

// Modifica el los Ángulos de los servos utilizando el Joystick Arduino KY 023
void ServoSolarTrak::_upgradeJoystick()
{
    int valX = analogRead(_JOYSTICK_HORISONTAL_PIN);
    int valY = analogRead(_JOYSTICK_VERTICAL_PIN);

    int Valor_Xmax = 1023; // Constante del valor máximo para X
    int Valor_Xmin = 0;    // Constante del valor mínimo para X

    int Valor_Ymax = 1023; // Constante del valor máximo para Y
    int Valor_Ymin = 0;    // Constante del valor mínimo para Y

    if (valX > 511)
    {                                   // Movimiento del eje X a lado Izquierdo partiendo del centro (valor de 511)
        Valor_Xmax = 1023 - valX + 511; // La constante del valor máximo para X se modificara con el nuevo valor
        Valor_Xmin = 0;                 // La constante del valor mínimo se mantendrá
    }
    else if (valX < 511)
    {                            // Movimiento del eje X a lado Derecho partiendo del centro (valor de 511)
        Valor_Xmax = 1023;       // La constante del valor máximo se mantendrá
        Valor_Xmin = 511 - valX; // La constante del valor mínimo para X se modificara con el nuevo valor
    }

    if (valY > 511)
    {                                   // Movimiento del eje Y hacia Arriba partiendo del centro (valor de 511)
        Valor_Ymax = 1023 - valY + 511; // La constante del valor máximo para Y se modificara con el nuevo valor
        Valor_Ymin = 0;                 // La constante del valor mínimo se mantendrá
    }
    else if (valY < 511)
    {                            // Movimiento del eje Y hacia Abajo partiendo del centro (valor de 511)
        Valor_Ymax = 1023;       // La constante del valor máximo se mantendrá
        Valor_Ymin = 511 - valY; // La constante del valor mínimo para Y se modificara con el nuevo valor
    }

    int mappedX = map(valX, Valor_Xmin, Valor_Xmax, 0, 180);
    int mappedY = map(valY, Valor_Ymin, Valor_Ymax, 0, 180);

    setHorizontalAngle(mappedX);
    setVerticalAngle(mappedY);
}

// Modifica el angulo del servo vertical utilizando el Joystick Arduino KY 023
void ServoSolarTrak::_upgradeJoystickVertical()
{

    int valY = analogRead(_JOYSTICK_VERTICAL_PIN);

    int Valor_Ymax = 1023; // Constante del valor máximo para Y
    int Valor_Ymin = 0;    // Constante del valor mínimo para Y

    bool flag = false; // Banint mappedX = map(valX, Valor_Xmin, Valor_Xmax, 0, 180);dera para saber si se ha movido el joystick

    if (valY > 511)
    {                                   // Movimiento del eje Y hacia Arriba partiendo del centro (valor de 511)
        Valor_Ymax = 1023 - valY + 511; // La constante del valor máximo para Y se modificara con el nuevo valor
        Valor_Ymin = 0;                 // La constante del valor mínimo se mantendrá
    }
    else if (valY < 511)
    {                            // Movimiento del eje Y hacia Abajo partiendo del centro (valor de 511)
        Valor_Ymax = 1023;       // La constante del valor máximo se mantendrá
        Valor_Ymin = 511 - valY; // La constante del valor mínimo para Y se modificara con el nuevo valor
    }
    
    int mappedY = map(valY, Valor_Ymin, Valor_Ymax, 0, 180);

    setHorizontalAngle(mappedX);
    setVerticalAngle(mappedY);
}

// Modifica los angulos de los servos utilizando las fotoreistencias LDR
void ServoSolarTrak::_upgredeLDR()
{
    // Realizar el seguimiento automático en ambos ejes
    int ldrUpValue = analogRead(_LDR_UP_PIN);
    int ldrDownValue = analogRead(_LDR_DOWN_PIN);
    int ldrRightValue = analogRead(_LDR_RIGHT_PIN);
    int ldrLeftValue = analogRead(_LDR_LEFT_PIN);

    int verticalAngle = map(ldrUpValue - ldrDownValue, -_LDR_MAX, _LDR_MAX, _VERTICAL_MIN_ANGLE, _VERTICAL_MAX_ANGLE);
    int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

    servoVertical.write(verticalAngle);
    servoHorizontal.write(horizontalAngle);
}

// Modifica el angulo del servo vertical utilizando las fotoreistencias LDR
void ServoSolarTrak::_upbradeLDRHorisontal()
{
    // Realizar el seguimiento automático en ambos ejes
    int ldrRightValue = analogRead(_LDR_RIGHT_PIN);
    int ldrLeftValue = analogRead(_LDR_LEFT_PIN);

    int horizontalAngle = map(ldrLeftValue - ldrRightValue, _LDR_MAX, _LDR_MAX, _HORIZONTAL_MIN_ANGLE, _HORIZONTAL_MAX_ANGLE);

    servoHorizontal.write(horizontalAngle);
}
