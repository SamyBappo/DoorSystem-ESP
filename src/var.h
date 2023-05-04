// pins for SPI communication with RFID-RC522 card reader
#ifndef VARS
#define VARS

#define RELAY_PIN 15 // pin for relay
#define RST_PIN 22 // Reset pin
#define SS_PIN 21  // Slave select pin

#define LED_GREEN_PIN 2
#define LED_YELLOW_PIN 4
#define LED_RED_PIN 17
#define ONBOARD_LED_PIN 2

// default Wifi credentianls
const char *ssid = "X280";
const char *password = "Chepo123";

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
const char *mqtt_sub_open   = "DoorSystem/door/open";
const char *mqtt_sub_card   = "DoorSystem/card/add";
const char *mqtt_sub_access = "DoorSystem/access/add";

#endif