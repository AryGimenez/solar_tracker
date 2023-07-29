#include "LedAdvertencia.h"

// Constructor de la clase que recibe el pin para el led de advertencia
LedAdvertencia::LedAdvertencia(int ledAdvertenciaPIN) : _ledAdvertenciaPIN(ledAdvertenciaPIN) {}

// Inicialización del led de advertencia
void LedAdvertencia::begin() {
    pinMode(_ledAdvertenciaPIN, OUTPUT);
    apagar(); // Asegurarse de que el led inicie apagado al inicializar
}

// Enciende el led de advertencia
void LedAdvertencia::encender() {
    digitalWrite(_ledAdvertenciaPIN, HIGH);
}

// Apaga el led de advertencia
void LedAdvertencia::apagar() {
    digitalWrite(_ledAdvertenciaPIN, LOW);
}
