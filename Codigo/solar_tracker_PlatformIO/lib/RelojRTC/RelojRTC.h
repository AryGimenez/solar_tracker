#ifndef RelojRTC_h
#define RelojRTC_h

#include <Arduino.h>
#include <RTClib.h>

class RelojRTC {
public:
  RelojRTC();
  void begin();
  void actualizar();
  DateTime getFechaHora();
  String getFechaHoraString();
  // Método para establecer una nueva fecha y hora en el módulo RTC
  void setFechaHora(DateTime fechaHora);
  // Método para establecer una nueva fecha y hora en el módulo RTC
  void setFechaHora(int year, int month, int day, int hour, int minute, int second);
  
  // Actualiza la fecha y hora almacenadas en el RelojRTC
  void actualizar();
  // Verificar si han pasado suficientes minutos desde la última actualización
  bool hanPasadoMinutos();
  // Reiniciar el contador de minutos
  void resetPasadoMinutos()

private:
    // Verificar si han pasado suficientes minutos desde la última actualización
    
    RTC_DS3231 _moduloRelojRTC;
    DateTime _fechaHora;
    // Variable que utilizamos para calcular cuando se cumplió el plazo que deseamos 
    // guardar para guardar los datos en la tarjeta SD 
    DateTime _fechaDisparador; 
    // Variable para almacenar 
    bool _hanPasadoMinutos = false;
    
    const bool _estadoRTC = true; // Estado del módulo de reloj Tiny RTC (true = Funciona, false = No funciona)
    //Led Advertencia
    const int _esperaMinutos = 5; // Espera en mitutos para guardar los datos en la tarjeta SD
};

#endif
