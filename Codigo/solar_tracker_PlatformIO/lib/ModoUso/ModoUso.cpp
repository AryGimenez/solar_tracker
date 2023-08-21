#include "ModoUso.h"

// Constructor de la clase ModoUso
ModoUso::ModoUso( 
    uint8_t btnModoManualPIN,               // PIN del botón para el modo manual
    uint8_t btnModoMotorHorizontal,          // PIN del botón para el modo solo motor horizontal
    uint8_t btnModoAutomatico,               // PIN del botón para el modo automático
    uint8_t ledModoManualPIN,                // PIN del LED que indica el modo manual
    uint8_t ledModoSoloMotorPIN,             // PIN del LED que indica el modo solo motor horizontal
    uint8_t ledModoAutomaticoPIN             // PIN del LED que indica el modo automático
) : 
    _btnModoManualPIN(btnModoManualPIN),            // Inicialización de la variable miembro para el PIN del botón de modo manual
    _btnModoMotorHorizontal(btnModoMotorHorizontal), // Inicialización de la variable miembro para el PIN del botón de modo solo motor horizontal
    _btnModoAutomatico(btnModoAutomatico),          // Inicialización de la variable miembro para el PIN del botón de modo automático
    _ledModoManualPIN(ledModoManualPIN),            // Inicialización de la variable miembro para el PIN del LED de modo manual
    _ledModoSoloMotorPIN(ledModoSoloMotorPIN),      // Inicialización de la variable miembro para el PIN del LED de modo solo motor horizontal
    _ledModoAutomaticoPIN(ledModoAutomaticoPIN)    // Inicialización de la variable miembro para el PIN del LED de modo automático
{}

// Método para inicializar los pines y los botones
void ModoUso::attach()
{
    // Inicializar los pines de los botones como entrada con resistencias pull-up internas
    pinMode(_btnModoManualPIN, INPUT_PULLUP);
    pinMode(_btnModoMotorHorizontal, INPUT_PULLUP);
    pinMode(_btnModoAutomatico, INPUT_PULLUP);

    // Inicializar los pines de los LEDs indicadores como salida
    pinMode(_ledModoManualPIN, OUTPUT);
    pinMode(_ledModoSoloMotorPIN, OUTPUT);
    pinMode(_ledModoAutomaticoPIN, OUTPUT);

    digitalWrite(_ledModoManualPIN, HIGH); // Enciende el LED de Modo Manual al iniciar
}

// Método para actualizar el estado de los LEDs según el modo de funcionamiento
void ModoUso::upgradeLEDs()
{

    // Comprueba el no se allá presionado un botón
    if (digitalRead(_btnModoManualPIN))
    {
        _modoFuncionamiento = 1; // Modo Manual
    }
    else if (digitalRead(_btnModoMotorHorizontal))
    {
        _modoFuncionamiento = 2; // Modo Motor Horizontal
    }
    else if (digitalRead(_btnModoAutomatico))
    {
        _modoFuncionamiento = 3; // Modo Automático
    }

    // Actualizar los LEDs indicadores según el modo de funcionamiento
    switch (_modoFuncionamiento)
    {
    case 1:                                       // Modo Manual
        digitalWrite(_ledModoManualPIN, HIGH);    // (💡)
        digitalWrite(_ledModoSoloMotorPIN, LOW);  // (❌)
        digitalWrite(_ledModoAutomaticoPIN, LOW); // (❌)
        break;
    case 2:                                       // Modo Motor Horizontal
        digitalWrite(_ledModoManualPIN, LOW);     // (❌)
        digitalWrite(_ledModoSoloMotorPIN, HIGH); // (💡)
        digitalWrite(_ledModoAutomaticoPIN, LOW); // (❌)
        break;
    case 3:                                        // Modo Automático
        digitalWrite(_ledModoManualPIN, LOW);      // (❌)
        digitalWrite(_ledModoSoloMotorPIN, LOW);   // (❌)
        digitalWrite(_ledModoAutomaticoPIN, HIGH); // (💡)
        break;
    }
}

// ... (otros métodos de la clase)

unsigned char ModoUso::getModoFuncionamiento()
{
    return _modoFuncionamiento;
}
