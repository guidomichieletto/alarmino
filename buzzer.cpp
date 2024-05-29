#include "buzzer.h"

void Buzzer::beep(unsigned int duration){
  _duration = duration;
}

void Buzzer::noBeep(){
  _duration = 0;
}

void Buzzer::tick(){
  if(_duration > 0){
    if(millis() - _lastBeep >= _duration){
      _status = !_status;
      _lastBeep = millis();
    }
  } else if(_duration == -1){
    _status = true;
  } else {
    _status = false;
  }
  
  if(_status) tone(BUZZER, 1200); else noTone(BUZZER);
}
