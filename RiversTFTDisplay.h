#ifndef RIVERS_TFT_DISPLAY_H
#define RIVERS_TFT_DISPLAY_H

#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>


#ifndef TOUCH_CS
#define TOUCH_CS 8
#endif

#ifndef TOUCH_IRQ
#define TOUCH_IRQ 2
#endif


#ifndef TFT_CS
#define TFT_CS 10
#endif

#ifndef TFT_DC
#define TFT_DC 9
#endif


#define TouchPoint TS_Point




#define TFT_BLACK 0, 0, 0
#define TFT_NAVY 0, 0, 123
#define TFT_DARKGREEN 0, 125, 0
#define TFT_DARKCYAN 0, 125, 123
#define TFT_MAROON 123, 0, 0
#define TFT_PURPLE 123, 0, 123
#define TFT_OLIVE 123, 125, 0
#define TFT_LIGHTGREY 198, 195, 198
#define TFT_DARKGREY 123, 125, 123
#define TFT_BLUE 0, 0, 255
#define TFT_GREEN 0, 255, 0
#define TFT_CYAN 0, 255, 255
#define TFT_RED 255, 0, 0
#define TFT_MAGENTA 255, 0, 255
#define TFT_YELLOW 255, 255, 0
#define TFT_WHITE 255, 255, 255
#define TFT_ORANGE 255, 165, 0
#define TFT_GREENYELLOW 173, 255, 41
#define TFT_PINK 255, 130, 198



class Display {
  private:
    int TS_MINX = 350;
    int TS_MINY = 150;
    int TS_MAXX = 4000;
    int TS_MAXY = 3900;
    int textSize = 2;


  public:
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    XPT2046_Touchscreen touch = XPT2046_Touchscreen(TOUCH_CS, TOUCH_IRQ);

    Display() {
    }


    void begin() {
      tft.begin();
      tft.setRotation(3);
      touch.begin();
      touch.setRotation(1);
      analogWrite(A0, 128);
    }

    boolean touched() {
      return touch.touched();
    }

    TouchPoint getTouchPoint() {
      return touch.getPoint();
    }

    void clearScreen() {

      tft.fillScreen(ILI9341_BLACK);
    }

    void println(String s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE) {
      tft.setCursor(x, y);
      tft.setTextColor(color);
      tft.setTextSize(textSize);
      tft.println(s);
    }
    void println(int s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE) {
      tft.setCursor(x, y);
      tft.setTextColor(color);
      tft.setTextSize(textSize);
      tft.println(s);
    }
    void println(float s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE) {
      tft.setCursor(x, y);
      tft.setTextColor(color);
      tft.setTextSize(textSize);
      tft.println(s);
    }
    void println(long s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE) {
      tft.setCursor(x, y);
      tft.setTextColor(color);
      tft.setTextSize(textSize);
      tft.println(s);
    }

    void println(String s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, x, y, this->color(r, g, b));
    }
    void println(int s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, x, y, this->color(r, g, b));
    }
    void println(float s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, x, y, this->color(r, g, b));
    }
    void println(long s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, x, y, this->color(r, g, b));
    }

    void println(String s, int li = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, 0, li * textSize * 8, this->color(r, g, b));
    }
    void println(int s, int li = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, 0, li * textSize * 8, this->color(r, g, b));
    }
    void println(float s, int li = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, 0, li * textSize * 8, this->color(r, g, b));
    }
    void println(long s, int li = 0, int r = 255, int g = 255, int b = 255) {
      this->println(s, 0, li * textSize * 8, this->color(r, g, b));
    }


    boolean touchDraw(int r = 255, int g = 0, int b = 0, int pen = 3) {
      return this->touchDraw(this->color(r, g, b));
    }
    boolean touchDraw(uint16_t color = ILI9341_RED, int pen = 3) {
      if (touch.touched()) {
        TouchPoint p = this->getTouchPoint();
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

        tft.fillCircle(p.x, p.y, pen, color);
        return true;
      }
      return false;
    }


    void drawPixel(int x, int y, int r, int g, int b) {
      tft.writePixel(x, y, this->color(r, g, b));
    }

    void drawLine(int x0, int y0, int x1, int y1, int r, int g, int b) {
      tft.drawLine(x0, y0, x1, y1, this->color(r, g, b));
    }


    void drawRect(int x, int y, int w, int h, int r, int g, int b) {
      tft.drawRect(x, y, w, h, this->color(r, g, b));
    }
    void fillRect(int x, int y, int w, int h, int r, int g, int b) {
      tft.fillRect(x, y, w, h, this->color(r, g, b));
    }
    void drawRoundRect(int x, int y, int w, int h, int rad, int r, int g, int b) {
       tft.drawRoundRect(x, y, w, h, rad, this->color(r, g, b));
    }
    void fillRoundRect(int x, int y, int w, int h, int rad, int r, int g, int b) {
      tft.fillRoundRect(x, y, w, h, rad, this->color(r, g, b));
    }

    void drawCircle(int x, int y, int rad, int r, int g, int b) {
      tft.drawCircle(x, y, rad, this->color(r, g, b));
    }
    void fillCircle(int x, int y, int rad, int r, int g, int b) {
      tft.fillCircle(x, y, rad, this->color(r, g, b));
    }

    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b) {
      tft.drawTriangle(x0, y0, x1, y1, x2, y2, this->color(r, g, b));
    }
    void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b) {
      tft.fillTriangle(x0, y0, x1, y1, x2, y2, this->color(r, g, b));
    }



    uint16_t color(int r, int g, int b) {
      return (uint8_t)map(r, 0, 255, 0, 31) << 11
             | (uint8_t)map(g, 0, 255, 0, 63) << 5
             | (uint8_t)map(b, 0, 255, 0, 31);
    }
};



#endif
