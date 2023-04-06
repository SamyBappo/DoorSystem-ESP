#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>

class myWiFi {
  public:
    bool connectToWiFi(const char* ssid, const char* password);
    void startAPMode(const char* apSSID, const char* apPassword);

  private:
    WiFiServer server;
    void serveWebPage(WiFiClient client);
};

#endif