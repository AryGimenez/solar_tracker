#include "ServoSolarTrak.h"

ServoSolarTrak::ServoSolarTrak(int verticalPin, int horizontalPin)
{
    _servoVerticalPin = verticalPin;
    _servoHorizontalPin = horizontalPin;
}

// Inicialización de los pines de los servos
void ServoSolarTrak::attach()
{
    _servoVertical.attach(_servoVerticalPin);
    _servoHorizontal.attach(_servoHorizontalPin);
}
// Deteien los Servomotores 
void ServoSolarTrak::detach()
{
    _servoVertical.detach();
    _servoHorizontal.detach();
}

void ServoSolarTrak::setVerticalAngle(int angle)
{
    angle = constrain(angle, 0, 180);
    _servoVertical.write(angle);
}

void ServoSolarTrak::setHorizontalAngle(int angle)
{
    angle = constrain(angle, 0, 180);
    _servoHorizontal.write(angle);
}