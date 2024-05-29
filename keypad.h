#ifndef KEYPAD_LIB_H
#define KEYPAD_LIB_H

#include <Arduino.h>
#include <Adafruit_Keypad.h>
#include "config.h"

class Keypad{
  private:
  
    const byte ROWS = 4;
    const byte COLS = 3;
    
    char hexaKeys[4][3] = {
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'},
      {'*', '0', '#'}
    };
    
    byte rowPins[4] = {2, 3, 4, 5};
    byte colPins[3] = {6, 7, 8};

    void reset();
    Adafruit_Keypad _keypad = Adafruit_Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // Usare questa libreria per UNO R4!!
    char _keyBuffer[PASSWORD_LENGTH];
    int _bufferSize = 0;
    unsigned long lastPressed = 0;
  
  public:
    void init();
    bool keyPressed();
    short getBufferSize();
    int checkCode(char passwords[USERS][PASSWORD_LENGTH]);
};


#endif
