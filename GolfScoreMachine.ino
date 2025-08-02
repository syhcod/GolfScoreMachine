#include <Arduino.h>            // Include the Arduino core library
#include "inter.h"              // Include the e-paper display GUI library
#include "testImage.h"
#include "BDtext.h"
#include "Score.h"
#include "SHARP.h"
#include "input.h"


// Define the size of the e-paper image buffer
uint8_t ImageBW[12480]; // E-paper image buffer

uint8_t stage = 0; // current stage of the machine. The stages are defined from line 16
uint8_t pending = 0;

char buffer = 0;
unsigned long before = 0;

// Stages;
#define STRANGER_ST 0
#define SCOREBOARD_ST 1
#define SAVE_ST 2
#define LOAD_ST 3

// Pending states:
#define SLIDER_P 0
#define OK_P 1
#define OKNO_P 2
#define SLIDERUPDOWN_P 3
#define NO_P 4
#define SLIDEROK_P 5
#define SLIDERUPDOWNOK_P 6

void stateMachine(char input) {
  switch (pending) {
  case SLIDER_P:
    if (input < 0) return;
    break;
  case OK_P:
    if (input != OK) return;
    break;
  case OKNO_P:
    if (input > NO) return;
    break;
  case SLIDERUPDOWN_P:
    if (input < UP) return;
    break;
  case NO_P:
    if (input != NO) return;
    break;
  case SLIDEROK_P:
    if (input < 0 && input != OK) return;
    break;
  case SLIDERUPDOWNOK_P:
    if (input == NO) return;
    break;
  default:
    return;
    break;
  }
  if (stage == STRANGER_ST) {
    if (input == OK) {
      stage = SCOREBOARD_ST;
      pending = SLIDERUPDOWN_P;
      initScore();
      setState(18, "Hole\nNo.");
      UI_Score();
      return;
    }
    if (input >= 0) {
      pending = SLIDEROK_P;
      setStrangers(input);
      return;
    }
  }
  else if (stage == SCOREBOARD_ST) {
    if (pending == SLIDER_P) {
      return;
    }
  }

}

// Clear the canvas and reinitialize the e-paper display
void clear_all() {
  Paint_NewImage(ImageBW, EPD_W, EPD_H, Rotation, WHITE); // Create a new image buffer
  Paint_Clear(WHITE); // Clear the canvas
  EPD_FastInit(); // Fast initialize the e-paper display
  EPD_Display_Clear(); // Clear the display content
  EPD_Update(); // Update the display
}

void UI_HK() {
  EPD_FastInit();  // Fast initialize the screen
  // EPD_ShowString(250,0,"ilbe.com",24,BLACK);  
  showPicture(0, 0, EPD_W, EPD_W, epd_bitmap_Hello_Kitty);  // Show the background image
  showPicture(240, 20, 176, 51, epd_bitmap_dtte);
  showPicture(240, 71, 176, 169, epd_bitmap_BD);
  EPD_Display(Paint.Image);  // Update the screen display
  EPD_Update();  // Refresh the screen
  EPD_DeepSleep();  // Enter deep sleep mode
}


void setup() {
  setSHARP();
  Serial.begin(115200);  // Start serial communication, set baud rate to 115200

  // Set the screen power pin and start the screen
  pinMode(7, OUTPUT);  // Set pin 7 to output mode
  digitalWrite(7, HIGH);  // Power the screen

  EPD_GPIOInit();  // Initialize the screen GPIO
  clear_all();
  UI_HK();  // Shows Hello Kitty screen while system boots
  delay(2000);
  clear_all();
  promptStranger();
  /*
  delay(700);
  initScore();
  UI_Score();
  goToRow(2);
  delay(700);
  goUp();
  delay(700);
  goUp();
  delay(700);
  goDown();
  delay(700);
  goToRow(5);
  delay(700);
  goUp();
  */
}

void loop() {
  // Input loop:
  if (whatKey() != IDLE) {
    setKey(IDLE);
    char key = whatKey();
    if (key < 0) {
      stateMachine(key);
      before = 0;
    }
    else {
      buffer = key;
      before = millis();
    }
  } else if (before != 0) {
    if (millis() - before > 700)
      stateMachine(buffer);
  }
}
