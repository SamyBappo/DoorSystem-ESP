#include "myMqtt.h"

MyMqtt::MyMqtt(const char* server, int port, const char* username, const char* password, const char* clientId, const char* subTopic)
  : mqttClient(wifiClient) {
  mqttServer = server;
  mqttPort = port;
  mqttUsername = username;
  mqttPassword = password;
  mqttClientId = clientId;
  mqttSubTopic = subTopic;
}

// callback to be executed when the subscribed-to topic has a pub
void MyMqtt::callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message received from ");
  Serial.print(topic);
  Serial.print(" ");
  /*for (int i = 0; i < length; i++) { acsLvl = (payload[i] - '0'); }
  Serial.print(acsLvl);

  // gestion des etats selon la reponse de l'api
  switch (acsLvl) {
  case 1: auth=1; break;
  case 2: add=20; break;
    default: break;
  }

  Serial.println();*/
}

void MyMqtt::setup() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(MyMqtt::callback);
  //mqttClient.setCallback(callback);

  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT server");
      mqttClient.subscribe(mqttSubTopic);
    } else {
      Serial.print("MQTT connection failed with error code ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

//check mqtt and reconnect if disconnected
void MyMqtt::refresh() {
  //check mqtt and reconnect if disconnected
  if (!mqttClient.connected()) {
    Serial1.println("MQTT connection lost, trying to reconnect...");
    while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT server");
      mqttClient.subscribe(mqttSubTopic);
    } else {
      Serial.print("MQTT connection failed with error code ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
  }
}

void MyMqtt::loop() {
  mqttClient.loop();
}

void MyMqtt::publish(const char* topic, const char* message) {
  mqttClient.publish(topic, message);
}
