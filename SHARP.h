#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

// any pins can be used
#define SHARP_SCK  9
#define SHARP_MOSI 8
#define SHARP_SS   3

extern int minorHalfSize; // 1/2 of lesser of display width or height

void setSHARP(void);

///

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h);

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h);

void drawPic(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h);

void NUM(uint8_t num);

void INFO(const char* str);