/*
Line Messaging API Library for ESP32 ESP8266
Simple replacement from Line Notify to Line Messaging API for ESP32 ESP8266 to send plain text message


*Note:
To use Line MessagingAPI you have to create Line OA account via https:/manager.line.biz then enable MessagingAPI
then create "Channel access token" to use like old Token from https://developers.line.biz/console/
then you have to know the receiver UserID or GroupID to send message to (open https://webhook.site/ and copy unique url to Line developper console
then send message from the user to Line OA then you will know that UserID from the Log)
*/

#include <LineMessagingAPI.h>

const char* LINE_TOKEN = "*******=";
//const char* LINE_USER = "U*******";
//multicast need 2 or more userIDs separate by comma
const char* LINE_USERS = "U1*******, U2********, U3********";

const char* ssid1 = "*****";
const char* password1 = "*****";

const int wifiTimeout = 30000;

bool wifiConnected() {
  return (WiFi.status() == WL_CONNECTED);
}

void setup() {
  Serial.begin(115200);
  delay(200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid1, password1);

  Serial.print("Connecting to wifi ");
  unsigned long Millis = millis();
  while (!wifiConnected()) { // Wait for the Wi-Fi to connect
    if (millis() - Millis >= wifiTimeout) {
      Serial.println(" timeout!");
      break;  
    }
    Serial.print(".");
    delay(200);
  }


LINE.begin(LINE_TOKEN);
//or
//LINE.setToken(LINE_TOKEN);

//set Multicast UserIDs
LINE.setMulticastUserIDs(LINE_USERS);


  if(wifiConnected()) {
    Serial.println(" Successful");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
	
	//LINE.setMulticastUserIDs(LINE_USERS);
    LINE.multicast("Test Multicast \"Message\" from\t'ESP8266'\r\n\\Running IP\\ " + WiFi.localIP().toString())) {
    //
	//or
    //LINE.multicast("Test Multicast \"Message\" from\t'ESP8266'\r\n\\Running IP\\ " + WiFi.localIP().toString()), LINE_USERS);
  }
}

void loop(){
  delay(20000);
    // get the return code
    if (LINE.multicast("Support 'Single quote\' \"Double quote\" \\Back slash\\ \ttab\t !@#$%^&*()_+-=;:.,/")) {
        Serial.println("Send Message successful");
    } else {
        Serial.println("Error sending message, status: " + LINE.status_code);
    }
}
