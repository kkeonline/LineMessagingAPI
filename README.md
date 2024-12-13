# LineMessagingAPI
Simple replacement from Line Notify to Line Messaging API for Arduino ESP32 / ESP8266 / NodeMCU to send message <br>
support only plain text without sticker/emoji, escape string \r \n \t \\" \\\\ are supported <br>

Note: <br>
To use Line MessagingAPI you have to create Line OA account via https://manager.line.biz then enable MessagingAPI <br>
then goto https://developers.line.biz/console/ and create "Channel access token" to use as Token <br>
To send a message you have to know the receiver UserID or GroupID to send message to <br>
to know that open https://webhook.site/ and copy unique url to Line developper console and enable hook
then send message from the user to Line OA then you will know the UserID from webhook Log.
