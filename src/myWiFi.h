#ifndef MYWIFI
#define MYWIFI

#include <WiFi.h>

class myWiFi {
  public:
    bool connectToWiFi(const char* ssid, const char* password);
    void startAPMode(const char* apSSID, const char* apPassword);

  private:
    WiFiServer server;
    void serveWebPage(WiFiClient client);
    bool myWiFi::makePostRequest(const char* url, const std::map<String, String>& formData);
};

#endif