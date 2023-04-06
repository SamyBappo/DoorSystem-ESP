#include "myWiFi.h"

bool myWiFi::connectToWiFi(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);  // The WiFi is in station mode
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 5000) {
    Serial.print(".");
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected!");
    return true;
  } else {
    Serial.println("Connection failed.");
    return false;
  }
}

void myWiFi::startAPMode(const char* apSSID, const char* apPassword) {
  WiFi.mode(WIFI_AP); // The WiFi is in access point mode
  WiFi.softAP(apSSID, apPassword);
  Serial.print("Access point mode started with SSID and password:");
  Serial.println(apSSID + String(" ") + apPassword);
  Serial.print("Access point IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  while (1) {
    WiFiClient client = server.available();
    if (client) {
      serveWebPage(client);
    }
  }
}

void myWiFi::serveWebPage(WiFiClient client) {
  String request = client.readStringUntil('\r');
  client.flush();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>WiFi Configuration</title></head>");
  client.println("<body><h1>Configure WiFi</h1>");
  client.println("<form method=\"get\" action=\"/config\">");
  client.println("<label>SSID:</label>");
  client.println("<input type=\"text\" name=\"ssid\"><br>");
  client.println("<label>Password:</label>");
  client.println("<input type=\"password\" name=\"password\"><br>");
  client.println("<input type=\"submit\" value=\"Submit\">");
  client.println("</form>");
  client.println("</body></html>");

  if (request.indexOf("/config") != -1) {
    int ssidStart = request.indexOf("ssid=") + 5;
    int ssidEnd = request.indexOf("&password=");
    int passwordStart = request.indexOf("password=") + 9;
    int passwordEnd = request.indexOf("HTTP/1.1") - 1;

    String ssid = request.substring(ssidStart, ssidEnd);
    String password = request.substring(passwordStart, passwordEnd);

    Serial.println("SSID: " + ssid);
    Serial.println("Password: " + password);

    WiFi.disconnect();
    delay(1000);
    WiFi.begin(ssid.c_str(), password.c_str());
  }
}