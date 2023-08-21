#include <Arduino.h>          // Librería para el uso de la placa Arduino y sus funciones básicas.
#include <SDCard.h>
#include <ServoSolarTrak.h>
#include <SensorVAI.h>
#include <RelojRTC.h>
#include <PantallaOLED.h>
#include <ModoUso.h>
#include <BusI2C.h>
#include <LedAdvertencia.h>



SDCard _controladorSdCar(SD_CS_PIN);
bool _estadoSD = false;

BusI2C _busI2C(RTC_SDA_PIN, 
                RTC_SCL_PIN);

ServoSolarTrak _servoSolarTracker(SERVO_VERTICAL_PIN,
                                  SERVO_HORIZONTAL_PIN,
                                  LDR_UP_PIN,
                                  LDR_DOWN_PIN,
                                  LDR_RIGHT_PIN,
                                  LDR_LEFT_PIN,
                                  JOYSTICK_VERTICAL_PIN,
                                  JOYSTICK_HORISONTAL_PIN);

ModoUso _modoUso(BTN_MODO_MANUAL_PIN, 
                  BTN_SOLO_MOTOR_HORIZONTAL_PIN, 
                  BTN_MODO_AUTOMATICO_PIN,  
                  LED_MODO_MANUAL_PIN,
                  LED_SOLO_MOTOR_HORIZONTAL_PIN, 
                  LED_AUTOMATICO_PIN);

LedAdvertencia _ledAdvertencia(LED_ERROR_ESTADO_PIN);

SensorVAI _sensorVAI (SENSOR_CORRIENTE_PIN,
                      SENSOR_VOLTAJE_PIN);



RelojRTC _relojRTC ();

PantallaOLED _pantallaOLED();




void setup(){
  _busI2C.begin();
  _servoSolarTracker.begin();
  _estadoSD = _controladorSdCar.begin();
  

  

}
  

void loop(){

}
