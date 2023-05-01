#ifndef MYHTTP
#define MYHTTP

#include <Arduino.h>
#include <HTTPClient.h>

class MyHttp {
  public:
    MyHttp(const char* url, uint16_t port);
    void sendPostReq(const char* url, const char* key1, const char* value1, const char* key2, const char* value2);

  private:
    HTTPClient client;
    const char* apiUrl;
    uint16_t apiPort;

    bool connect();
};

#endif
