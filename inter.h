#include "EPD_GUI.h"

void showPicture(uint16_t x,uint16_t y,uint16_t sizex,uint16_t sizey,const uint8_t BMP[]);
void drawRectFill(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color);
void drawLine(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color);
void drawGrid(uint16_t rows, uint16_t cols, uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color);
void finish();

//sizes come in 8, 12, 16, 24, 48
void showChar(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1, uint16_t color);
//sizes come in 8, 12, 16, 24, 48
void showWhiteChar(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1);

void drawCircle(uint16_t X_Center,uint16_t Y_Center,uint16_t Radius);
void drawCurvedRect(uint16_t x,uint16_t y,uint16_t xf,uint16_t yf,uint16_t radius);
void showString(uint16_t x,uint16_t y,const char *chr,uint16_t size1,uint16_t color);