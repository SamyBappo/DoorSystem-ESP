// pins for SPI communication with RFID-RC522 card reader
#define RELAY_PIN 15 // pin for relay
#define ONBOARD_LED_PIN 2
#define RST_PIN 22 // Reset pin
#define SS_PIN 21  // Slave select pin

// default Wifi credentianls
const char *ssid = "EcoleDuWeb2.4g";
const char *password = "EcoleDuWEBno";

// const and var for mqtt connection and communication
const char *mqttServer        = "172.16.5.101";
const int   mqttPort          = 1883;
const char *mqtt_client_name  = "ESP32";
const char *mqtt_pub_check    = "/door/card/check"; // The topic to which our client will publish
const char *mqtt_pub_add      = "/door/card/add"; // The topic to which our client will publish
const char *mqtt_sub_topic    = "/door/acsLvl";  // The topic to which our client will subscribe
