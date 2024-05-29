#ifndef LCD_LIB_H
#define LCD_LIB_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "config.h"

class LCD{
  private:
    LiquidCrystal_I2C _lcd;
  
  public:
    LCD();
    void init();
    void update(short status, short authStep, short bufferSize);
};

#endif
