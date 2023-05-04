#include <SPI.h>
#include <MFRC522.h>

#include "myWiFi.h"
#include "myHttp.h"
#include "myMqtt.h"
#include "myRfid.h"

#include "var.h"

//__________________________________________________________________________________________________________

// my classes
// Create all instances.
MyRfid rfid(SS_PIN, RST_PIN);
MyWiFi wifi;
MyHttp http(apiServer, apiPort);
MyMqtt mqtt(mqttServer, mqttPort, mqtt_id, "", "", doorName);

/**
 * Initialize.
 */
void setup(){
  Serial.begin(115200); // Initialize serial communications with the PC
  
  pinMode(RELAY_PIN, OUTPUT);// pin setup for relay
  digitalWrite(RELAY_PIN, LOW); // make sure the relay is off
  pinMode(LED_GREEN_PIN, OUTPUT);// pin setup for led
  digitalWrite(LED_GREEN_PIN, LOW); // make sure the led is off
  pinMode(LED_YELLOW_PIN, OUTPUT);// pin setup for led
  digitalWrite(LED_YELLOW_PIN, LOW); // make sure the led is off
  pinMode(LED_RED_PIN, OUTPUT);// pin setup for led
  digitalWrite(LED_RED_PIN, HIGH); // make sure the led is on
  
  rfid.setup(); // Initialize RFID-RC522 card reader.
  delay(100);

  // wifi connection
  if( !wifi.connectToWiFi(ssid, password)){
    wifi.startAPMode("ESP32", "Patate123");
  }
  delay(100);

  mqtt.mqttSubAccess = mqtt_sub_access;
  mqtt.mqttSubAdd = mqtt_sub_add;
  mqtt.setup();// mqtt connection

  while (!Serial)
    ; // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  Serial.println("Lessgo scan...");
}


/**
 * Main loop.
 */
void loop(){
  mqtt.refresh();  //check mqtt and reconnect if disconnected

  if (rfid.isNewCardPresent()) {
    rfid.readCardSerial();
    Serial.print("UID tag: ");
    Serial.println(rfid.card);
    
    // http request to add card and door authorisation if add timout hasen't run out yet
    if (mqtt.add > 0){ http.sendPostReq(api_card_add, "uid", rfid.card.c_str(), "doorName", doorName); }
    // http request to check if card is authorized
    else{ http.sendPostReq(api_card_check, "cardUid", rfid.card.c_str(), "doorName", doorName); }
    //mqtt.publish(mqtt_pub_check, rfid.card.c_str());
  }

  mqtt.loop(); // loop mqtt client to check for incoming messages
  
  // opens door if card is authorized
  if (mqtt.auth) {
    digitalWrite(RELAY_PIN, HIGH);  // open door
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);
    delay(2000);                    // wait 2 seconds
    digitalWrite(RELAY_PIN, LOW);   // close door
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);
    mqtt.auth=0;                    // reset auth
  }

  
  if(mqtt.add > 0){
    mqtt.add --;
    digitalWrite(LED_YELLOW_PIN, HIGH);
    Serial.print(mqtt.add);
    Serial.println(" seconds remaining, Next card will be added .... ");
    delay (250);
    digitalWrite(LED_YELLOW_PIN, LOW);
  }
  delay(250);
}