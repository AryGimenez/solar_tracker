#ifndef PantallaOLED_h
#define PantallaOLED_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class PantallaOLED {
public:
    PantallaOLED(int screenWidth, int screenHeight);
    void begin();
    void clearScreen();
    void displayText(int x, int y, const char* text);
    void drawRect(int x, int y, int width, int height, bool filled);
    void drawCircle(int x, int y, int radius, bool filled);
    void displayBitmap(const unsigned char* bitmap, int width, int height);

private:
    Adafruit_SSD1306 _display;
    int _screenWidth;
    int _screenHeight;
};

#endif // PantallaOLED_h
