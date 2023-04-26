// pins for SPI communication with RFID-RC522 card reader
#define RELAY_PIN 15 // pin for relay
#define ONBOARD_LED_PIN 2
#define RST_PIN 22 // Reset pin
#define SS_PIN 21  // Slave select pin

// default Wifi credentianls
const char *ssid = "P500";
const char *password = "Patate123";

// const and var for mqtt connection and communication
const char *doorName        = "C-089";

const char *apiServer       = "137.184.168.254";
const int   apiPort         = 8080;
const char *api_check_card  = "/api/access/check";
const char *api_add_card    = "/api/card/add";

const char *mqttServer      = "172.16.5.101";
const int   mqttPort        = 1883;
const char *mqtt_name       = "ESP32";
const char *mqtt_pub_check  = "/door/card/check"; // The topic to which our client will publish
const char *mqtt_pub_add    = "/door/card/add"; // The topic to which our client will publish
const char *mqtt_sub_topic  = "/door/access";  // The topic to which our client will subscribe
