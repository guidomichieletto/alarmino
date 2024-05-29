#include "keypad.h"

void Keypad::init(){
  _keypad.begin();
}

bool Keypad::keyPressed(){
  _keypad.tick();

  while(_keypad.available()){
    keypadEvent e = _keypad.read();
    Serial.print((char)e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED) return true;
  }

  return false;
}

int Keypad::checkCode(char passwords[USERS][PASSWORD_LENGTH]){
  _keypad.tick();

  

  while(_keypad.available()){
    keypadEvent e = _keypad.read();

    if(millis() - lastPressed <= 1000 || e.bit.EVENT != KEY_JUST_PRESSED) continue;

    _keyBuffer[_bufferSize] = e.bit.KEY;
    _bufferSize++;

    if(_bufferSize == PASSWORD_LENGTH - 1){
      _bufferSize = 0;
      for(int userId = 0; userId < USERS; userId++){
        if(!strcmp(_keyBuffer, passwords[userId])) return userId; // codice corretto
      }

      reset();
    }
  }

  return -1;
}

short Keypad::getBufferSize(){
  return _bufferSize;
}

void Keypad::reset(){
  _bufferSize = 0;
}
