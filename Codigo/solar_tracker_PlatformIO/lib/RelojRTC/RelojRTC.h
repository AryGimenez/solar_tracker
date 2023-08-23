#ifndef RelojRTC_h
#define RelojRTC_h

#include <Arduino.h>
#include <RTClib.h>
#include <TimeLib.h>

/**
 * @class RelojRTC
 * @brief Gestiona la funcionalidad del módulo de reloj RTC DS3231.
 */
class RelojRTC {
public:
    /**
     * @brief Constructor predeterminado para inicializar la instancia del reloj RTC.
     */
    RelojRTC();

  /**
   * @brief Inicializa el módulo RTC y verifica su estado.
   * Si el RTC ha perdido energía, mantiene la hora actual. En caso contrario, ajusta al valor por defecto.
   * @return Estado de funcionamiento del módulo RTC: true si está funcionando correctamente, false si ha perdido energía.
   */
    bool begin();

    /**
     * @brief Obtiene la fecha y hora actuales del módulo RTC.
     * @return Retorna un objeto DateTime con la fecha y hora actuales.
     */
    DateTime getFechaHora();
  
    /**
     * @brief Establece una nueva fecha y hora en el módulo RTC.
     * @param fechaHora Objeto DateTime con la fecha y hora a establecer.
     */
    void setFechaHora(DateTime fechaHora);
  
    /**
     * @brief Establece una nueva fecha y hora en el módulo RTC.
     * @param year Año a establecer.
     * @param month Mes a establecer.
     * @param day Día a establecer.
     * @param hour Hora a establecer.
     * @param minute Minuto a establecer.
     * @param second Segundo a establecer.
     */
    void setFechaHora(int year, int month, int day, int hour, int minute, int second);
  
    /**
     * @brief Actualiza la fecha y hora almacenadas en el objeto a partir del módulo RTC.
     * @return Retorna true si han pasado los minutos establecidos, de lo contrario retorna false.
     */
    bool update();

    /**
     * @brief Verifica si han pasado suficientes minutos desde la última actualización.
     * @return Retorna true si han pasado los minutos establecidos, de lo contrario retorna false.
     */
    bool hanPasadoMinutos();

    /**
     * @brief Reinicia el contador de minutos desde la última actualización.
     */
    void resetPasadoMinutos();

    /**
     * @brief Obtiene el estado de funcionamiento del módulo RTC.
     * @return Retorna true si el módulo RTC está funcionando correctamente, de lo contrario retorna false.
     */
    bool getEstadoRTC();
    /**
     * @brief Modifica el los minutos de espera para determinar si han pasado suficientes minutos desde la última actualización.
    */
    void setEsperaMinutos(uint8_t esperaMinutos);

private:
    RTC_DS3231 _moduloRelojRTC;  // Instancia del módulo RTC DS3231.
    DateTime _fechaHora;         // Fecha y hora actuales obtenidas del módulo RTC.
    DateTime _fechaDisparador;   // Marca de tiempo utilizada para determinar el intervalo de actualización.
    
    bool _hanPasadoMinutos = false; // Bandera que indica si ha pasado el tiempo de espera.
    bool _estadoRTC = true;        // Estado de funcionamiento del módulo RTC.
    
    uint8_t _esperaMinutos = 5;    // Intervalo en minutos para determinar si se ha cumplido el tiempo de espera.
};

#endif // RelojRTC_h
