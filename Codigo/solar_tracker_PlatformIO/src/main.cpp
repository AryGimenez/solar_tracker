#include <Arduino.h>          // Librería para el uso de la placa Arduino y sus funciones básicas.

#include <Wire.h>             // Librería para la comunicación I2C, utilizada para el módulo de reloj Tiny RTC y el display OLED.
#include <Adafruit_ADS1015.h> // Librería para el uso del ADC ADS1015, utilizado para el sensor de corriente ACS712.
#include <RTClib.h>           // Librería para el manejo del reloj de tiempo real (RTC).
#include <SD.h>               // Librería para el uso de la tarjeta microSD.
#include <SPI.h>              // Librería para la comunicación SPI, utilizada para la tarjeta microSD.
#include <SoftwareSerial.h>   // Librería para la comunicación serial de software, utilizada para el módulo Bluetooth HM-05.
#include <Adafruit_GFX.h>     // Librería para el control de pantallas OLED utilizando el controlador SSD1306.
#include <Adafruit_SSD1306.h> // Librería para el control de pantallas OLED utilizando el controlador SSD1306.
#include <ArduinoJson.h>      // Librería para el manejo de datos en formato JSON.




// Definición de los pines de los LEDs indicadores
const int LED_SD_ESTADO_PIN = LED_SD_ESTADO_PIN;

// Definición de los pines para el sensor de corriente ACS712
const int ACS712_PIN = ACS712_PIN;

// Definición de los pines para el módulo microSD Card
const int SD_CS_PIN = SD_CS_PIN;

// Definición del pin para el nivel de batería
const int NIVEL_BATERIA_PIN = NIVEL_BATERIA_PIN;



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



// Variables para almacenar los datos
String mLugarFisico = "Lugar Fisico";
int mIntervaloSensado = 10; // Intervalo de sensado en minutos (por defecto 10 minutos)
int previousMillis = 0;     // Variable para almacenar el tiempo anterior en milisegundos
bool mEstadoSD = true;                // Estado de la tarjeta SD (true = Funciona, false = No funciona)

// Variable para almacenar el nivel de batería
float mNivelBateria = 0.0;

void setup()
{



  // Inicialización del módulo de reloj Tiny RTC
  Wire.begin(RTC_SDA_PIN, RTC_SCL_PIN);
  rtc.begin();

  // Inicialización del sensor de corriente ACS712
  ads.begin();

  // Inicialización del módulo microSD Card
  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("Error al inicializar la tarjeta microSD");
    mEstadoSD = false;
  }

  // Inicialización de la comunicación Bluetooth
  BTSerial.begin(9600);

  // Inicialización del display OLED SSD1306
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
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

void loop()
{
 

  





  else if (modoSoloMotorHorizontal)
  {
    // Realizar el seguimiento automático en el eje horizontal
    int ldrLeftValue = analogRead(LDR_LEFT_PIN);
    int horizontalAngle = map(ldrLeftValue, LDR_MIN, LDR_MAX, HORIZONTAL_MIN_ANGLE, HORIZONTAL_MAX_ANGLE);
    servoVertical.write(VERTICAL_MIN_ANGLE);
    servoHorizontal.write(horizontalAngle);
  }
  else if (modoAutomatico)
  {
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
  if (currentMillis - previousMillis >= mIntervaloSensado * 60000)
  {
    dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile)
    {
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
    }
    else
    {
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
  if (!mEstadoSD)
  {
    display.println("ERROR SD");
  }
  display.display();

  // Enviar datos a la APK si se ha pasado el intervalo de envío
  if (BTSerial.available())
  {
    String command = BTSerial.readString();
    if (command.startsWith("intervalo:"))
    {
      // Cambiar el rango de mIntervaloSensado para cambiar el intervalo de tiempo de sensado
      mIntervaloSensado = command.substring(10).toInt();
    }
    else if (command.startsWith("fecha:"))
    {
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
    }
    else if (command.startsWith("lugar:"))
    {
      // Cambiar el valor de mLugarFisico
      mLugarFisico = command.substring(6);
    }
  }
}
