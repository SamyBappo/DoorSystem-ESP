// pins for SPI communication with RFID-RC522 card reader
#define RELAY_PIN 7 // pin for relay
#define RST_PIN 22 // Reset pin
#define SS_PIN 21  // Slave select pin

#define LED_GREEN_PIN 2
#define LED_YELLOW_PIN 4
#define LED_RED_PIN 17
#define ONBOARD_LED_PIN 2

// default Wifi credentianls
const char *ssid = "EcoleDuWeb2.4g";
const char *password = "EcoleDuWEB";

// const and var for mqtt connection and communication
const char *doorName        = "C-089";

const char *apiServer       = "137.184.168.254";
const int   apiPort         = 8080;
const char *api_card_check  = "/api/access/check";
const char *api_card_add    = "/api/card/add";

const char *mqttServer      = "172.16.5.101";
const int   mqttPort        = 1883;
const char *mqtt_name       = "ESP32";
const char *mqtt_pub_check  = "/door/card/check"; // The topic to which our client will publish
const char *mqtt_pub_add    = "/door/card/add"; // The topic to which our client will publish
const char *mqtt_sub_topic  = "/DoorSystem/access";  // The topic to which our client will subscribe