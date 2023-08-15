#ifndef BusI2C_h
#define BusI2C_h

#include <Arduino.h>
#include <Wire.h>

class BusI2C{
private:
    const int _RTC_SDA_PIN;
    const int _RTC_SCL_PIN;



public:
    BusI2C(int RTC_SDA_PIN, int RTC_SCL_PIN);

    // Inicializacion de la comunicación I2C con los pines SDA y SCL
    void begin();

};
 