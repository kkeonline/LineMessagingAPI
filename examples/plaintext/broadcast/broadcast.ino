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
// Broadcast do not need UserID because it send to all Friends
//const char* LINE_USER = "U*******";

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


// Broadcast do not need UserID because it send to all Friends just call begin or setToken
LINE.begin(LINE_TOKEN);
//or
//LINE.setToken(LINE_TOKEN);


  if(wifiConnected()) {
    Serial.println(" Successful");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
	
    delay(1000);
    // Broadcast send message to all friends then take care of your monthly limit
    if (LINE.broadcast("Test Broadcast Message, Support 'Single quote\' \"Double quote\" \\Back slash\\ \ttab\t !@#$%^&*()_+-=;:.,/")) {
        Serial.println("Send Message successful");
    } else {
        Serial.println("Error sending message, status: " + LINE.status_code);
    }
  }
}

void loop(){
}
