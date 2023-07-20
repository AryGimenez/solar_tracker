#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

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
const int LED_SD_ESTADO_PIN = 13;

// Definición de los pines para el módulo de reloj Tiny RTC
const int RTC_SDA_PIN = 20;
const int RTC_SCL_PIN = 21;

// Definición de los pines para el sensor de corriente ACS712
const int ACS712_PIN = A4;

// Definición de los pines para el módulo microSD Card
const int SD_CS_PIN = 53;

// Definición del pin para el nivel de batería
const int NIVEL_BATERIA_PIN = A5;

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
SoftwareSerial BTSerial(8, 9); // RX, TX

// Crear objeto para el display OLED SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variables para almacenar los modos de funcionamiento
bool modoManual = false;
bool modoSoloMotorHorizontal = false;
bool modoAutomatico = false;

// Variables para almacenar los datos
String mLugarFisico = "Lugar Fisico";
unsigned long mIntervaloSensado = 10; // Intervalo de sensado en minutos (por defecto 10 minutos)
unsigned long previousMillis = 0; // Variable para almacenar el tiempo anterior en milisegundos
bool mEstadoSD = true; // Estado de la tarjeta SD (true = Funciona, false = No funciona)

// Variable para almacenar el nivel de batería
float mNivelBateria = 0.0;

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
  pinMode(LED_SD_ESTADO_PIN, OUTPUT);

  // Inicialización del módulo de reloj Tiny RTC
  Wire.begin(RTC_SDA_PIN, RTC_SCL_PIN);
  rtc.begin();

  // Inicialización del sensor de corriente ACS712
  ads.begin();

  // Inicialización del módulo microSD Card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Error al inicializar la tarjeta microSD");
    mEstadoSD = false;
  }

  // Inicialización de la comunicación Bluetooth
  BTSerial.begin(9600);

  // Inicialización del display OLED SSD1306
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error al iniciar el display OLED SSD1306");
  }

  // Limpiar el display
  display.clearDisplay();

  // Mostrar el mensaje de inicio en el display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Solar Tracker");
  display.display();
  delay(2000);

  // Leer el nivel de batería
  mNivelBateria = map(analogRead(NIVEL_BATERIA_PIN), 0, 1023, 0, 100);
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
  digitalWrite(LED_SD_ESTADO_PIN, mEstadoSD);

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
      StaticJsonDocument<200> jsonDocument;
      jsonDocument["lugar"] = mLugarFisico;
      jsonDocument["fecha_hora"] = now.timestamp();
      jsonDocument["voltaje"] = voltage;
      jsonDocument["amperaje"] = current;
      jsonDocument["potencia"] = power;
      String jsonData;
      serializeJson(jsonDocument, jsonData);
      dataFile.println(jsonData);
      dataFile.close();
    } else {
      Serial.println("Error al abrir el archivo en la tarjeta microSD");
      mEstadoSD = false;
    }
    previousMillis = currentMillis;
  }

  // Mostrar los datos en el display OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Lugar: ");
  display.println(mLugarFisico);
  display.print("Fecha: ");
  display.print(now.timestamp());
  display.println();
  display.print("Hora: ");
  display.print(now.timestamp());
  display.println();
  display.print("Voltaje: ");
  display.print(voltage);
  display.println(" mV");
  display.print("Amperaje: ");
  display.print(current);
  display.println(" A");
  display.print("Potencia: ");
  display.print(power);
  display.println(" W");
  display.print("Nivel Bateria: ");
  display.print(mNivelBateria);
  display.println(" %");
  if (!mEstadoSD) {
    display.println("ERROR SD");
  }
  display.display();

  // Enviar datos a la APK si se ha pasado el intervalo de envío
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
