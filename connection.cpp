#include "connection.h"

void Connection::init(){
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
    
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  for (int i = 1; i < 4 && !connected(); i++) {
    Serial.print("Tentativo ");
    Serial.print(i);
    Serial.println(" di connessione WiFi");
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network.
    WiFi.begin(ssid, pass);
    
    // wait 10 seconds for connection:
    delay(10000);
  }

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

bool Connection::connected(){
  if(WiFi.status() == WL_CONNECTED) return true;
  return false;
}

bool Connection::serverUpdate(short status){
  if(!connected()) return false;

  bool connection = false;
  for(int i = 0; i < 3 && !connection; i++){
    Serial.print("Tentativo connessione n.");
    Serial.println(i);
    connection = client.connect(SERVER, 443);
  }

  if (connection) {
    Serial.println("Connesso, invio messaggio");
    
    client.print("GET /alarm/update-endpoint.php?status=");
    if(status == STATUS_DEACTIVATED || status == STATUS_ACTIVATING) client.print("deactivated");
    if(status == STATUS_ACTIVATED || status == STATUS_DELAY) client.print("activated");
    if(status == STATUS_ALARM) client.print("alarm");
    client.print("&token=");
    client.print(TOKEN);
    client.println(" HTTP/1.1");
    
    client.print("Host: ");
    client.println(SERVER);
    
    client.println("Connection: close");
    client.println();
    
    uint32_t received_data_num = 0;
    unsigned long waitStart = millis();
    while (!client.available() && millis() - waitStart < 1000);
    
    while (client.available()) {
      /* actual data reception */
      char c = client.read();
      /* print data to serial port */
      Serial.print(c);
      /* wrap data to 80 columns*/
      received_data_num++;
      if(received_data_num % 80 == 0) { 
        Serial.println();
      }
    }

    waitStart = millis();
    while(client.connected() && millis() - waitStart < 1000);
    
    client.stop();
    Serial.println("Messaggio inviato");
  } else {
    Serial.println("Connessione fallita!");
  }

  return true;
}
