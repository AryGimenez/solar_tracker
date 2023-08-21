#ifndef  SensorVAI_h
#define SensorVAI_h

#include <Arduino.h>
// Clase que permite obtener los valores de voltaje, amperaje y potencia
class SensorVAI{


public:

    SensorVAI(uint8_t sensorAmperajePIN, uint8_t sensorVoltajePIN);

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
    float _voltaje = 0;
    float _amperaje = 0; 
    float _potencia = 0; 

    const uint8_t _sensorAmperajePIN; // Sensor ACS712
    const uint8_t _sensorVoltajePIN; // Sensor FZ0430


};

#endif // SensorVAI_h