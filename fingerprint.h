#ifndef FINGERPRINT_LIB_H
#define FINGERPRINT_LIB_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include "config.h"

class Fingerprint{
  private:
    SoftwareSerial _fingerpadSerial;
    Adafruit_Fingerprint _finger = Adafruit_Fingerprint(&_fingerpadSerial);
    unsigned long lastRead = 0;
    bool _connected = false;
  
  public:
    Fingerprint();
    void init();
    int getFingerprint();
    bool isConnected();
};

#endif
