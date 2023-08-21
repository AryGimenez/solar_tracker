#ifndef ModoUso_h
#define ModoUso_h

#include <Arduino.h>

class ModoUso
{
public:
    ModoUso(uint8_t btnModoManualPIN,
            uint8_t btnModoMotorHorizontal,
            uint8_t btnModoAutomatico,
            uint8_t _ledModoManual,
            uint8_t _ledModoSoloMotor,
            uint8_t _ledModoAutomatico);

    // Inicializa los pines y los botones y de el led
    // de modo _ledModoManualPIN esta encendido
    void attach();

    void upgradeLEDs(); // Actualiza el estado de los led

    unsigned char getModoFuncionamiento(); // Getter para mModoFuncionamiento

private:
    // Variables Botón Indicador Modo
    const uint8_t _btnModoManualPIN;
    const uint8_t _btnModoMotorHorizontal;
    const uint8_t _btnModoAutomatico;

    // Variables Led Indicador Modo
    const uint8_t _ledModoManualPIN;
    const uint8_t _ledModoSoloMotorPIN;
    const uint8_t _ledModoAutomaticoPIN;

    // Variables para almacenar los modos de funcionamiento
    // 1 - Manual
    // 2 - Modo motor Horizontal
    // 3 - Modo Automático
    uint8_t _modoFuncionamiento = '3';
};

#endif
