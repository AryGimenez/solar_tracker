#ifndef PantallaOLED_h
#define PantallaOLED_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



class PantallaOLED {
public:

    PantallaOLED();

    void begin();

    void setVoltaje(float voltaje);
    
    void setAmperaje(float amperaje);

    void actualizarPantalla();

private:

    Adafruit_SSD1306 _display;
    
    // Definir constantes
    const uint8_t _ANCHO_PANTALLA = 128; // ancho pantalla OLED
    const uint8_t _ALTO_PANTALLA = 64; // alto pantalla OLED
    //Direccion pantalla OLED 0x3C
    const uint8_t _DireccionPantalla = 0x3C;
        

    float _voltaje = 0;
    float _amperaje = 0;
    float _potencia = 0;

    bool _errorPantalla = false;
       

};

#endif // PantallaOLED_h
