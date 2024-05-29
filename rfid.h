#ifndef RFID_LIB_H
#define RFID_LIB_H

#include <Arduino.h>
#include <SPI.h>
#include <RFID.h>
#include "config.h"

class RFIDA{
  private:
    RFID _rc522;
  
  public:
    RFIDA();
    void init();
    int getCard(String uids[USERS]);
};

#endif
