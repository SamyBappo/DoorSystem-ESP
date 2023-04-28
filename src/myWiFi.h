#ifndef MYWIFI
#define MYWIFI

#include <WiFi.h>

class MyWiFi {
  public:
    bool connectToWiFi(const char* ssid, const char* password);
    void startAPMode(const char* apSSID, const char* apPassword);

  private:
    WiFiServer server;
    void serveWebPage(WiFiClient client);
};

#endif