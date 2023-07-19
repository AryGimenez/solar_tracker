#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

// Definición de los pines de los servos
const int SERVO_VERTICAL_PIN = 7;
const int SERVO_HORIZONTAL_PIN = 6;

// Definición de los pines de las fotorresistencias
const int LDR_UP_PIN = A3;
const int LDR_DOWN_PIN = A2;
const int LDR_RIGHT_PIN = A1;
const int LDR_LEFT_PIN = A0;

// Definición de los pines de los botones
const int BTN_MODO_MANUAL_PIN = 4;
const int BTN_SOLO_MOTOR_HORIZONTAL_PIN = 3;
const int BTN_MODO_AUTOMATICO_PIN = 2;

// Definición de los pines de los LEDs indicadores
const int LED_MODO_MANUAL_PIN = 12;
const int LED_SOLO_MOTOR_HORIZONTAL_PIN = 11;
const int LED_AUTOMATICO_PIN = 10;

// Definición de los pines para el módulo de reloj Tiny RTC
const int RTC_SDA_PIN = 20;
const int RTC_SCL_PIN = 21;

// Definición de los pines para el sensor de corriente ACS712
const int ACS712_PIN = A4;

// Definición de los pines para el módulo microSD Card
const int SD_CS_PIN = 53;

// Definición de los pines para el módulo Bluetooth HM-05
const int BT_TX_PIN = 8;
const int BT_RX_PIN = 9;

// Rangos para calibrar los valores de las fotorresistencias
const int LDR_MIN = 0;
const int LDR_MAX = 1023;

// Valores límite para el movimiento de los servos
const int VERTICAL_MIN_ANGLE = 0;
const int VERTICAL_MAX_ANGLE = 180;
const int HORIZONTAL_MIN_ANGLE = 0;
const int HORIZONTAL_MAX_ANGLE = 180;

// Crear objetos de los servos
Servo servoVertical;
Servo servoHorizontal;

// Crear objeto para el módulo de reloj Tiny RTC
RTC_DS1307 rtc;

// Crear objeto para el sensor de corriente ACS712
Adafruit_ADS1115 ads;
const float ACS712_SENSITIVITY = 0.185; // Sensibilidad del sensor ACS712 en mV/A

// Crear objeto para la tarjeta microSD
File dataFile;

// Crear objeto para la comunicación Bluetooth
SoftwareSerial BTSerial(BT_TX_PIN, BT_RX_PIN);

// Variables para almacenar los modos de funcionamiento
bool modoManual = false;
bool modoSoloMotorHorizontal = false;
bool modoAutomatico = false;

// Variables para almacenar los datos
String mLugarFisico = "Lugar Fisico";
unsigned long mIntervaloSensado = 10; // Intervalo de sensado en minutos (por defecto 10 minutos)
unsigned long previousMillis = 0; // Variable para almacenar el tiempo anterior en milisegundos

void setup() {
  // Inicialización de los pines de los servos
  servoVertical.attach(SERVO_VERTICAL_PIN);
  servoHorizontal.attach(SERVO_HORIZONTAL_PIN);

  // Inicialización de los pines de los botones
  pinMode(BTN_MODO_MANUAL_PIN, INPUT_PULLUP);
  pinMode(BTN_SOLO_MOTOR_HORIZONTAL_PIN, INPUT_PULLUP);
  pinMode(BTN_MODO_AUTOMATICO_PIN, INPUT_PULLUP);

  // Inicialización de los pines de los LEDs indicadores
  pinMode(LED_MODO_MANUAL_PIN, OUTPUT);
  pinMode(LED_SOLO_MOTOR_HORIZONTAL_PIN, OUTPUT);
  pinMode(LED_AUTOMATICO_PIN, OUTPUT);

  // Inicialización del módulo de reloj Tiny RTC
  Wire.begin(RTC_SDA_PIN, RTC_SCL_PIN);
  rtc.begin();

  // Inicialización del sensor de corriente ACS712
  ads.begin();

  // Inicialización del módulo microSD Card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Error al inicializar la tarjeta microSD");
    while (1);
  }

  // Inicialización de la comunicación Bluetooth
  BTSerial.begin(9600);
}

