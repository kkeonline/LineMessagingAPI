/*
Line Messaging API for ESP8266
*/

#ifndef LineMessagingAPI_H
#define LineMessagingAPI_H

  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClientSecure.h>
  #define HARDWARE "esp8266"

class LineMessagingAPI{
  private:
    String _TOKEN = "";
    String _USERID = "";
    String _API_HOST = "api.line.me";
    String _API_PATH = "/v2/bot/message/push";
	String escapeStr(String S);

  public:
    int status_code = 0;

    LineMessagingAPI();

    void begin(String Channel_access_token = "");
    void begin(String Channel_access_token = "", String ReceiverUserID = "");
    void setToken(String Channel_access_token);
    void setUserID(String ReceiverUserID);
    bool notify(String message);
};

extern LineMessagingAPI LINE;
#endif
