#ifndef ModoUso_h
#define ModoUso_h

#include <Arduino.h>

class ModoUso
{
public:
    ModoUso(int btnModoManualPIN,
            int btnModoSoloMotor,
            int btnModoAutomatico,
            int _ledModoManual,
            int _ledModoSoloMotor,
            int _ledModoAutomatico);

    // Inicializa los pines y los botones y de el led
    // de modo _ledModoManualPIN esta encendido
    void attach();

    void upgradeLEDs(); // Actualiza el estado de los led

    unsigned char getModoFuncionamiento(); // Getter para mModoFuncionamiento

private:
    // Variables Botón Indicador Modo
    const int _btnModoManualPIN;
    const int _btnModoSoloMotor;
    const int _btnModoAutomatico;

    // Variables Led Indicador Modo
    const int _ledModoManualPIN;
    const int _ledModoSoloMotorPIN;
    const int _ledModoAutomaticoPIN;

    // Variables para almacenar los modos de funcionamiento
    // 1 - Manual
    // 2 - Modo motor Horizontal
    // 3 - Modo Automático
    unsigned char _modoFuncionamiento = '3';
};

#endif
