#include "BusI2C.h"

// Constructor de la clase que recibe los pines SDA y SCL del bus I2C
BusI2C::BusI2C(uint8_t rtcSDA_PIN, 
                uint8_t rtcSCL_PIN)
                : 
                _rtcSDA_PIN(rtcSDA_PIN),
                _rtcSCL_PIN(rtcSCL_PIN)
                
{}

// Inicializacion de la comunicación I2C con los pines SDA y SCL
void BusI2C::begin()
{
    // Inicializar el bus I2C con los pines SDA y SCL
    Wire.begin();
}