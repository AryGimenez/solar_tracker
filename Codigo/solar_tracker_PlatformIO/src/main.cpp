#include <Arduino.h>          // Librería estándar de Arduino.
#include <SDCard.h>
#include <ServoSolarTrak.h>
#include <SensorVAI.h>
#include <RelojRTC.h>
#include <PantallaOLED.h>
#include <ModoUso.h>
#include <BusI2C.h>
#include <LedAdvertencia.h>

// -------------- Inicialización de objetos y variables --------------

// Controlador de tarjeta SD con el pin correspondiente.
SDCard _controladorSdCar(SD_CS_PIN);
bool _estadoSD = false;  // Estado de la tarjeta SD (true si está funcionando, false si hay algún problema).

// Configuración del bus I2C con los pines SDA y SCL.
BusI2C _busI2C(RTC_SDA_PIN, RTC_SCL_PIN);

// Rastreador solar servo controlado. 
// Utiliza varios pines para detectar la posición del sol y para mover el servo.
ServoSolarTrak _servoSolarTracker(SERVO_VERTICAL_PIN,    // Pin para el servo que se mueve verticalmente
                                  SERVO_HORIZONTAL_PIN,  // Pin para el servo que se mueve horizontalmente
                                  LDR_UP_PIN,            // Sensor de luz (LDR) arriba
                                  LDR_DOWN_PIN,          // Sensor de luz (LDR) abajo
                                  LDR_RIGHT_PIN,         // Sensor de luz (LDR) derecha
                                  LDR_LEFT_PIN,          // Sensor de luz (LDR) izquierda
                                  JOYSTICK_VERTICAL_PIN, // Joystick para el movimiento vertical
                                  JOYSTICK_HORISONTAL_PIN); // Joystick para el movimiento horizontal

// Modos de uso y configuración de LEDs para indicar el modo actual.
ModoUso _modoUso(BTN_MODO_MANUAL_PIN,         // Botón para el modo manual
                  BTN_SOLO_MOTOR_HORIZONTAL_PIN, // Botón para activar solo el motor horizontal
                  BTN_MODO_AUTOMATICO_PIN,     // Botón para el modo automático
                  LED_MODO_MANUAL_PIN,         // LED indicador del modo manual
                  LED_SOLO_MOTOR_HORIZONTAL_PIN, // LED indicador del motor horizontal solo activo
                  LED_AUTOMATICO_PIN);         // LED indicador del modo automático

// LED para advertir sobre problemas o estados específicos del sistema.
LedAdvertencia _ledAdvertencia(LED_ERROR_ESTADO_PIN);

// Sensor de Voltaje y Amperaje con sus respectivos pines.
SensorVAI _sensorVAI(SENSOR_CORRIENTE_PIN,     // Pin para medir corriente
                     SENSOR_VOLTAJE_PIN);      // Pin para medir voltaje

// Reloj en tiempo real (RTC).
RelojRTC _relojRTC;
bool _estadoReloj = false;  // Estado del reloj (true si está funcionando, false si hay algún problema).

// Pantalla OLED para visualizar datos.
PantallaOLED _pantallaOLED;
bool _estadoPantalla = false;  // Estado de la pantalla (true si está funcionando, false si hay algún problema).

// Función para verificar el estado de los componentes y actualizar el LED de advertencia en consecuencia.
void updateLedAdvertenica() {
    if (!_estadoSD || !_estadoReloj || !_estadoPantalla) 
        _ledAdvertencia.encender(); // Si hay algún problema, enciende el LED de advertencia.
     else 
        _ledAdvertencia.apagar();   // Si todo está bien, apaga el LED de advertencia.
    
}


// -------------- Setup (Configuración inicial) --------------

void setup() {
    _busI2C.begin();                            // Inicializa el bus I2C
    _servoSolarTracker.begin();                 // Inicializa el rastreador solar
    _estadoSD = _controladorSdCar.begin();      // Inicializa el controlador de la tarjeta SD y actualiza el estado
    _modoUso.begin();                           // Establece los modos de uso disponibles
    _ledAdvertencia.begin();                    // Inicializa el LED de advertencia
    _estadoPantalla = _pantallaOLED.begin();    // Inicializa la pantalla OLED y actualiza el estado
    _estadoReloj = _relojRTC.begin();           // Inicializa el reloj y actualiza el estado
    _sensorVAI.begin();                         // Inicializa el sensor de Voltaje y Amperaje
  
    _relojRTC.setEsperaMinutos(_controladorSdCar.getMinutosEspera()); // Establece los minutos de espera para guardar datos en la tarjeta SD
    
    updateLedAdvertenica();     // Actualiza el LED de advertencia
}

void loop() {

    _servoSolarTracker.setModoUso(_modoUso.getModoFuncionamiento());    // Establece el modo de uso del rastreador solar
    _servoSolarTracker.upgradeServo();                                  // Actualiza los servos del rastreador solar
    _sensorVAI.update();                                                // Actualiza los valores de voltaje y amperaje
    _estadoReloj = _relojRTC.update();                                  // Actualiza el reloj
    if (_relojRTC.hanPasadoMinutos()) {                                 // Si han pasado los minutos establecidos, guarda los datos en la tarjeta SD
        _controladorSdCar.guardarDatos(_relojRTC.getFechaHora(), _sensorVAI.getAmperaje(), _sensorVAI.getVoltaje(), _sensorVAI.getPotencia());
        _relojRTC.resetPasadoMinutos();                                 // Reinicia el contador de minutos
    }
    _estadoPantalla = _pantallaOLED.update(_relojRTC.getFechaHora(), _sensorVAI.getAmperaje(), _sensorVAI.getVoltaje(), _sensorVAI.getPotencia()); // Actualiza la pantalla OLED

}