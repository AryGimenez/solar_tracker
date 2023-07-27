#include "RelojRTC.h"

RelojRTC::RelojRTC(
    int RTC_SDA_PIN, 
    int RTC_SCL_PIN) 
    : 
    _RTC_SDA_PIN(RTC_SDA_PIN), 
    _RTC_SCL_PIN(RTC_SCL_PIN) 
{}

void RelojRTC::begin() {
  Wire.begin(_RTC_SDA_PIN, _RTC_SCL_PIN);
  _moduloRelojRTC.begin();

  if (!_moduloRelojRTC.isrunning()) {
    // Establecemos la fecha y hora del reloj RTC en la compilación del programa
    _moduloRelojRTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void RelojRTC::actualizar() {
  _fechaHora = _moduloRelojRTC.now();
}

DateTime RelojRTC::getFechaHora() {
  return _fechaHora;
}
