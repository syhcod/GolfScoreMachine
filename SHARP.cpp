#include <Adafruit_SharpMem.h>

#include "SHARP.h"
#include "EPD_font.h"
#include "Score.h"
#include "BIGNUM.h"

int minorHalfSize;

const int16_t BLK = 0;
const int16_t WHT = 1;

const int16_t SHARP_H = 168;
const int16_t SHARP_W = 144;

uint8_t curNum = 0;

Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 144, 168);
// The currently-available SHARP Memory Display (144x168 pixels)
// requires > 4K of microcontroller RAM; it WILL NOT WORK on Arduino Uno
// or other <4K "classic" devices!  The original display (96x96 pixels)
// does work there, but is no longer produced.

void setSHARP(void)
{
  // start & clear the display
  display.begin();
  display.clearDisplay();

  // Several shapes are drawn centered on the screen.  Calculate 1/2 of
  // lesser of display width or height, this is used repeatedly later.
  minorHalfSize = min(display.width(), display.height()) / 2;

  // draw a single pixel
  display.drawPixel(10, 10, BLK);
  display.refresh();
  delay(500);
  display.clearDisplay();

  drawPic(0,0,epd_bitmap_mom, 112, 40);
  display.refresh();
  delay(500);
  // display.clearDisplay();

  NUM(0);
  delay(5000);
  INFO("FUCK!\nJOTT!");
  for (int i = 0; i < 19; i++) {
    NUM(i);
    delay(1000);
  }
}

///

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  display.drawLine(x0, y0, x1, y1, BLK);
}

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h) {
  display.drawRect(x, y, w, h, BLK);
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h) {
  display.fillRect(x, y, w, h, BLK);
}

void rmRect(int16_t x, int16_t y, int16_t w, int16_t h) {
  display.fillRect(x, y, w, h, WHT);
}

void drawPic(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h) {
  display.drawBitmap(x, y, bitmap, w, h, BLK);
}

void drawNUM(uint8_t n, int16_t x, int16_t y) {
  if (n == 0 || n == curNum) return;
  curNum = n;
  switch (n) {
  case 0:
    drawPic(x,y, ZERO, 40, 93);
    break;
  case 1:
    drawPic(x,y, ONE, 40, 93);
    break;
  case 2:
    drawPic(x,y, TWO, 40, 93);
    break;
  case 3:
    drawPic(x,y, THREE, 40, 93);
    break;
  case 4:
    drawPic(x,y, FOUR, 40, 93);
    break;
  case 5:
    drawPic(x,y, FIVE, 40, 93);
    break;
  case 6:
    drawPic(x,y, SIX, 40, 93);
    break;
  case 7:
    drawPic(x,y, SEVEN, 40, 93);
    break;
  case 8:
    drawPic(x,y, EIGHT, 40, 93);
    break;
  case 9:
    drawPic(x,y, NINE, 40, 93);
    break;
  case -4:
    drawPic(x,y, OKAY, 92, 92);
    break;
  case -3:
    drawPic(x,y, NONE, 92, 92);
    break;
  case -2:
    drawPic(x,y, UPUP, 92, 92);
    break;
  case -1:
    drawPic(x,y, DOWN, 92, 92);
    break;
  default:
    break;
  }
}

void NUM_Refresh() {
  rmRect(0,76,144,93);
}

void INF_Refresh() {
  rmRect(0,0,144,92);
}

void NUM(uint8_t num) {
  if (num > 99) return;
  NUM_Refresh();
  if (num > 9) {
    uint8_t num1 = num / 10;
    uint8_t num2 = num % 10;
    drawNUM(num1, 36, 76);
    drawNUM(num2, 73, 76);
  } else if (num >= 0) {
    drawNUM(num, 54,76);
  } else {
    drawNUM(num, 26, 76);
  }
  display.refresh();
}

void INFO(const char* str) {
  INF_Refresh();
  display.setTextSize(4);
  display.setTextColor(BLK);
  display.setCursor(2,2);
  display.cp437(true);

  while (*str != '\0') {
    uint8_t i = *str;\
    display.write(i);
    str++;
  }
  display.refresh();
}