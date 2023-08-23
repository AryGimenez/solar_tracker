#include "SDCard.h"

// public ---------------------------------------

// Constructor de la clase que recibe el pin de selección del chip para la tarjeta SD
SDCard::SDCard(uint8_t chipSelectPin) : _chipSelectPin(chipSelectPin) {}

// Inicialización de la tarjeta SD y el sistema de archivos
bool SDCard::begin() {
    if (SD.begin(_chipSelectPin)){
        _estadoSD = loadConfig(); // Cargar la configuración del Solar Tracker desde la tarjeta SD

    }else
        _estadoSD = false; // No se ha inicializado correctamente la tarjeta SD

    return _estadoSD; // Fallo en la inicializarían de la tarjeta SD
}

// Retorna el lugar físico donde se encuentra el Solar Tracker
String SDCard::getLugarFisico() {
    return _lugarFisico;
}

// Modifica el lugar físico donde se encuentra el Solar Tracker y lo guarda 
// en la tarjeta SD 
bool SDCard::setLugarFisico(String lugarFisico){
    _lugarFisico = lugarFisico;
    return updateConfigFile(_minutosEspera, lugarFisico);
}

// Retorna el tiempo de espera entre mediciones
uint8_t SDCard::getMinutosEspera() {
    return _minutosEspera;
}

bool SDCard::setMinutosEspera(uint8_t minutosEspera) {
    _minutosEspera = minutosEspera;
    return updateConfigFile(minutosEspera, _lugarFisico);
}

// Escribir datos en un archivo existente en la tarjeta SD
bool SDCard::guardarDatos(DateTime fecha_hora, float amperaje, float voltaje, float potencia){
    File file = SD.open(_fichDatos, FILE_WRITE); // Abrir el archivo en modo escritura
    if (file) {
        file.println(SDCard::_getJSON(fecha_hora, amperaje, voltaje, potencia)); // Escribir los datos en el archivo
        file.close(); // Cerrar el archivo
        return true; // Se han escrito los datos exitosamenteSDCard.
    } else {
        return false; // Fallo al abrir el archivo para escritura
    }
}

// private ---------------------------------------


bool SDCard::loadConfig () {
    // Abrir el archivo en modo lectura
    File file = SD.open(_fichConfig);

    if (file) {
        // Crear un objeto DynamicJsonDocument para almacenar los datos del JSON
        DynamicJsonDocument jsonDocument(256);

        // Leer el archivo y parsear el JSON
        DeserializationError error = deserializeJson(jsonDocument, file);

        // Verificar si se pudo parsear correctamente el JSON
        if (error) {
            Serial.println("Error al parsear JSON");
            _estadoSD = false; // No se ha inicializado correctamente la tarjeta SD
            return false; // Falló al parsear el JSON
        }

        // Obtener los datos del JSON
        _minutosEspera = jsonDocument["minutos_espera"].as<uint8_t>();
        _lugarFisico = jsonDocument["lugar_fisico"].as<String>();

        // Cerrar el archivo después de leerlo
        file.close();

        _estadoSD = true; // Se ha inicializado correctamente la tarjeta SD
        return true; // Operación exitosa
    } else {
        _estadoSD = false; // No se ha inicializado correctamente la tarjeta SD
        return false; // Falló al abrir el archivo para lectura
    }
}

bool SDCard::updateConfigFile(uint8_t minutosEspera, String lugarFisico) {
    // Abrir el archivo en modo escritura
    File file = SD.open (_fichConfig, FILE_WRITE);
    
    if (file) {
        // Crear un objeto DynamicJsonDocument para almacenar los datos del JSON
        DynamicJsonDocument jsonDocument(256);

        // Crear un objeto JsonObject y agregarlo al objeto jsonDocument
        JsonObject jsonObject = jsonDocument.to<JsonObject>();

        // Agregar los datos al objeto JSON utilizando claves y valores
        jsonObject["minutos_espera"] = minutosEspera; // Convertir la fecha y hora a un valor numérico (timestamp)
        jsonObject["lugar_fisico"] = lugarFisico;

        // Escribir el objeto JSON en el archivo
        if (serializeJson(jsonDocument, file) == 0) {
            file.close();
            return false; // Falló la escritura del JSON en el archivo
        }

        // Cerrar el archivo después de escribir en él
        file.close();
        
        return true; // Operación exitosa
    } else {
        return false; // Falló al abrir el archivo para escritura
    }
}

