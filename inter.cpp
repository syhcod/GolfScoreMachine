#include "inter.h"
#include "EPD_font.h"

void showPicture(uint16_t x,uint16_t y,uint16_t sizex,uint16_t sizey,const uint8_t BMP[]) {
  EPD_ShowPicture(y, x, sizey, sizex, BMP, WHITE);
}

void drawRectFill(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color) {
  EPD_DrawRectangle(Ystart, Xstart, Yend, Xend, Color, 1);
}
void drawLine(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color) {
  EPD_DrawLine(Ystart,Xstart,Yend,Xend, Color);
}

void drawGrid(uint16_t rows, uint16_t cols, uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t Color) {
  uint16_t xr = (Xend - Xstart) / rows;
  uint16_t yr = (Yend - Ystart) / cols;
  for (uint16_t x = Xstart; x < Xend; x += xr) {
    drawLine(x, Ystart, x, Yend, Color);
  }
  for (uint16_t y = Ystart; y < Yend; y += yr) {
    drawLine(Xstart, y, Xend, y, Color);
  }
}

void finish() {
  EPD_Display(Paint.Image);  // Update the screen display
  EPD_Update();  // Refresh the screen
  EPD_DeepSleep();  // Enter deep sleep mode
}

void showChar(uint16_t x,uint16_t y,uint16_t chr,uint16_t size1, uint16_t color){
  uint16_t i,m,temp,size2,chr1;
  uint16_t x0,y0;
  y0 = x;
  x = y;
  y = y0;
  x0=x;
  if(size1==8)size2=6;
  else size2=(size1/8+((size1%8)?1:0))*(size1/2);  //得到字体一个字符对应点阵集所占的字节数
  chr1=chr-' ';  //计算偏移后的值
  for(i=0;i<size2;i++)
  {
    if(size1==8)
        {temp=ascii_0806[chr1][i];} //调用0806字体
    else if(size1==12)
        {temp=ascii_1206[chr1][i];} //调用1206字体
    else if(size1==16)
        {temp=ascii_1608[chr1][i];} //调用1608字体
    else if(size1==24)
        {temp=ascii_2412[chr1][i];} //调用2412字体
    else if(size1==48)
        {temp=ascii_4824[chr1][i];} //调用2412字体
    else return;
    for(m=0;m<8;m++)
    {
      if(temp&0x01)Paint_SetPixel(x,y,color);
      else Paint_SetPixel(x,y,!color);
      temp>>=1;
      x++;
    }
    y++;
    if((size1!=8)&&((y-y0)==size1/2))
    {y=y0;x0=x0+8;}
    x=x0;
  }
}

void showString(uint16_t x,uint16_t y,const char *chr,uint16_t size1,uint16_t color)
{
  while(*chr!='\0')//判断是不是非法字符!
  {
    showChar(x,y,*chr,size1,color);
    chr++;
    x+=size1/2;
  }
}

void drawCircle(uint16_t X_Center,uint16_t Y_Center,uint16_t Radius) {
  EPD_DrawCircle(Y_Center, X_Center, Radius, BLACK, 0);
  EPD_DrawCircle(Y_Center, X_Center, Radius - 1, WHITE, 1);
}

void drawCurvedRect(uint16_t x,uint16_t y,uint16_t xf,uint16_t yf,uint16_t radius) {
  drawCircle(x + radius, y + radius, radius);
  drawCircle(x + radius, y + radius, radius - 4);
  drawCircle(xf - radius, y + radius, radius);
  drawCircle(xf - radius, y + radius, radius - 4);
  drawCircle(x + radius, yf - radius, radius);
  drawCircle(x + radius, yf - radius, radius - 4);
  drawCircle(xf - radius, yf - radius, radius);
  drawCircle(xf - radius, yf - radius, radius - 4);
  drawRectFill(x, y+radius, xf, yf-radius, WHITE);
  drawRectFill(x+radius, y, xf-radius, yf, WHITE);

  drawLine(x+radius, y,xf-radius,y,BLACK);
  drawLine(x, y+radius, x, yf-radius, BLACK);
  drawLine(x+radius, yf,xf-radius,yf,BLACK);
  drawLine(xf, y+radius, xf, yf-radius, BLACK);

  drawLine(x+radius, y + 4,xf-radius,y + 4,BLACK);
  drawLine(x + 4, y+radius, x + 4, yf-radius, BLACK);
  drawLine(x+radius, yf - 4,xf-radius,yf - 4,BLACK);
  drawLine(xf - 4, y+radius, xf - 4, yf-radius, BLACK);
}