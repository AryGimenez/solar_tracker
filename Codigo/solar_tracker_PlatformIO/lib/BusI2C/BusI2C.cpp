#include "BusI2C.h"

// Constructor de la clase que recibe los pines SDA y SCL del bus I2C
BusI2C::BusI2C(int RTC_SDA_PIN, int RTC_SCL_PIN)
    : _RTC_SDA_PIN(RTC_SDA_PIN),
      _RTC_SCL_PIN(RTC_SCL_PIN)
{
}

// Inicializacion de la comunicación I2C con los pines SDA y SCL
void BusI2C::begin()
{
    // Inicializar el bus I2C con los pines SDA y SCL
    Wire.begin(_RTC_SDA_PIN, _RTC_SCL_PIN);
}