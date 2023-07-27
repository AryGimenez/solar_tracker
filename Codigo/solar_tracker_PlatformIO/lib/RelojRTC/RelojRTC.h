#ifndef RelojRTC_h
#define RelojRTC_h

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

class RelojRTC {
public:
  RelojRTC(int RTC_SDA_PIN, int RTC_SCL_PIN);
  void begin();
  void actualizar();
  DateTime getFechaHora();

private:
    RTC_DS3231 _moduloRelojRTC;
    DateTime _fechaHora;

    // Definición de los pines para el módulo de reloj Tiny RTC
    const int _RTC_SDA_PIN;
    const int _RTC_SCL_PIN;
};

#endif
