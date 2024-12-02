# LineMessagingAPI
Simple replacement from Line Notify to Line Messaging API for Arduino ESP8266 / NodeMCU to send message
support only plain text without sticker/emoji
escape string \r \n \t \" are supported

OLD code:
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN "************************"
LINE.setToken(LINE_TOKEN);
LINE.notify("your message");

NEW code:
#include <LineMessagingAPI.h>
const char* LINE_TOKEN = "***********************************************************";
const char* LINE_USER = "*************************";
LINE.setToken(LINE_TOKEN);
LINE.setUserID(LINE_USER);
LINE.notify("your message");

*Note:
To use Line MessagingAPI you have to create Line OA account via https:/manager.line.biz then enable MessagingAPI
then create "Channel access token" to use like old Token from https://developers.line.biz/console/
then you have to know the receiver UserID or GroupID to send message to (open https://webhook.site/ and copy unique url to Line developper console then send message from that user to Line OA then you will know that UserID from the Log)
