#include "PantallaOLED.h"

PantallaOLED::PantallaOLED() : _display(_ANCHO_PANTALLA, _ALTO_PANTALLA, &Wire, -1) {
}


void PantallaOLED::begin() {
    // Inicializamos la pantalla OLED 
    if (_display.begin(SSD1306_SWITCHCAPVCC, _DireccionPantalla)){
        _errorPantalla = false;
        _display.clearDisplay();
        _display.display();
    }else{
        _errorPantalla = true;
    }
    
}


void PantallaOLED::setVoltaje(float voltaje) {
    _voltaje = voltaje;
    _potencia = _voltaje * _amperaje;
}

void PantallaOLED::setAmperaje(float amperaje) {
    _amperaje = amperaje;
    _potencia = _voltaje * _amperaje;
}



void PantallaOLED::actualizarPantalla() {
    _display.clearDisplay();
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0, 0);

    _display.println("Voltaje: " + String(_voltaje) + " V");
    _display.println("Amperaje: " + String(_amperaje) + " A");
    _display.println("Potencia: " + String(_potencia) + " W");

    _display.display();
}
