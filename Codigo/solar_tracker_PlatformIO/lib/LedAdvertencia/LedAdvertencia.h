#ifndef LedAdvertencia_h
#define LedAdvertencia_h

#include <Arduino.h>

class LedAdvertencia {
public:
    // Constructor de la clase que recibe el pin para el led de advertencia
    LedAdvertencia(uint8_t ledAdvertenciaPIN);

    // Inicialización del led de advertencia
    void begin();

    // Enciende el led de advertencia
    void encender();

    // Apaga el led de advertencia
    void apagar();


private:
    const uint8_t _ledAdvertenciaPIN; // Pin para el led de advertencia
};

#endif // LedAdvertencia_h
