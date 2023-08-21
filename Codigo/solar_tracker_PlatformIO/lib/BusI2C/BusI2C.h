#ifndef BusI2C_h
#define BusI2C_h

#include <Arduino.h>
#include <Wire.h>

class BusI2C{
public:
    BusI2C(uint8_t rtcSDA_PIN, uint8_t rtcSCL_PIN);

    // Inicializacion de la comunicación I2C con los pines SDA y SCL
    void begin();

private:
    const uint8_t _rtcSDA_PIN;
    const uint8_t _rtcSCL_PIN;
};

#endif // BusI2C_h
 