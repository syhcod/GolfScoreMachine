#include <Arduino.h>            // Include the Arduino core library
#include "inter.h"              // Include the e-paper display GUI library
#include "testImage.h"
#include "BDtext.h"
#include "score.h"
#include "SHARP.h"


// Define the size of the e-paper image buffer
uint8_t ImageBW[12480]; // E-paper image buffer


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
  /*
  UI_HK();  // Shows Hello Kitty screen while system boots
  delay(2000);
  clear_all();
  
  promptStranger();
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
  // put your main code here, to run repeatedly:
  if (whatKey() != 0)
}
