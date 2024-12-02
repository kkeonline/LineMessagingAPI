#include <LineMessagingAPI.h>

const char* LINE_TOKEN = "*******=";
const char* LINE_USER = "U*******";

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

LINE.begin(LINE_TOKEN, LINE_USER);
//or can set the Token and userID separately without call begin
//LINE.setToken(LINE_TOKEN);
//LINE.setUserID(LINE_USER);

  if(wifiConnected()) {
    Serial.println(" Successful");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    LINE.notify("Test \"Message\" from\t 'ESP8266'\r\nRunning IP:" + WiFi.localIP().toString())) {
  }
}

void loop(){
  delay(20000);
    if (LINE.notify("Test \"Message\" from\t 'ESP8266'\r\nRunning IP:" + WiFi.localIP().toString())) {
        Serial.println("Send Message successful");
    } else {
        Serial.println("Error sending message, status: " + LINE.status_code);
    }
}
