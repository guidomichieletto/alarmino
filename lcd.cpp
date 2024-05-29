#include "lcd.h"

LCD::LCD() : _lcd(LCD_ADDR, 20, 4){
  
}

void LCD::init() {
  _lcd.init();
  _lcd.backlight();
  _lcd.print("Inizializzazione...");
}

void LCD::update(short status, short authStep, short bufferSize){
  _lcd.clear();

  if(status == STATUS_DEACTIVATED){
    _lcd.print("Stato: DISINSERITO");
  }

  if(status == STATUS_ACTIVATED){
    _lcd.print("Stato: INSERITO");
  }

  if(status == STATUS_ACTIVATING){
    _lcd.print("Stato: INSERIMENTO");
  }

  if(status == STATUS_DELAY || status == STATUS_ALARM){
    _lcd.print("AUTENTICAZIONE");
    _lcd.setCursor(0, 1);
    
    if(authStep == AUTH_FINGERPRINT){
      _lcd.print("-> IMPRONTA");
      _lcd.setCursor(0, 2);
      _lcd.print("-  CHIAVE RFID");
      _lcd.setCursor(0, 3);
      _lcd.print("-  CODICE");
    }

    if(authStep == AUTH_RFID){
      _lcd.print("OK IMPRONTA");
      _lcd.setCursor(0, 2);
      _lcd.print("-> CHIAVE RFID");
      _lcd.setCursor(0, 3);
      _lcd.print("-  CODICE");
    }

    if(authStep == AUTH_KEYPAD){
      _lcd.print("OK IMPRONTA");
      _lcd.setCursor(0, 2);
      _lcd.print("OK CHIAVE RFID");
      _lcd.setCursor(0, 3);
      _lcd.print("-> CODICE [");
      for(int i = 0; i < bufferSize; i++){
        _lcd.print("*");
      }
      for(int i = 1; i < PASSWORD_LENGTH - bufferSize; i++){
        _lcd.print(" ");
      }
      _lcd.print("]");
    }
  }
}
