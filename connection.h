#ifndef CONNECTION_LIB_H
#define CONNECTION_LIB_H

#include <Arduino.h>
#include "WiFiS3.h"
#include "IPAddress.h"
#include <ArduinoJson.h>
#include "config.h"

class Connection{
  public:
    void init();
    bool connected();
    short serverUpdate(short status);

  private:
    char ssid[20] = WIFI_SSID;
    char pass[20] = WIFI_PASS;
    WiFiSSLClient client;
};

#endif
