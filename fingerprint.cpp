#include "fingerprint.h"

Fingerprint::Fingerprint() : _fingerpadSerial(16, 17){
 
}

void Fingerprint::init(){
  _fingerpadSerial.begin(57600);
  _finger.begin(57600);
  delay(1000);

  if (!_finger.verifyPassword()) {
    Serial.println("Lettore impronte non trovato! Durante l'autenticazione verrà saltata l'identificazione dell'impronta");
    return;
  }

  _connected = true;
}

bool Fingerprint::isConnected(){
  return _connected;
}

int Fingerprint::getFingerprint(){
  if(millis() - lastRead <= 1000) return -1; // Se l'ultima lettura effettuata è ravvicinata esco in modo da non sovraccaricare
  
  lastRead = millis();
  if(_finger.getImage() != FINGERPRINT_OK) return -1;
  if(_finger.image2Tz() != FINGERPRINT_OK) return -1;
  Serial.println("Impronta rilevata!");
  if(_finger.fingerSearch() != FINGERPRINT_OK) return -1;

  Serial.print("Found ID #"); Serial.print(_finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(_finger.confidence);
  
  return _finger.fingerID;
}
