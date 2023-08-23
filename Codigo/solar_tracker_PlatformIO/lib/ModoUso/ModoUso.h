#ifndef ModoUso_h
#define ModoUso_h

#include <Arduino.h>

/**
 * @class ModoUso
 * @brief Gestiona los modos de funcionamiento del sistema y los correspondientes LEDs y botones indicadores.
 */
class ModoUso
{
public:
    /**
     * @brief Constructor para inicializar los pines de botones y LEDs.
     * @param btnModoManualPIN Pin del botón para el modo manual.
     * @param btnModoMotorHorizontal Pin del botón para el modo motor horizontal.
     * @param btnModoAutomatico Pin del botón para el modo automático.
     * @param ledModoManual Pin del LED indicador del modo manual.
     * @param ledModoSoloMotor Pin del LED indicador del modo solo motor.
     * @param ledModoAutomatico Pin del LED indicador del modo automático.
     */
    ModoUso(uint8_t btnModoManualPIN,
            uint8_t btnModoMotorHorizontal,
            uint8_t btnModoAutomatico,
            uint8_t ledModoManual,
            uint8_t ledModoSoloMotor,
            uint8_t ledModoAutomatico);

    /**
     * @brief Inicializa los pines, botones y LEDs. 
     * Una vez inicializado, el LED asociado con _ledModoManualPIN se enciende, 
     * indicando el modo manual activo.
     */
    void begin();

    /**
     * @brief Actualiza el estado de los LEDs basándose en el modo de funcionamiento actual.
     */
    void upgradeLEDs();

    /**
     * @brief Obtiene el modo de funcionamiento actual.
     * @return Retorna el modo de funcionamiento: '1' (Manual), '2' (Modo motor Horizontal) o '3' (Modo Automático).
     */
    uint8_t getModoFuncionamiento();

private:
    // Variables para botones que determinan el modo de funcionamiento.
    const uint8_t _btnModoManualPIN;
    const uint8_t _btnModoMotorHorizontal;
    const uint8_t _btnModoAutomatico;

    // Variables para LEDs que indican el modo de funcionamiento.
    const uint8_t _ledModoManualPIN;
    const uint8_t _ledModoSoloMotorPIN;
    const uint8_t _ledModoAutomaticoPIN;

    // Variable para almacenar el modo de funcionamiento actual.
    // '1' - Modo Manual
    // '2' - Modo motor Horizontal
    // '3' - Modo Automático
    uint8_t _modoFuncionamiento = '3';
};

#endif
