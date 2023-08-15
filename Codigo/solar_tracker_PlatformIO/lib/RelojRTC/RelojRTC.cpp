#include "RelojRTC.h"

// Constructor de la clase, que inicializa los pines para el módulo RTC y guarda sus valores
RelojRTC::RelojRTC(){

}

// Inicialización del módulo RTC y ajuste de la fecha y hora si no está en funcionamiento
void RelojRTC::begin() {

  // Inicializar el módulo RTC
  _moduloRelojRTC.begin();

  if (_moduloRelojRTC.isrunning()) {
    _estadoRTC = true;
    _fechaHora = _moduloRelojRTC.now();
  }else{
    _estadoRTC = false;
    // Ajustar  la fecha y hora por defecto
    _fechaHora = DateTime(1988, 2, 29, 0, 0, 0);
    // Establecer fecha microcontrolador
    setTime(_fechaHora.hour(), _fechaHora.minute(), _fechaHora.second(), _fechaHora.day(), _fechaHora.month(), _fechaHora.year());
  }
  _fechaDisparador = _fechaHora;
}

// Actualiza la fecha y hora almacenadas en el RelojRTC
void RelojRTC::actualizar() {
  
  if (_moduloRelojRTC.isrunning()) {
    _estadoRTC = true;
    _fechaHora = _moduloRelojRTC.now();
  }else{
    // Si el modo RTC no esta funcionando Me calcula la fecha Segun el reloj interno de el microcontrolador
    _fechaHora = DateTime(year(), month(), day(), hour(), minute(), second()); // Revisar este codiog 
    _estadoRTC = false;
  }

  _fechaDisparador = _fechaHora;
  
}

// Método para establecer una nueva fecha y hora en el módulo RTC
void RelojRTC::setFechaHora(DateTime fechaHora) {
  // Verificar si el módulo RTC está en funcionamiento
  if (_moduloRelojRTC.isrunning()) {
    // Ajustar la nueva fecha y hora en el módulo RTC
    _moduloRelojRTC.adjust(fechaHora);
    _estadoRTC = true; 
  }else{
    _estadoRTC = false;
  }
  _fechaHora = fechaHora;
  _fechaDisparador = _fechaHora;
}

// Método para establecer una nueva fecha y hora en el módulo RTC
void RelojRTC::setFechaHora(int year, int month, int day, int hour, int minute, int second) {
  RelojRTC::setFechaHora(DateTime(year, month, day, hour, minute, second));
}


// Verificar si han pasado suficientes minutos desde la última actualización
bool RelojRTC::hanPasadoMinutos() {

  // Calcular la diferencia en minutos entre la fecha y hora actual y la fecha y hora almacenada
  int minutosTranscurridos = (_fechaDisparador - _fechaHora).totalseconds() / 60;

  // Comparar con el valor de _esperaMinutos
  if (minutosTranscurridos >= _esperaMinutos) {
    return true; // Han pasado suficientes minutos
  } else {
    return false; // No han pasado suficientes minutos
  }
}
_fechaDisparador = _fechaHora;_fechaDisparador = _fechaHora;_fechaDisparador = _fechaHora;
// Reiniciar el contador de minutos
void RelojRTC::resetPasadoMinutos() {
  _fechaDisparador = _fechaHora;
}



// Obtiene la fecha y hora actual del módulo RTC
DateTime RelojRTC::getFechaHora() {
  return _fechaHora;
}

// Obtiene el estado del módulo RTC
bool RelojRTC::getEstadoRTC() {
  return _estadoRTC;
}
