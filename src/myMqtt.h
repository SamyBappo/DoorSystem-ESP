#ifndef MYMQTT
#define MYMQTT

#include <WiFi.h>
#include <PubSubClient.h>

class MyMqtt {
  private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    const char* mqttServer;
    int mqttPort;
    const char* mqttUsername;
    const char* mqttPassword;
    const char* mqttClientId;
    const char* mqttSubTopic;

  public:
    MyMqtt(const char* server, int port, const char* username, const char* password, const char* clientId, const char* subTopic);
    void setup();
    void refresh();
    void loop();
    void publish(const char* topic, const char* message);
    void callback();
};

#endif
