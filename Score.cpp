#include "Score.h"
#include "input.h"

uint8_t strangers = 2;
uint8_t state = 1;
uint8_t to9[4][9];
uint8_t to18[4][9];
uint8_t cursor[2];

void initScore() {
  cursor[0] = 0;
  cursor[1] = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 9; j++) {
      to9[i][j] = (i + j) * 4;
      to18[i][j] = 10+i;
    }
  }
}

void promptStranger() {
  EPD_FastInit();  // Fast initialize the screen
  drawCurvedRect(100, 40, 316, 200, 20);
  showString(112, 54, "No. of Players", 24, BLACK);
  showString(112, 120, "Input:", 24, BLACK);
  finish();
  strangers = getStranger();
  if (strangers > 2) strangers = 0;
  delay(1500);
  EPD_FastInit();
  showChar(208, 120, strangers + '2', 24, BLACK);
  finish();
}

void UI_Score() {
  EPD_FastInit();  // Fast initialize the screen
  Paint_Clear(WHITE); // Clear the canvas
  // showPicture(0, 0, EPD_W, EPD_W, epd_bitmap_Hello_Kitty);  // Show the background image
  showPicture(3, 80, 112, 40, epd_bitmap_mom);
  showPicture(0, 120, 112, 40, epd_bitmap_dad);
  // showPicture(240, 80, 176, 51, epd_bitmap_dtte);
  drawRectFill(0,0,416,80,BLACK);
  drawGrid(9, 2, 112, 0, 418, 80, WHITE);
  drawGrid(9, 4, 112, 81, 418, 238, BLACK);
  drawGrid(1, 2, 0, 0, 112, 80, WHITE);
  drawGrid(1, 4, 0, 81, 112, 240, BLACK);

  showString(5,10,"Hole",24,WHITE);
  showString(5,50,"Par",24,WHITE);
  for (uint8_t i = 0; i < 9; i++) {
    showChar(124 + 34 * (uint16_t)i,10,i+'1',24, WHITE);
    showChar(124 + 34 * (uint16_t)i,50,'3',24, WHITE);
  }

  showScore();
  finish();
}

void showScore() {
  char k = '\0';
  for (uint8_t i = 0; i < 9; i++) {
    for (uint8_t j = 0; j < strangers + 2; j++) {
      switch(state) {
      case 1:
        k = to9[j][i];
        break;
      case 2:
        k = to18[j][i];
        break;
      default:
        k = to9[j][i];
        break;
      }
      if (k != 0) {
        if (k > 9) {
          showChar(131 + 34 * (uint16_t)i,90 + 40 * j,k % 10 + '0',24, BLACK);
          showChar(131 + 34 * (uint16_t)i - 12,90 + 40 * j,k / 10 + '0',24, BLACK);
        } else {
          showChar(124 + 34 * (uint16_t)i,90 + 40 * j,k + '0',24, BLACK);
        }
      }
    }
  }
}

void setCur(bool isWhite) {
  char k = '\0';
  uint16_t color = isWhite ? WHITE : BLACK;
  uint8_t i = cursor[0];
  uint8_t j = cursor[1];
  switch(state) {
  case 1:
    k = to9[j][i];
    break;
  case 2:
    k = to18[j][i];
    break;
  default:
    k = to9[j][i];
    break;
  }
  if (k != 0 || isWhite) {
    if (k > 9) {
      showChar(131 + 34 * (uint16_t)i,90 + 40 * j,k % 10 + '0',24, color);
      showChar(131 + 34 * (uint16_t)i - 12,90 + 40 * j,k / 10 + '0',24, color);
    } else {
      showChar(124 + 34 * (uint16_t)i,90 + 40 * j,k + '0',24, color);
    }
  }
}


void setState(uint8_t st) {
  if (st != 1 && st != 2) return;
  if (st == state) return;
  state = st;
  for (uint8_t i = 0; i < 9; i++) {
    uint8_t k = i + 10;
    showChar(131 + 34 * (uint16_t)i,10,k % 10 + '0',24, WHITE);
    showChar(119 + 34 * (uint16_t)i,10,k / 10 + '0',24, WHITE);
    showChar(124 + 34 * (uint16_t)i,50,'3',24, WHITE);
  }
}

void goToRow(uint8_t row) {
  EPD_FastInit();  // Fast initialize the screen
  setCur(false);
  if (row > 8) setState(2);
  else setState(1);
  cursor[0] = row;
  setCur(true);
  finish();
}

void goUp() {
  EPD_FastInit();  // Fast initialize the screen
  setCur(false);
  if (cursor[1] == 0) cursor[1] = strangers + 1;
  else cursor[1]--;
  setCur(true);
  finish();
}

void goDown() {
  EPD_FastInit();  // Fast initialize the screen
  setCur(false);
  if (cursor[1] == strangers + 1) cursor[1] = 0;
  else cursor[1]++;
  setCur(true);
  finish();
}