void loop() {
  // Leer el estado de los botones
  bool modoManualPressed = digitalRead(BTN_MODO_MANUAL_PIN) == LOW;
  bool modoSoloMotorHorizontalPressed = digitalRead(BTN_SOLO_MOTOR_HORIZONTAL_PIN) == LOW;
  bool modoAutomaticoPressed = digitalRead(BTN_MODO_AUTOMATICO_PIN) == LOW;

  // Actualizar los modos de funcionamiento según los botones presionados
  if (modoManualPressed) {
    modoManual = true;
    modoSoloMotorHorizontal = false;
    modoAutomatico = false;
  } else if (modoSoloMotorHorizontalPressed) {
    modoManual = false;
    modoSoloMotorHorizontal = true;
    modoAutomatico = false;
  } else if (modoAutomaticoPressed) {
    modoManual = false;
    modoSoloMotorHorizontal = false;
    modoAutomatico = true;
  }

  // Actualizar los LEDs indicadores según los modos de funcionamiento
  digitalWrite(LED_MODO_MANUAL_PIN, modoManual);
  digitalWrite(LED_SOLO_MOTOR_HORIZONTAL_PIN, modoSoloMotorHorizontal);
  digitalWrite(LED_AUTOMATICO_PIN, modoAutomatico);

  // Verificar los modos de funcionamiento y realizar el seguimiento del sol correspondiente
  if (modoManual) {
    // Realizar el seguimiento manual con el Arduino Joystick
    // Aquí puedes agregar tu código para controlar los servos con el módulo Arduino Joystick
  } else if (modoSoloMotorHorizontal) {
    // Realizar el seguimiento automático en el eje horizontal
    int ldrLeftValue = analogRead(LDR_LEFT_PIN);
    int horizontalAngle = map(ldrLeftValue, LDR_MIN, LDR_MAX, HORIZONTAL_MIN_ANGLE, HORIZONTAL_MAX_ANGLE);
    servoVertical.write(VERTICAL_MIN_ANGLE);
    servoHorizontal.write(horizontalAngle);
  } else if (modoAutomatico) {
    // Realizar el seguimiento automático en ambos ejes
    int ldrUpValue = analogRead(LDR_UP_PIN);
    int ldrDownValue = analogRead(LDR_DOWN_PIN);
    int ldrRightValue = analogRead(LDR_RIGHT_PIN);
    int ldrLeftValue = analogRead(LDR_LEFT_PIN);

    int verticalAngle = map(ldrUpValue - ldrDownValue, -LDR_MAX, LDR_MAX, VERTICAL_MIN_ANGLE, VERTICAL_MAX_ANGLE);
    int horizontalAngle = map(ldrLeftValue - ldrRightValue, -LDR_MAX, LDR_MAX, HORIZONTAL_MIN_ANGLE, HORIZONTAL_MAX_ANGLE);

    servoVertical.write(verticalAngle);
    servoHorizontal.write(horizontalAngle);
  }

  // Obtener la fecha y hora actual del reloj Tiny RTC
  DateTime now = rtc.now();

  // Obtener los valores de voltaje, amperaje y potencia del sensor de corriente ACS712
  int16_t adcValue = ads.readADC_SingleEnded(ACS712_PIN);
  float voltage = adcValue * 0.1875; // Conversión del valor ADC a voltaje en mV
  float current = voltage / ACS712_SENSITIVITY;
  float power = voltage * current / 1000; // Potencia en Watts

  // Guardar los datos en la tarjeta microSD
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= mIntervaloSensado * 60000) {
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.print(mLugarFisico);
      dataFile.print(",");
      dataFile.print(now.timestamp());
      dataFile.print(",");
      dataFile.print(voltage);
      dataFile.print(",");
      dataFile.print(current);
      dataFile.print(",");
      dataFile.println(power);
      dataFile.close();
    } else {
      Serial.println("Error al abrir el archivo en la tarjeta microSD");
    }
    previousMillis = currentMillis;
  }

  // Leer los comandos enviados por la comunicación Bluetooth
  if (BTSerial.available()) {
    String command = BTSerial.readString();
    if (command.startsWith("intervalo:")) {
      // Cambiar el rango de mIntervaloSensado para cambiar el intervalo de tiempo de sensado
      mIntervaloSensado = command.substring(10).toInt();
    } else if (command.startsWith("fecha:")) {
      // Cambiar la fecha del reloj Tiny RTC
      String fecha = command.substring(6);
      int year = fecha.substring(0, 4).toInt();
      int month = fecha.substring(5, 7).toInt();
      int day = fecha.substring(8, 10).toInt();
      int hour = fecha.substring(11, 13).toInt();
      int minute = fecha.substring(14, 16).toInt();
      int second = fecha.substring(17, 19).toInt();
      DateTime newTime(year, month, day, hour, minute, second);
      rtc.adjust(newTime);
    } else if (command.startsWith("lugar:")) {
      // Cambiar el valor de mLugarFisico
      mLugarFisico = command.substring(6);
    }
  }
}
