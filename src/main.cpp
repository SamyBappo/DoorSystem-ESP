#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <PubSubClient.h>

// Wifi credentianls
const char *ssid = "EcoleDuWeb2.4g";
const char *password = "EcoleDuWEB";

// #define RST_PIN 9 // Configurable, see typical pin layout above
// #define SS_PIN 10 // Configurable, see typical pin layout above
#define ONBOARD_LED_PIN 2
#define RST_PIN 22 // Reset pin
#define SS_PIN 21  // Slave select pin
#define RELAY_PIN 15

// mqtt broker
char *mqttServer = "172.16.5.101";
int mqttPort = 1883;
const char *mqtt_client_name = "ESP32";
const char *mqtt_pub_check = "/door/card/check"; // The topic to which our client will publish
const char *mqtt_pub_add = "/door/card/add"; // The topic to which our client will publish
const char *mqtt_sub_topic = "/door/acsLvl";  // The topic to which our client will subscribe

//__________________________________________________________________________________________________________

WiFiClient client;
PubSubClient mqttClient(client);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

String card="";
byte acsLvl=0;
bool add=0;
bool auth=0;

String masterCard = "72 0C AA 1B";
String cards[] = {"B2 A8 3F 61", "DC 33 75 32"};

// callback to be executed when the subscribed-to topic has a pub
void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message received from ");
  Serial.print(topic);
  Serial.print(" ");
  for (int i = 0; i < length; i++) { acsLvl = (payload[i] - '0'); }
  Serial.print(acsLvl);
  switch (acsLvl)
  {
  case 1:
    auth=1;
    break;
  case 2:
    add=1;
    break;
  
  default:
    break;
  }

  Serial.println();
}

/**
 * Initialize.
 */
void setup(){
  Serial.begin(115200); // Initialize serial communications with the PC
  WiFi.mode(WIFI_STA);  // The WiFi is in station mode
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Hol'up a minute");
  delay(3000);

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  while (!Serial)
    ; // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init();
  delay(10);
  //mfrc522.PCD_DumpVersionToSerial(); // remove in prod
  if (!mqttClient.connected())
  {
    while (!mqttClient.connected())
    {
      if (mqttClient.connect(mqtt_client_name))
      {
        Serial.println("MQTT Connected!");
        mqttClient.subscribe(mqtt_sub_topic);
      }
      else { Serial.print(".");}
    }
  }

  Serial.println("Lessgo scan...");
}

/**
 * Main loop.
 */
void loop(){
  //check mqtt and reconnect if disconnected
  if (!mqttClient.connected()) {
    while (!mqttClient.connected())
    {
      if (mqttClient.connect(mqtt_client_name))
      {
        Serial.println("MQTT Connected!");
        mqttClient.subscribe(mqtt_sub_topic);
      }
      else { Serial.print("."); }
    }
  }

  if (mfrc522.PICC_IsNewCardPresent()) // when card is scanned
  {
    mfrc522.PICC_ReadCardSerial();
    card = "";
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      card.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      card.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    card.toUpperCase();
    //Serial.print("UID tag : ");
    //Serial.println(card);
    mqttClient.publish(mqtt_pub_check, card.c_str());
    delay(500);
  }

  mqttClient.loop();
  /*if (adding)
  {
    Serial.println("Next card will be added .... ");
    //cards[(sizeof(cards) / sizeof(int)) + 1] = content.substring(1); // marche pas ca
  }
  else
  {*/
    /*for (byte i = 0; i < sizeof(cards) / sizeof(int); i++) {
    if (card.substring(1) == masterCard) {
      authorisation = 1;
      break;
    }

    else { if (card.substring(1) == cards[i]) { authorisation = 1; } }
  }*/

  if (auth)
  {
    //Serial.println("access oui");
    digitalWrite(RELAY_PIN, HIGH); // ouvrir porte
    delay(2000);                   // laisser ouvert 2 secondes
    digitalWrite(RELAY_PIN, LOW);  // fermer porte
  }
  else
  {
    //Serial.println("non tu non non");
  }
  auth=0;
  add=0;
  //}
  delay(250);
}