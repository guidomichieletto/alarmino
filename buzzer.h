#ifndef BUZZER_LIB_H
#define BUZZER_LIB_H

#include <Arduino.h>
#include "config.h"

class Buzzer{
  public:
    void beep(unsigned int duration);
    void noBeep();
    void tick();

  private:
    bool _status = false;
    unsigned int _duration;
    unsigned long _lastBeep;
};

#endif
