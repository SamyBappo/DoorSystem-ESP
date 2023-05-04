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

  public:
    const char* mqttSubOpen;
    const char* mqttSubAddCard;
    const char* mqttSubAddAccess;
    const char* doorName;
    bool open=0;
    byte addCard=0;
    byte addAccess=0;
    MyMqtt(const char* server, int port, const char* client_id, const char* username, const char* password, const char* doorName);
    void setup();
    void refresh();
    void loop();
    void publish(const char* topic, const char* message);
    void setCallback(std::function<void(char*, byte*, unsigned int)> callback);
    void callback(char* topic, byte* payload, unsigned int length);
};

#endif
