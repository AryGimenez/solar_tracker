#include "PantallaOLED.h"

PantallaOLED::PantallaOLED(int screenWidth, int screenHeight)
    : _screenWidth(screenWidth), _screenHeight(screenHeight) {}

void PantallaOLED::begin() {
    _display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Dirección I2C de la pantalla OLED
    _display.clearDisplay();
    _display.display();
}

void PantallaOLED::clearScreen() {
    _display.clearDisplay();
}

void PantallaOLED::displayText(int x, int y, const char* text) {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(x, y);
    _display.print(text);
}

void PantallaOLED::drawRect(int x, int y, int width, int height, bool filled) {
    _display.drawRect(x, y, width, height, filled ? SSD1306_WHITE : SSD1306_BLACK);
}

void PantallaOLED::drawCircle(int x, int y, int radius, bool filled) {
    _display.drawCircle(x, y, radius, filled ? SSD1306_WHITE : SSD1306_BLACK);
}

void PantallaOLED::displayBitmap(const unsigned char* bitmap, int width, int height) {
    _display.drawBitmap(0, 0, bitmap, width, height, SSD1306_WHITE);
    _display.display();
}
