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




#define TFT_BLACK 0
#define TFT_NAVY 0x000F
#define TFT_DARKGREEN 0x03E0
#define TFT_DARKCYAN 0x03EF
#define TFT_MAROON 0x7800
#define TFT_PURPLE 0x780F
#define TFT_OLIVE 0x7BE0
#define TFT_LIGHTGREY 0xC618
#define TFT_DARKGREY 0x7BEF
#define TFT_BLUE 0x001F
#define TFT_GREEN 0x07E0
#define TFT_CYAN 0x07FF
#define TFT_RED 0xF800
#define TFT_MAGENTA 0xF81F
#define TFT_YELLOW 0xFFE0
#define TFT_WHITE 0xFFFF
#define TFT_ORANGE 0xFD20
#define TFT_GREENYELLOW 0xAFE5
#define TFT_PINK 0xFC18



class Display /*: public Print*/ {
  private:
    int TS_MINX = 350;
    int TS_MINY = 150;
    int TS_MAXX = 4000;
    int TS_MAXY = 3900;


    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    XPT2046_Touchscreen touch = XPT2046_Touchscreen(TOUCH_CS, TOUCH_IRQ);
    uint16_t textColor = ILI9341_WHITE;
    uint8_t textSize = 2;
    uint16_t drawColor = ILI9341_RED;


  public:
    Display();
    void begin();

    boolean touched();
    TouchPoint getTouchPoint();
    void clearScreen();
    void rotate(int r);

    void setTextSize(uint8_t size);
    void setTextColor(uint16_t color);
    void setTextColor(int r, int g, int b);
    void print(String s, int x = 0, int y = 0);
    void print(int s, int x = 0, int y = 0);
    void print(float s, int x = 0, int y = 0);
    void print(double s, int x = 0, int y = 0);
    void print(long s, int x = 0, int y = 0);

    void printToLine(String s, int li = 0);
    void printToLine(int s, int li = 0);
    void printToLine(float s, int li = 0);
    void printToLine(double s, int li = 0);
    void printToLine(long s, int li = 0);

    void setDrawColor(uint16_t color);
    void setDrawColor(int r, int g, int b);
    boolean touchDraw(int pen = 3);

    void drawPixel(int x, int y);
    void drawLine(int x0, int y0, int x1, int y1);
    void drawRect(int x, int y, int w, int h);
    void fillRect(int x, int y, int w, int h);
    void drawRoundRect(int x, int y, int w, int h, int rad);
    void fillRoundRect(int x, int y, int w, int h, int rad);
    void drawCircle(int x, int y, int rad);
    void fillCircle(int x, int y, int rad);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
    void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);

    void setBrightness(uint16_t bright);

    int width();
    int height();

    uint16_t color(int r, int g, int b);

    Adafruit_ILI9341 display();
    XPT2046_Touchscreen touchScreen();

    //virtual size_t write(uint8_t x);
};



#endif
