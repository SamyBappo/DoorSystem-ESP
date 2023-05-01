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
const char *ssid = "P500";
const char *password = "Patate123";

// const and var for mqtt connection and communication
const char *doorName        = "C-089";

const char *apiServer       = "137.184.168.254";
const int   apiPort         = 8080;
const char *api_card_check  = "/api/access/check";
const char *api_card_add    = "/api/card/add";

const char *mqttServer      = "137.184.168.254";
const int   mqttPort        = 1883;
const char *mqtt_user       = "user";
const char *mqtt_password   = "Patate123";
const char *mqtt_id         = "ESP32";
const char *mqtt_pub_check  = "/DoorSystem/card/check"; // The topic to which our client will publish
const char *mqtt_pub_add    = "/DoorSystem/card/add"; // The topic to which our client will publish
const char *mqtt_sub_access = "/DoorSystem/door/open";  // The topic to which our client will subscribe
const char *mqtt_sub_add    = "/DoorSystem/card/add";  // The topic to which our client will subscribe

#endif