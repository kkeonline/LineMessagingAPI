/*
Line Messaging API for ESP8266
*/

#include "LineMessagingAPI.h"

LineMessagingAPI::LineMessagingAPI() {

}

void LineMessagingAPI::begin(String Channel_access_token) {
    this->_TOKEN = "Bearer " + Channel_access_token;
}

void LineMessagingAPI::begin(String Channel_access_token, String ReceiverUserID) {
    this->_TOKEN = "Bearer " + Channel_access_token;
    this->_USERID = ReceiverUserID;
}

void LineMessagingAPI::setToken(String Channel_access_token) {
    this->_TOKEN = "Bearer " + Channel_access_token;
}

void LineMessagingAPI::setUserID(String ReceiverUserID) {
    this->_USERID = ReceiverUserID;
}

String LineMessagingAPI::escapeStr(String S) {
  S.replace("\\", "\\\\");
  S.replace("\t", "\\t");
  S.replace("\r", "\\r");
  S.replace("\n", "\\n");
  S.replace("\"", "\\\"");
  return(S);
}

bool LineMessagingAPI::notify(String message) {
    this->status_code=0;
    if (message.length() <= 0) {
		this->status_code=-999; // Invalid Message length
        return false;
    }

    if (this->_USERID.length() <= 0) {
		this->status_code=-888; // Invalid UserID
        return false;
    }

   WiFiClientSecure client;
   HTTPClient https;
   client.setInsecure();
   https.begin(client, this->_API_HOST, 443, this->_API_PATH, true);
   https.addHeader("Content-Type", "application/json");
   https.addHeader("Authorization", this->_TOKEN);
   this->status_code = https.POST("{\"to\":\"" + this->_USERID + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}");
   https.end();
   client.stop();
   return(this->status_code==200);
}

LineMessagingAPI LINE;
