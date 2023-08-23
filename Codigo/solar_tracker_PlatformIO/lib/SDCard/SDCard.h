#ifndef SDCard_h
#define SDCard_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <RTClib.h>

/**
 * @class SDCard
 * @brief Gestiona las operaciones relacionadas con una tarjeta SD, como guardar y leer datos.
 * 
 * Esta clase se encarga de interactuar con una tarjeta SD, permitiendo guardar datos
 * del Solar Tracker y también obtener información guardada previamente.
 */
class SDCard
{
public:
    /**
     * @brief Constructor que inicializa la tarjeta SD.
     * 
     * @param chipSelectPin Pin CS utilizado para comunicarse con la tarjeta SD.
     */
    SDCard(uint8_t chipSelectPin);

    /**
     * @brief Inicializa la tarjeta SD.
     * 
     * @return true si la inicialización es exitosa, false en caso contrario.
     */
    bool begin();

    /**
     * @brief Obtiene el lugar físico donde se encuentra el Solar Tracker.
     * 
     * @return Un string con el nombre del lugar.
     */
    String getLugarFisico();

    /**
     * @brief Establece y guarda el lugar físico donde se encuentra el Solar Tracker.
     * 
     * @param lugarFisico El nombre del lugar donde está el Solar Tracker.
     * @return true si el lugar fue guardado exitosamente, false en caso contrario.
     */
    bool setLugarFisico(String lugarFisico);

    /**
     * @brief Obtiene los minutos de espera entre guardados de datos en la tarjeta SD.
     * 
     * @return El número de minutos de espera.
     */
    uint8_t getMinutosEspera();

    /**
     * @brief Establece y guarda los minutos de espera entre guardados de datos en la tarjeta SD.
     * 
     * @param minutosEspera El número de minutos de espera.
     * @return true si se estableció exitosamente, false en caso contrario.
     */
    bool setMinutosEspera(uint8_t minutosEspera);

    /**
     * @brief Guarda datos del Solar Tracker en un archivo de la tarjeta SD.
     * 
     * @param fecha_hora La fecha y hora del registro.
     * @param amperaje El amperaje medido.
     * @param voltaje El voltaje medido.
     * @param potencia La potencia calculada.
     * @return true si los datos se guardaron exitosamente, false en caso contrario.
     */
    bool guardarDatos(DateTime fecha_hora, float amperaje, float voltaje, float potencia);

private:
    const uint8_t _chipSelectPin;  // Pin CS para comunicación con la tarjeta SD.
    
    String _lugarFisico = "Salto"; // Ubicación predeterminada del Solar Tracker.
    uint8_t _minutosEspera = 5;   // Intervalo predeterminado para guardar datos.

    bool _estadoSD; // Estado actual de la tarjeta SD.

    // Nombres de archivos en la tarjeta SD.
    static constexpr const char* _fichDatos = "datos.txt";   // Archivo de datos del Solar Tracker.
    static constexpr const char* _fichConfig = "config.txt"; // Archivo de configuración del Solar Tracker.

    // Trae la configuración desde la tarjeta SD.
    bool loadConfig(); // Carga configuración desde la tarjeta SD.
    bool updateConfigFile(uint8_t minutosEspera, String lugarFisico); // Actualiza el archivo de configuración en la tarjeta SD.
    String _getJSON(DateTime fecha_hora, float amperaje, float voltaje, float potencia); // Genera una representación JSON de los datos.
    DynamicJsonDocument getDataInRange(DateTime fecha_hora_inicio, DateTime fecha_hora_fin); // Obtiene datos en un rango de fechas específico.
};

#endif // SDCard_h
