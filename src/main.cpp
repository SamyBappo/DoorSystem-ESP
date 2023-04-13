#include <SPI.h>
#include <MFRC522.h>
#include "myWiFi.h"
#include "myMqtt.h"

// pins for SPI communication with RFID-RC522 card reader
#define RELAY_PIN 15 // pin for relay
#define ONBOARD_LED_PIN 2
#define RST_PIN 22 // Reset pin
#define SS_PIN 21  // Slave select pin

// default Wifi credentianls
const char *ssid = "EcoleDuWeb2.4g";
const char *password = "EcoleDuWEB";

// const and var for mqtt connection and communication
const char *mqttServer        = "172.16.5.101";
const int   mqttPort          = 1883;
const char *mqtt_client_name  = "ESP32";
const char *mqtt_pub_check    = "/door/card/check"; // The topic to which our client will publish
const char *mqtt_pub_add      = "/door/card/add"; // The topic to which our client will publish
const char *mqtt_sub_topic    = "/door/acsLvl";  // The topic to which our client will subscribe

//__________________________________________________________________________________________________________

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

// my classes
myWiFi wifi;
MyMqtt mqtt(mqttServer, mqttPort,  mqtt_client_name, "", "", mqtt_sub_topic);
// variables for state management
String card="";
byte acsLvl=0;
//byte add=0;
//bool auth=0;

// test variables (remove later)
String masterCard = "72 0C AA 1B";
String cards[] = {"B2 A8 3F 61", "DC 33 75 32"};

/**
 * Initialize.
 */
void setup(){
  Serial.begin(115200); // Initialize serial communications with the PC
  
  // pin setup for relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // make sure the relay is off
  
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init();
  delay(10);

  // wifi connection
  if( !wifi.connectToWiFi(ssid, password)){
    wifi.startAPMode("ESP32", "Patate123");
  }
  delay(3000);

  // mqtt connection
  mqtt.setup();

  while (!Serial)
    ; // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  Serial.println("Lessgo scan...");
}


/**
 * Main loop.
 */
void loop(){
  //check mqtt and reconnect if disconnected
  mqtt.refresh();

  if (mfrc522.PICC_IsNewCardPresent()) // when card is scanned
  {
    mfrc522.PICC_ReadCardSerial(); // card is read
    card = "";
    for (byte i = 0; i < mfrc522.uid.size; i++){
      card.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      card.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    card.toUpperCase();
    Serial.print("UID tag : ");
    Serial.println(card);

    if(mqtt.add==0){ mqtt.publish(mqtt_pub_check, card.c_str()); }// send uid to mqtt server to check if card is authorized
    else {
      mqtt.publish(mqtt_pub_add, card.c_str()); // send uid to mqtt server to add card
      mqtt.add=0;
    }
  }

  mqtt.loop(); // loop mqtt client to check for incoming messages
  
  // opens door if card is authorized
  if (mqtt.auth) {
    Serial.println("access oui");
    digitalWrite(RELAY_PIN, HIGH); // ouvrir porte
    delay(2000);                   // laisser ouvert 2 secondes
    digitalWrite(RELAY_PIN, LOW);  // fermer porte
    mqtt.auth=0;                        // reset
  }

  // pour ajouter la carte
  if (mqtt.add > 0){
    mqtt.add --;
    Serial.print(mqtt.add);
    Serial.println(" second remaining, Next card will be added .... ");
  }

  delay(250);
}

// callback to be executed when the subscribed-to topic has a pub
/*void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message received from ");
  Serial.print(topic);
  Serial.print(" ");
  for (int i = 0; i < length; i++) { acsLvl = (payload[i] - '0'); }
  Serial.print(acsLvl);

  // gestion des etats selon la reponse de l'api
  switch (acsLvl) {
  case 1: auth=1; break;
  case 2: add=20; break;
    default: break;
  }

  Serial.println();
}*/