String SDCard::_getJSON(DateTime fecha_hora, float amperaje, float voltaje, float potencia) {
  // Creamos un objeto DynamicJsonDocument para almacenar los datos del JSON
  // El tamaño se ajusta automáticamente según los datos agregados
  DynamicJsonDocument jsonDocument(256);

  // Creamos un objeto JsonObject y lo agregamos al objeto jsonDocument
  JsonObject jsonObject = jsonDocument.to<JsonObject>();

  // Agregamos los datos al objeto JSON utilizando claves y valores
  jsonObject["fecha_hora"] = fecha_hora.timestamp(); // Convertimos la fecha y hora a un valor numérico (timestamp)
  jsonObject["lugar_fisico"] = _lugarFisico;
  jsonObject["amperaje"] = amperaje;
  jsonObject["voltaje"] = voltaje;
  jsonObject["potencia"] = potencia;

  // Creamos un buffer para almacenar el JSON
  char buffer[256];
  
  // Serializamos el objeto JSON en el buffer
  serializeJson(jsonDocument, buffer, sizeof(buffer));

  // Creamos un String a partir del buffer
  String jsonString(buffer);


  // Devolvemos el JSON como un String
  return jsonString;

}

DynamicJsonDocument SDCard::getDataInRange(DateTime fechadesde, DateTime fechahasta) {
    // Abrir el archivo Datos.txt
    File file = SD.open(_fichDatos);

    // Modificar la hora de las fechas para que sea 00:00:00
    DateTime fechadesde_00h = DateTime(fechadesde.year(), fechadesde.month(), fechadesde.day(), 0, 0, 0);
    DateTime fechahasta_23h = DateTime(fechahasta.year(), fechahasta.month(), fechahasta.day(), 23,59, 59);


    // Crear un objeto DynamicJsonDocument para almacenar los datos JSON
    DynamicJsonDocument jsonDocument(512);

    if (file) {
        // Moverse al final del archivo
        file.seek(file.size());

        while (file.position() > 0) {
            file.seek(file.position() - 1); // Retroceder en el archivo una posición

            char c = file.read(); // Leer un carácter del archivo

            // Agregar el carácter leído al principio de un String para reconstruir el contenido del archivo
            String jsonString = c + jsonDocument.as<String>();

            // Parsear el JSON para obtener los datos
            DeserializationError error = deserializeJson(jsonDocument, jsonString);

            // Verificar si se pudo parsear correctamente el JSON
            if (error) {
                Serial.println("Error al parsear JSON");
                return jsonDocument; // Devolver el JSON parcial en caso de error
            }

            // Obtener el valor de "fecha_hora" del JSON
            uint32_t fecha_hora = jsonDocument["fecha_hora"];

            // Convertir el valor numérico a un objeto DateTime
            DateTime fecha_hora_obj(fecha_hora);

            // Verificar si la fecha_hora se encuentra dentro del rango
            if (fecha_hora_obj >= fechadesde_00h && fecha_hora_obj <= fechahasta_23h) {
                // Agregar el objeto JSON completo al resultado final
                jsonDocument.add(jsonDocument.as<JsonObject>());

                // Limpiar el contenido del objeto para reutilizarlo en la próxima iteración
                jsonDocument.clear();
            }
        }
        file.close(); // Cerrar el archivo
    }

    return jsonDocument; // Devolver los datos en el rango de fechas
}

