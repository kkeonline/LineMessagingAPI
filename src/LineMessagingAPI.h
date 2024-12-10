/*
Line Messaging API Library for ESP32 ESP8266
Simple replacement from Line Notify to Line Messaging API for ESP32 ESP8266 to send plain text message
*/

#ifndef LineMessagingAPI_H
#define LineMessagingAPI_H

#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
  #include <NetworkClientSecure.h>
  #define HARDWARE "esp32"
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClientSecure.h>
  #define HARDWARE "esp8266"
#endif

class LineMessagingAPI{
  private:
    String _TOKEN = "";
    String _USERID = "";
    String _MULTICAST_USERIDS = "";
    const String _API_HOST = "api.line.me";
    const String _API_BASE_PATH = "/v2/bot/message";
    const String _API_PUSH_PATH = _API_BASE_PATH + "/push";
    const String _API_MULTICAST_PATH = _API_BASE_PATH + "/multicast";
    const String _API_BROADCAST_PATH = _API_BASE_PATH + "/broadcast";
	String escapeStr(String S);
    bool send(String apipath, String payload);

  public:
    int status_code = 0;

    LineMessagingAPI();

    void begin(String Channel_access_token = "");
    void begin(String Channel_access_token = "", String ReceiverUserID = "");
    void setToken(String Channel_access_token);
    void setUserID(String ReceiverUserID); // String UserID = "userid1";
    void setMulticastUserIDs(String ReceiverUserIDs); // String UserIDs = "userid1, userid2, userid3";
    bool push(String message);
    bool push(String message, String ReceiverUserID);
    bool notify(String message);
    bool multicast(String message);
    bool multicast(String message, String ReceiverUserIDs);
    bool broadcast(String message);
};

extern LineMessagingAPI LINE;
#endif
