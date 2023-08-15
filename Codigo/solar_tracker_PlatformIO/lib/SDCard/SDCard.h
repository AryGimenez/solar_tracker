#ifndef SDCard_h
#define SDCard_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>

class SDCard
{
public:
    // Constructor de la clase que recibe el pin CS para la tarjeta SD
    SDCard(unsigned short chipSelectPin);

    // Inicializar de la tarjeta SD
    bool begin();

    // Retorna el lugar físico donde se encuentra el Solar Tracker
    String getLugarFisico();

    // Modifica el lugar físico donde se encuentra el Solar Tracker y lo guarda 
    // en la tarjeta SD 
    bool setLugarFisico(String lugarFisico);


    // Retorna los minutos de espera guardados en la tarjeta SD
    unsigned short getMinutosEspera();

    // Modifica los minutos de espera para guardar los datos en la tarjeta SD
    void setMinutosEspera(unsigned short minutosEspera);

    // Escribir datos en un archivo existente en la tarjeta SD
    bool writeDatos(DateTime fecha_hora, float amperaje, float voltaje, float potencia);



private:



    const unsigned short _chipSelectPin;  // Pin de selección de la tarjeta SD
    
    String _lugarFisico = "Salto"; // Lugar físico donde se encuentra el Solar Tracker
    unsigned short _minutosEspera = 5;  // Minutos de espera para guardar los datos en la tarjeta SD

    bool _estadoSD; // Estado de la tarjeta SD

    // Nombres de los ficheros
    const char _fichDatos[] = "datos.txt";  // nombre de fichero para guardar los datos del Solar Tracker
    const char _fichConfig[] = "config.txt" // nombre del fichero para guardar la configuración del Solar Tracker

    
    bool loadConfig(); // Carga la configuración del Solar Tracker desde la tarjeta SD

    bool updateConfigFile(); // Actualiza la configuración del Solar Tracker en la tarjeta SD

    String _getJSON (DateTime fecha_hora, float amperaje, float voltaje, float potencia);

    // Rtorna los datos de la tarjeta sd en formato JSON en el rango de fechas indicado
    DynamicJsonDocument getDataInRange(DateTime fecha_hora_inicio, DateTime fecha_hora_fin);    
};

#endif // SDCard_h
