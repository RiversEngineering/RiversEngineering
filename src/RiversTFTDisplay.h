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


    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    XPT2046_Touchscreen touch = XPT2046_Touchscreen(TOUCH_CS, TOUCH_IRQ);

  public:
    Display();
    void begin();
    boolean touched();
    TouchPoint getTouchPoint();
    void clearScreen();
    void println(String s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE);
    void println(int s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE);
    void println(float s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE);
    void println(long s, int x = 0, int y = 0, uint16_t color = ILI9341_WHITE);
    void println(String s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255);
    void println(int s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255);
    void println(float s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255);
    void println(long s, int x = 0, int y = 0, int r = 255, int g = 255, int b = 255);
    void println(String s, int li = 0, int r = 255, int g = 255, int b = 255);
    void println(int s, int li = 0, int r = 255, int g = 255, int b = 255);
    void println(float s, int li = 0, int r = 255, int g = 255, int b = 255);
    void println(long s, int li = 0, int r = 255, int g = 255, int b = 255);
    boolean touchDraw(int r = 255, int g = 0, int b = 0, int pen = 3);
    boolean touchDraw(uint16_t color = ILI9341_RED, int pen = 3);
    void drawPixel(int x, int y, int r, int g, int b);
    void drawLine(int x0, int y0, int x1, int y1, int r, int g, int b);
    void drawRect(int x, int y, int w, int h, int r, int g, int b);
    void fillRect(int x, int y, int w, int h, int r, int g, int b);
    void drawRoundRect(int x, int y, int w, int h, int rad, int r, int g, int b);
    void fillRoundRect(int x, int y, int w, int h, int rad, int r, int g, int b);
    void drawCircle(int x, int y, int rad, int r, int g, int b);
    void fillCircle(int x, int y, int rad, int r, int g, int b);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b);
    void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int r, int g, int b);
    uint16_t color(int r, int g, int b);
    Adafruit_ILI9341 display();
    XPT2046_Touchscreen touchScreen();
};



#endif
