#include "input.h"
#include "BMK52T016.h"
#include <Arduino.h>
#include "SHARP.h"


TwoWire newWire(0);

BMK52T016*     BMK52 = nullptr;
volatile char t_key = 0;
volatile char state = -100;

volatile uint8_t max_num = 2;

char getKey() {
  if (BMK52->getINT() != 0) return (char)0;

  Serial.println(BMK52->readKeyValue(),DEC);
  unsigned short st = BMK52->readKeyValue();
  if (st < 9) return (char)st;
  switch (st) {
    case 2048:
      return DN;
      break;
    case 1024:
      return UP;
      break;
    case 512:
      return NO;
      break;
    case 256:
      return OK;
      break;
    default:
      return 0;
      break;
  }
  return 0;
}

void onkeyP() {
  char c = getKey();
  if (state == IDLE) state = 0;
  if (t_key == IDLE) {
    t_key = c;
    return;
  }
  state += c - t_key;
  t_key = c;
  if (state < 0) state = 0;
  if (state > max_num) state = max_num;
  NUM(state);
  delay(50);
}

char whatKey() {
  return state;
}

void setkey(char p) {
  t_key = IDLE;
  state = p;
}

void initT() {
  newWire.setPins(18, 16);

  BMK52 = new BMK52T016(14, &newWire);
  BMK52->begin(0x72);

  attachInterrupt(digitalPinToInterrupt(14), onkeyP, FALLING);
}

void setState(uint8_t max, const char* message) {
  max_num = max;
  INFO(message);
}