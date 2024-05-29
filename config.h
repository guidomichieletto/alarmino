#ifndef CONFIG
#define CONFIG

#define PASSWORD_LENGTH 5
#define USERS 3

#define PIR A0
#define BUZZER A1
#define RFID_SDA_DIO 10
#define RFID_RESET_DIO 11
#define LCD_ADDR 0x27

#define WIFI_SSID "MM"
#define WIFI_PASS ""
#define SERVER ""
#define TOKEN ""

#define ALARM_DELAY 60000
#define ACTIVATION_DELAY 30000

#define STATUS_DEACTIVATED 0
#define STATUS_ACTIVATING 1
#define STATUS_ACTIVATED 2
#define STATUS_DELAY 3
#define STATUS_ALARM 4

#define AUTH_FINGERPRINT 0
#define AUTH_RFID 1
#define AUTH_KEYPAD 2

#define RFID_RST 9
#define RFID_SS 10

#endif
