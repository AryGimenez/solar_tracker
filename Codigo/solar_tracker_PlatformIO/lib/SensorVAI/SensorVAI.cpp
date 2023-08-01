#include "SensorVAI.h"

// Constructor de la clase que recibe los pines de los sensores
SensorVAI::SensorVAI(unsigned short sensorAmperajePIN, unsigned short sensorVoltajePIN) 
    : _sensorAmperajePIN(sensorAmperajePIN), _sensorVoltajePIN(sensorVoltajePIN) {
    // Inicialización de variables privadas
    _voltaje = 0;
    _amperaje = 0;
    _potencia = 0;
}

void SensorVAI::begin() {
    // Configurar los pines de los sensores como entrada
    pinMode(_sensorAmperajePIN, INPUT);
    pinMode(_sensorVoltajePIN, INPUT);
}

void SensorVAI::update() {
    // Lee los valores de los sensores
    _amperaje = analogRead(_sensorAmperajePIN);
    _voltaje = analogRead(_sensorVoltajePIN);

    // Conversión a voltios y amperios según las características de tus sensores
    // Estos valores pueden cambiar dependiendo de los sensores específicos que estés utilizando.
    _amperaje = (_amperaje / 1024.0) * 5.0; // ejemplo de conversión, ajustar según tu sensor
    _voltaje = (_voltaje / 1024.0) * 5.0; // ejemplo de conversión, ajustar según tu sensor

    // Calcular la potencia P=VI
    _potencia = _voltaje * _amperaje;
}

float SensorVAI::getVoltaje() {
    return _voltaje;
}

float SensorVAI::getAmperaje() {
    return _amperaje;
}

float SensorVAI::getPotencia() {
    return _potencia;
}
