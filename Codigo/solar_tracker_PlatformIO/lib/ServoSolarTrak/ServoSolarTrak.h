#ifndef ServoSolarTrak_h
#define ServoSolarTrak_h

#include <Arduino.h>
#include <Servo.h>

class ServoSolarTrak {

public:

    // Constructor que inicializa los pines de los servomotores y sensores.
    ServoSolarTrak(uint8_t verticalPin,               // Pin del servo vertical
                   uint8_t horizontalPin,             // Pin del servo horizontal
                   uint8_t ldrUpPin,                 // Pin del sensor LDR superior
                   uint8_t ldrDownPin,               // Pin del sensor LDR inferior
                   uint8_t ldrRightPin,              // Pin del sensor LDR derecho
                   uint8_t ldrLeftPin,               // Pin del sensor LDR izquierdo
                   uint8_t joystickVerticalPin,      // Pin vertical del joystick
                   uint8_t joystickHorizontalPin);   // Pin horizontal del joystick


    void attach(); // Inicialización de los pines de los servos
    void detach(); // Detener los servos
    void setVerticalAngle(uint8_t angle); // Establecer el ángulo vertical del servo
    void setHorizontalAngle(uint8_t angle); // Establecer el ángulo horizontal del servo
    
    // Establece el modo funcionamiento 
    // 1 - Modo Manual 
    // 2 - Modo Motor Horizontal
    // 3 - Modo Automático 
    void setModoUso(unsigned char modoFuncionamiento);  
    
    // Actuializa el estado de los servos
    void upgradeServo();

private:
    const uint8_t _servoVerticalPin; // Pin para el servo vertical
    const uint8_t _servoHorizontalPin; // Pin para el servo horizontal
    Servo _servoVertical; // Objeto del servo vertical
    Servo _servoHorizontal; // Objeto del servo horizontal

    // Establece el modo funcionamiento 
    // 1 - Modo Manual 
    // 2 - Modo Motor Horizontal
    // 3 - Modo Automático 
    unsigned char _modoFuncionamiento = 0;

    // Rangos para calibrar los valores de las fotorresistencias ⬅️ ➡️
    const uint8_t _ldr_min = 0;
    const uint16_t _ldr_max = 1023;

    // Valores límite para el movimiento de los servos ⬆️⬇️ 
    const uint8_t _vertical_min_angle = 0; //⬇️
    const uint8_t _vertical_max_angle = 180; // ⬆️
    const uint8_t _horizontal_min_angle = 0; // ⬅️
    const uint8_t _horizontal_max_angle = 180; //  ➡️

    // Definición de los pines de las fotorresistencias 🌞
    const uint8_t _ldr_up_pin; // ⬆️
    const uint8_t _ldr_down_pin; // ⬇️
    const uint8_t _ldr_right_pin; // ➡️
    const uint8_t _ldr_left_pin; // ⬅️
    
    // Definición de los pines de Modulo Joystick Arduino KY 023 🕹️
    const uint8_t _joystick_vertical_pin; // Pin para el joystick vertical
    const uint8_t _joystick_horizontal_pin; // Pin para el joystick horizontal


    // Métodos para el control de los servos utilizando el Joystick Arduino KY 023 🕹️
    void _upgradeJoystick(); // Modifica el los Ángulos de los servos utilizando el Joystick (Para modo de funcionamiento 1 - Modo Manual)
    void _upgradeJoystickVertical(); // Modifica el angulo de el servo vertical utilizando el Joystick (Par funcionamiento 2 - Modo Motor Horizontal)
    
    // Métodos para el control de los servos utilizando las fotorresistencias 🌞
    void _upgradeLDR(); // Modifica los ángulos de los servos utilizando las fotorresistencias LDR (Para modo de funcionamiento 3 - Modo Automático))
    void _upgradeLDRHorizontal(); // Modifica el angulo de el servo horizontal utilizando las fotorresistencias LDR (Par modo de funcionamiento 2 - Modo Motor Horizontal)

};


#endif // ServoSolarTrak_h
