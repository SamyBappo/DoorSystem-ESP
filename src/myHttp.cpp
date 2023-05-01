#include "myHttp.h"

MyHttp::MyHttp(const char* url, uint16_t port) {
  apiUrl = url;
  apiPort = port;
}

void MyHttp::sendPostReq(const char* uri, const char* key1, const char* value1, const char* key2, const char* value2) {
  client.begin(apiUrl, apiPort, uri);

  client.addHeader("Content-Type", "application/x-www-form-urlencoded");

  char postData[100];
  strcpy(postData, key1);
  strcat(postData, "=");
  strcat(postData, value1);
  strcat(postData, "&");
  strcat(postData, key2);
  strcat(postData, "=");
  strcat(postData, value2);


  int httpResponseCode = client.POST(postData);

  // if (httpResponseCode > 0) {
  //   Serial.print("HTTP Response code: ");
  //   Serial.println(httpResponseCode);
  //   String response = client.getString();
  //   Serial.println(response);
  // } else {
  //   Serial.print("Error code: ");
  //   Serial.println(httpResponseCode);
  // }
}