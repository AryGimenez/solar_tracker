#ifndef ServoSolarTrak_h
#define ServoSolarTrak_h

#include <Arduino.h>
#include <Servo.h>

class ServoSolarTrak {
public:
    ServoSolarTrak(int verticalPin, int horizontalPin);

    void attach(); // Inicialización de los pines de los servos
    void detach();
    void setVerticalAngle(int angle);
    void setHorizontalAngle(int angle);

private:
    int _servoVerticalPin;
    int _servoHorizontalPin;
    Servo _servoVertical;
    Servo _servoHorizontal;
};

#endif // ServoSolarTrak_h
