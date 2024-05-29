#include "rfid.h"

RFIDA::RFIDA() : _rc522(RFID_SS, RFID_RST){
  
}

void RFIDA::init(){
  SPI.begin();
  _rc522.init();
}

int RFIDA::getCard(String uids[USERS]){
  if (_rc522.isCard()) {
    String uid = "";
    _rc522.readCardSerial();
    
    for(byte i = 0; i <= 4; i++){
      uid += String(_rc522.serNum[i], HEX);
      uid.toUpperCase();
    }

    Serial.println(uid);

    for(int i = 0; i < USERS; i++){
      if(uids[i].equals(uid)){
        Serial.println(i);
        return i;
      }
    }
  }

  return -1;
}
