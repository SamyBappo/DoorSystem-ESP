#include <functional>
#include "myMqtt.h"

MyMqtt::MyMqtt(const char* server, int port, const char* client_id, const char* username, const char* password, const char* doorName)
  : mqttClient(wifiClient) {
  mqttServer = server;
  mqttPort = port;
  mqttClientId = client_id;
  mqttUsername = username;
  mqttPassword = password;
  this->doorName = doorName;
}

// callback to be executed when the subscribed-to topic has a pub
void MyMqtt::callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message received from ");
  Serial.print(topic);
  Serial.print(" ");
  String message;
  for (int i = 0; i < length; i++) { 
    message += (char)payload[i];
  }
  Serial.print(message);

  if (strcmp(topic, mqttSubAccess) == 0) {
    if (strcmp(message.c_str(), doorName) == 0) { this->auth = 1; } 
  } 
  if (strcmp(topic, mqttSubAdd) == 0) {
    this->add = 20;
  }
  // update member variables based on the received message
  // switch (access) {
  // case 1: this->auth=1; break;
  // case 2: this->add=20; break;
  //   default: break;
  // }

  Serial.println();
}

void MyMqtt::setup() {
  mqttClient.setServer(mqttServer, mqttPort);
  this->setCallback(std::bind(&MyMqtt::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  //mqttClient.setCallback(&MyMqtt::callback, this);
  //mqttClient.setCallback(callback);

  Serial.println("Connecting to MQTT server...");
  if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
    Serial.println("Connected to MQTT server");
    mqttClient.subscribe(mqttSubAccess);
    mqttClient.subscribe(mqttSubAdd);
  } else {
    Serial.print("MQTT connection failed with error code ");
    Serial.println(mqttClient.state());
    delay(5000);
  }
  
}

//check mqtt and reconnect if disconnected
void MyMqtt::refresh() {
  //check mqtt and reconnect if disconnected
  if (!mqttClient.connected()) {

    this->setCallback(std::bind(&MyMqtt::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    Serial1.println("MQTT connection lost, trying to reconnect...");
    
    Serial.println("Connecting to MQTT server...");
    if (mqttClient.connect(mqttClientId, mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT server");
      mqttClient.subscribe(mqttSubAccess);
      mqttClient.subscribe(mqttSubAdd);
    } 
    else {
      Serial.print("MQTT connection failed with error code ");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

void MyMqtt::loop() {
  mqttClient.loop();
}

void MyMqtt::publish(const char* topic, const char* message) {
  mqttClient.publish(topic, message);
}

void MyMqtt::setCallback(std::function<void(char*, byte*, unsigned int)> callback) {
  mqttClient.setCallback([=](char* topic, byte* payload, unsigned int length) {
    callback(topic, payload, length);
  });
}
