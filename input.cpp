#include "input.h"
#include "BMK52T016.h"
#include <Arduino.h>


TwoWire newWire(0);
BMK52T016*     BMK52 = nullptr;
volatile char t_key = 0;

char getKey() {
  if (BMK52->getINT() != 0) return (char)0;

  Serial.println(BMK52->readKeyValue(),DEC);
  unsigned short st = BMK52->readKeyValue();
  if (st < 9) return (char)st;
  switch (st) {
    case 2048:
      return -1;
      break;
    case 1024:
      return -2;
      break;
    case 512:
      return -3;
      break;
    case 256:
      return -4;
      break;
    default:
      return 0;
      break;
  }
  return 0;
}

void onkeyP() {
  t_key = getKey();
  delay(50);
}

char whatKey() {
  return t_key;
}

void setkey(char p) {
  t_key = p;
}

void initT() {
  newWire.setPins(18, 16);

  BMK52 = new BMK52T016(14, &newWire);
  BMK52->begin(0x72);

  attachInterrupt(digitalPinToInterrupt(14), onkeyP, FALLING);
}

unsigned char getStranger() {
  return 0;
}