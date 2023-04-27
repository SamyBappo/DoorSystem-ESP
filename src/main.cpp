#include <SPI.h>
#include <MFRC522.h>
#include "myWiFi.h"
#include "myHttp.h"
#include "myMqtt.h"
#include "myRfid.h"

#include "var.h"

//__________________________________________________________________________________________________________

// my classes

MyRfid rfid(SS_PIN, RST_PIN); // Create MyRfid instance.
MyWiFi wifi;
MyHttp http(apiServer, apiPort);
MyMqtt mqtt(mqttServer, mqttPort,  mqtt_name, "", "", mqtt_sub_topic);

// variables for state management
String card="";
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
  
  rfid.setup(); // Initialize RFID-RC522 card reader.
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

  if (rfid.isNewCardPresent()) {
    card = rfid.readCardSerial();
    Serial.print("UID tag: ");
    Serial.println(card);
    
    if (mqtt.add > 0){
        // http request to add card and door authorisation
        http.sendPostReq(api_check_card, "cardUid", card.c_str(), "doorName", doorName);
      }
      else{
        // http request to check if card is authorized
        http.sendPostReq(api_check_card, "cardUid", card.c_str(), "doorName", doorName);
      }
  }

  mqtt.loop(); // loop mqtt client to check for incoming messages
  
  // opens door if card is authorized
  if (mqtt.auth) {
    Serial.println("access oui");
    digitalWrite(RELAY_PIN, HIGH);  // open door
    delay(2000);                    // wait 2 seconds
    digitalWrite(RELAY_PIN, LOW);   // close door
    mqtt.auth=0;                    // reset auth
  }

  

  mqtt.add --;
  Serial.print(mqtt.add);
  Serial.println(" second remaining, Next card will be added .... ");
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