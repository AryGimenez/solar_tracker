#include "ServoSolarTrak.h"

// Constructor de la clase `ServoSolarTrak`.
// Este método inicializa las variables miembro con los valores de los pines proporcionados.
ServoSolarTrak::ServoSolarTrak(uint8_t verticalPin,           // Pin del servo vertical
                               uint8_t horizontalPin,         // Pin del servo horizontal
                               uint8_t ldrUpPin,              // Pin del sensor LDR superior
                               uint8_t ldrDownPin,            // Pin del sensor LDR inferior
                               uint8_t ldrRightPin,           // Pin del sensor LDR derecho
                               uint8_t ldrLeftPin,            // Pin del sensor LDR izquierdo
                               uint8_t joystickVerticalPin,   // Pin vertical del joystick
                               uint8_t joystickHorizontalPin) // Pin horizontal del joystick

    // Inicialización de las variables miembro usando la lista de inicialización.
    : _servoVerticalPin(verticalPin), 
      _servoHorizontalPin(horizontalPin),
      _ldr_up_pin(ldrUpPin),
      _ldr_down_pin(ldrDownPin),
      _ldr_right_pin(ldrRightPin),
      _ldr_left_pin(ldrLeftPin),
      _joystick_vertical_pin(joystickVerticalPin),
      _joystick_horizontal_pin(joystickHorizontalPin)
{}


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
void ServoSolarTrak::setVerticalAngle(uint8_t angle)
{
    angle = constrain(angle, 0, 180);
    _servoVertical.write(angle);
}

// Establece el ángulo del servomotor horizontal
void ServoSolarTrak::setHorizontalAngle(uint8_t angle)
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
        ServoSolarTrak::_upgradeLDRHorizontal();
        break;
    case 3: // Modo Automatico
        ServoSolarTrak::_upgradeLDR();
        break;
    }
}

// Modifica el los Ángulos de los servos utilizando el Joystick Arduino KY 023
void ServoSolarTrak::_upgradeJoystick()
{
    int valX = analogRead(_joystick_horizontal_pin);
    int valY = analogRead(_joystick_vertical_pin);

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

    int valY = analogRead(_joystick_vertical_pin);

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

    setVerticalAngle(mappedY);
}

// Modifica los angulos de los servos utilizando las fotoreistencias LDR
void ServoSolarTrak::_upgradeLDR()
{
    // Realizar el seguimiento automático en ambos ejes
    int ldrUpValue = analogRead(_ldr_up_pin);
    int ldrDownValue = analogRead(_ldr_down_pin);
    int ldrRightValue = analogRead(_ldr_right_pin);
    int ldrLeftValue = analogRead(_ldr_left_pin);

    int verticalAngle = map(ldrUpValue - ldrDownValue, -_ldr_max, _ldr_max, _vertical_min_angle, _vertical_max_angle);
    int horizontalAngle = map(ldrLeftValue - ldrRightValue, _ldr_max, _ldr_max, _horizontal_min_angle, _horizontal_max_angle);

    _servoVertical.write(verticalAngle);
    _servoHorizontal.write(horizontalAngle);
}

// Modifica el angulo del servo vertical utilizando las fotoreistencias LDR
void ServoSolarTrak::_upgradeLDRHorizontal()
{
    // Realizar el seguimiento automático en ambos ejes
    int ldrRightValue = analogRead(_ldr_right_pin);
    int ldrLeftValue = analogRead(_ldr_left_pin);

    int horizontalAngle = map(ldrLeftValue - ldrRightValue, _ldr_max, _ldr_max, _horizontal_min_angle, _horizontal_max_angle);

    _servoHorizontal.write(horizontalAngle);
}
