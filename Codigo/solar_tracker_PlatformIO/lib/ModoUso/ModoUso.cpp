#include "ModoUso.h"

// Constructor de la clase ModoUso
ModoUso::ModoUso(int btnModoManualPIN,
                 int btnModoSoloMotor,
                 int btnModoAutomatico,
                 int ledModoManualPIN,
                 int ledModoSoloMotorPIN,
                 int ledModoAutomaticoPIN) : _btnModoManualPIN(btnModoManualPIN),
                                             _btnModoSoloMotor(btnModoSoloMotor),
                                             _btnModoAutomatico(btnModoAutomatico),
                                             _ledModoManualPIN(ledModoManualPIN),
                                             _ledModoSoloMotorPIN(ledModoSoloMotorPIN),
                                             _ledModoAutomaticoPIN(ledModoAutomaticoPIN)
{
    // Constructor vacío
}

// Método para inicializar los pines y los botones
void ModoUso::attach()
{
    // Inicializar los pines de los botones como entrada con resistencias pull-up internas
    pinMode(_btnModoManualPIN, INPUT_PULLUP);
    pinMode(_btnModoSoloMotor, INPUT_PULLUP);
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
    else if (digitalRead(_btnModoSoloMotor))
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
