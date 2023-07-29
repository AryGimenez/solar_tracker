#ifndef LedAdvertencia_h
#define LedAdvertencia_h

#include <Arduino.h>

class LedAdvertencia {
public:
    // Constructor de la clase que recibe el pin para el led de advertencia
    LedAdvertencia(int _ledAdvertenciaPIN);

    // Inicialización del led de advertencia
    void begin();

    // Enciende el led de advertencia
    void encender();

    // Apaga el led de advertencia
    void apagar();


private:
    const int _ledAdvertenciaPIN; // Pin para el led de advertencia
};