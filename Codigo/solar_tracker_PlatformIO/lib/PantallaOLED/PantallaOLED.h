#ifndef PantallaOLED_h
#define PantallaOLED_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * @class PantallaOLED
 * @brief Gestiona la visualización de datos en una pantalla OLED usando la librería Adafruit_SSD1306.
 */
class PantallaOLED {
public:

    /**
     * @brief Constructor predeterminado para inicializar la pantalla OLED.
     */
    PantallaOLED();

    /**
     * @brief Inicializa la pantalla OLED.
     * @return Retorna true si la pantalla se inicializó con éxito, de lo contrario, retorna false.
     */
    bool begin();

    /**
     * @brief Establece el valor de voltaje a mostrar en la pantalla.
     * @param voltaje Valor de voltaje.
     */
    void setVoltaje(float voltaje);
    
    /**
     * @brief Establece el valor de amperaje a mostrar en la pantalla.
     * @param amperaje Valor de amperaje.
     */
    void setAmperaje(float amperaje);

    /**
     * @brief Actualiza y muestra los valores de voltaje, amperaje y potencia en la pantalla OLED.
     */
    void actualizarPantalla();

    /**
     * @brief Obtiene el estado actual de la pantalla (encendido/apagado).
     * @return Retorna true si la pantalla está encendida, de lo contrario, retorna false.
     */
    bool getEstadoPantalla();
    

private:
    // Objeto para gestionar la pantalla OLED usando la librería Adafruit_SSD1306.
    Adafruit_SSD1306 _display;
    
    // Constantes para definir las dimensiones de la pantalla OLED.
    const uint8_t _ANCHO_PANTALLA = 128; // Ancho de la pantalla OLED.
    const uint8_t _ALTO_PANTALLA = 64;   // Alto de la pantalla OLED.

    // Dirección I2C de la pantalla OLED.
    const uint8_t _DireccionPantalla = 0x3C;
        
    // Variables para almacenar valores de voltaje, amperaje y potencia.
    float _voltaje = 0;
    float _amperaje = 0;
    float _potencia = 0;

    // Variable para almacenar el estado de la pantalla (encendido/apagado).
    bool _estadoPantalla = false;
};

#endif // PantallaOLED_h
