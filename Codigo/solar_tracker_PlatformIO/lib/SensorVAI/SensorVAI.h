#ifndef  SensorVAI_h
#define SensorVAI_h

#include <Arduino.h>
// Clase que permite obtener los valores de voltaje, amperaje y potencia
class SensorVAI{


public:

    SensorVAI(unsigned short sensorAmperajePIN, unsigned short sensorVoltajePIN);

    // Inicializa Los sensores de voltaje y amperaje
    void begin();
    // Actualiza los valores de voltaje y amperaje 
    // tmando los datos de los sensores FZ0430 (Voltaje) y ACS712 (Amperaje)  
    void update();

    // Retorna el voltaje
    float getVoltaje();

    // Retorna el amperaje
    float getAmperaje();

    // Retorna la potencia
    float getPotencia();

    

private:
    float _voltaje;
    float _amperaje; 
    float _potencia; 

    const unsigned short _sensorAmperajePIN; // Sensor ACS712
    const unsigned short _sensorVoltajePIN; // Sensor FZ0430


};