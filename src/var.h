// pins for SPI communication with RFID-RC522 card reader
#ifndef VARS
#define VARS

#define RELAY_PIN 15 // pin for relay
#define RST_PIN 39 // Reset pin
#define SS_PIN 5  // Slave select pin

#define LED_GREEN_PIN 2
#define LED_YELLOW_PIN 4
#define LED_RED_PIN 17

// default Wifi credentianls
const char *ssid = "Velvet"; // "EcoleDuWeb2.4g"; // "DESKTOP-LAMBDA"; //
const char *password = "Chepo123"; // "EcoleDuWEB"; // "bonjoure";// 

// const and var for mqtt connection and communication
const char *doorName        = "C-089";
const int   door_open_delay = 2000; // in milliseconds

const char *apiServer       = "137.184.168.254";
const int   apiPort         = 8080;
const char *api_card_add    = "/api/card/add";
const char *api_access_add  = "/api/access/add";
const char *api_access_check= "/api/access/check";

const char *mqttServer      = "137.184.168.254";
const int   mqttPort        = 1883;
const char *mqtt_user       = "user";
const char *mqtt_password   = "Patate123";
const char *mqtt_id         = "ESP32";
//const char *mqtt_pub_check  = "DoorSystem/card/check";
//const char *mqtt_pub_addCard= "DoorSystem/card/add";
const char *mqtt_door_open  = "DoorSystem/door/open";
const char *mqtt_card_add   = "DoorSystem/card/add";
const char *mqtt_access_add = "DoorSystem/access/add";

#endif