#ifndef ServoSolarTrak_h
#define ServoSolarTrak_h

#include <Arduino.h>
#include <Servo.h>

class ServoSolarTrak {
public:
    // Constructor de la clase que recibe los pines de los servos como parámetros
    ServoSolarTrak(int verticalPin, int horizontalPin);

    void attach(); // Inicialización de los pines de los servos
    void detach(); // Detener los servos
    void setVerticalAngle(int angle); // Establecer el ángulo vertical del servo
    void setHorizontalAngle(int angle); // Establecer el ángulo horizontal del servo
    
    // Establece el modo funcionamiento 
    // 1 - Modo Manual 
    // 2 - Modo Motor Horizontal
    // 3 - Modo Automático 
    void setModoUso(unsigned char modoFuncionamiento);  
    
    // Actuializa el estado de los servos
    void upgradeServo();
private:
    int _servoVerticalPin; // Pin para el servo vertical
    int _servoHorizontalPin; // Pin para el servo horizontal
    Servo _servoVertical; // Objeto del servo vertical
    Servo _servoHorizontal; // Objeto del servo horizontal

    // Establece el modo funcionamiento 
    // 1 - Modo Manual 
    // 2 - Modo Motor Horizontal
    // 3 - Modo Automático 
    unsigned char _modoFuncionamiento = 0;

    // Rangos para calibrar los valores de las fotorresistencias
    const int _LDR_MIN = 0;
    const int _LDR_MAX = 1023;

    // Valores límite para el movimiento de los servos
    const int _VERTICAL_MIN_ANGLE = 0;
    const int _VERTICAL_MAX_ANGLE = 180;
    const int _HORIZONTAL_MIN_ANGLE = 0;
    const int _HORIZONTAL_MAX_ANGLE = 180;


    // Definición de los pines de las fotorresistencias
    const int _LDR_UP_PIN;
    const int _LDR_DOWN_PIN;
    const int _LDR_RIGHT_PIN;
    const int _LDR_LEFT_PIN;

};

#endif // ServoSolarTrak_h
