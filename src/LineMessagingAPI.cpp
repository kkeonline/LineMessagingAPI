/*
Line Messaging API Library for ESP32 ESP8266
Simple replacement from Line Notify to Line Messaging API for ESP32 ESP8266 to send plain text message
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

void LineMessagingAPI::setMulticastUserIDs(String ReceiverUserIDs) {
    ReceiverUserIDs.replace(" ", "");
    ReceiverUserIDs.replace(",", "\",\"");
    this->_MULTICAST_USERIDS = "\"" + ReceiverUserIDs + "\"";
}

String LineMessagingAPI::escapeStr(String S) {
  S.replace("\\", "\\\\");
  S.replace("\t", "\\t");
  S.replace("\r", "\\r");
  S.replace("\n", "\\n");
  S.replace("\"", "\\\"");
  return(S);
}

bool LineMessagingAPI::send(String apipath, String payload) {
    this->status_code=0;

	#ifdef ESP32
	  NetworkClientSecure client;
	#else
	  WiFiClientSecure client;
	#endif

    HTTPClient https;
    client.setInsecure();
    https.begin(client, this->_API_HOST, 443, apipath, true);
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", this->_TOKEN);
    this->status_code = https.POST(payload);
    https.end();
    client.stop();
    return(this->status_code==200);
}

bool LineMessagingAPI::push(String message) {
    this->status_code=0;
    if (message.length() <= 0) {
		this->status_code=-999; // Invalid Message length
        return false;
    }
    if (this->_USERID.length() <= 0) {
		this->status_code=-888; // Invalid UserID
        return false;
    }
	return this->send(_API_PUSH_PATH, "{\"to\":\"" + this->_USERID + "\",\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}");
}

bool LineMessagingAPI::push(String message, String ReceiverUserID) {
	this->setUserID(ReceiverUserID);
    return this->push(message);
}

bool LineMessagingAPI::notify(String message) {
    return this->push(message);
}

bool LineMessagingAPI::multicast(String message) {
    this->status_code=0;
    if (message.length() <= 0) {
		this->status_code=-999; // Invalid Message length
        return false;
    }
    if (this->_MULTICAST_USERIDS.length() <= 0) {
		this->status_code=-888; // Invalid UserIDs
        return false;
    }
    if (this->_MULTICAST_USERIDS.indexOf(',') <= 0) {
		this->status_code=-888; // Invalid UserIDs
        return false;
    }
	return this->send(_API_MULTICAST_PATH, "{\"to\":[" + this->_MULTICAST_USERIDS + "],\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}");
}

bool LineMessagingAPI::multicast(String message, String ReceiverUserIDs) {
	this->setMulticastUserIDs(ReceiverUserIDs);
    return this->multicast(message);
}

bool LineMessagingAPI::broadcast(String message) {
    this->status_code=0;
    if (message.length() <= 0) {
		this->status_code=-999; // Invalid Message length
        return false;
    }
	return this->send(_API_BROADCAST_PATH, "{\"messages\":[{\"type\":\"text\",\"text\":\"" + this->escapeStr(message) + "\"}]}");
}

LineMessagingAPI LINE;
