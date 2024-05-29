/**
 * ALARMINO PROJECT
 */

// LIBRARIES
#include "keypad.h"
#include "connection.h"
#include "fingerprint.h"
#include "lcd.h"
#include "rfid.h"
#include "buzzer.h"

Keypad keypad;
Connection connection;
Fingerprint finger;
LCD lcd;
Buzzer buzzer;
RFIDA rfid;

short status = STATUS_DEACTIVATED;
int userId = -1;
short authStep = AUTH_FINGERPRINT;

char passwords[USERS][PASSWORD_LENGTH] = {"", "5678", "2580"}; // Codici per keypad
String uids[USERS] = {"", "3937DB4B7", "5ADFFC3F46"}; // Identificativi delle chiavi RFID

short prevStatus = -1;
short prevBufferSize = -1;

// TIMERS
unsigned long lastServerUpdate = 0;
unsigned long lastStatusChange = 0;

void setup() {
  Serial.begin(115200);

  lcd.init();
  connection.init();
  finger.init();
  keypad.init();
  rfid.init();

  pinMode(PIR, INPUT);

  lcd.update(status, authStep, 0);

}

void loop() {
  buzz();
  
  if(millis() - lastServerUpdate >= 25000 && status != STATUS_ACTIVATING && status != STATUS_DELAY){
    connection.serverUpdate(status);
    lastServerUpdate = millis();
    prevStatus = status;
  }

  checkStatus();

  if(status == STATUS_DELAY || status == STATUS_ALARM) authenticate();
}

void checkStatus(){
  if(status == STATUS_ACTIVATED && digitalRead(PIR)){
    changeStatus(STATUS_DELAY);
    changeAuthStep(AUTH_FINGERPRINT);
  }

  if(status == STATUS_DEACTIVATED && keypad.keyPressed()) changeStatus(STATUS_ACTIVATING);
   
  if(status == STATUS_DELAY && millis() - lastStatusChange >= ALARM_DELAY){
    changeStatus(STATUS_ALARM);
    lastServerUpdate = 0; // Forzo aggiornamento istantaneo a server
  }
  
  if(status == STATUS_ACTIVATING && millis() - lastStatusChange >= ACTIVATION_DELAY) changeStatus(STATUS_ACTIVATED);
}

void authenticate(){
  if(authStep == AUTH_FINGERPRINT){
    if(!finger.isConnected()) changeAuthStep(AUTH_RFID);
    userId = finger.getFingerprint();
    if(userId != -1) changeAuthStep(AUTH_RFID);
  }

  if(authStep == AUTH_RFID){
    // Se mi viene già fornito un userId verifico la corrispondenza altrimenti lo ricavo dalla lista carte
    if(userId == -1){
      userId = rfid.getCard(uids);
    } else {
      if(rfid.getCard(uids) == userId) changeAuthStep(AUTH_KEYPAD);
    }
  }

  if(authStep == AUTH_KEYPAD){
    if(prevBufferSize != keypad.getBufferSize()){
      lcd.update(status, authStep, keypad.getBufferSize());
      prevBufferSize = keypad.getBufferSize();
    }
    if(keypad.checkCode(passwords) == userId) changeStatus(STATUS_DEACTIVATED);
  }
}

void buzz(){
  if(status == STATUS_ACTIVATING){
    buzzer.beep(1000);
  } else if(status == STATUS_DELAY){
    buzzer.beep(100);
  } else if(status == STATUS_ALARM){
    buzzer.beep(-1);
  } else {
    buzzer.noBeep();
  }

  buzzer.tick();
}

void changeAuthStep(short newStep){
  authStep = newStep;
  prevBufferSize = 0;
  lcd.update(status, authStep, 0);
}

void changeStatus(short newStatus){
  status = newStatus;
  lastStatusChange = millis();
  lcd.update(status, authStep, 0);

  if(newStatus != STATUS_ALARM) userId = -1;
}
