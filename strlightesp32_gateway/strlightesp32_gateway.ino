#define RXD2 16
#define TXD2 17
#include <HTTPClient.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
const char* ssid = "Redmi";
const char* password = "12345678";
const char* serverName = "http://api.thingspeak.com/update";  // https://api.thingspeak.com/channels/1674256/status.json?api_key=YLVXH5RSVPPGCC1E
String finalUrl = "";
String jsondata;
StaticJsonDocument<200> doc;
String apiKey = "829G5SPQXORERTJU";
AsyncWebServer server(80);
void data_receive(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);

char* buff = (char*) incomingData;        //char buffer
  jsondata = String(buff);                  //converting into STRING
//  Serial.print("Recieved ");
  Serial.println(jsondata); 

}
void setup() {
 
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,RXD2,TXD2); //serial2.begin(baud-rate,protocol,rxpin,tx pin
  WiFi.mode(WIFI_AP_STA);
   WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

//  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
   
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
 
}

 
void loop() {
   esp_err_t outcome = esp_now_register_recv_cb(data_receive);
//   jsondata="";
//   doc["api_key"]="829G5SPQXORERTJU";                     //"api_Key":"829G5SPQXORERTJU","Device_ID":1,"current":3
//    doc["Device_ID"]=1;
//   doc["current"]=3;
//   serializeJson(doc,jsondata);
//   Serial.println(jsondata);
//   Serial2.print(jsondata);
//  if (outcome == ESP_OK) {

// Serial2.print(jsondata);
if(WiFi.status()== WL_CONNECTED)

  {
 Serial.println("entering http ");
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
//      http.begin(client, serverName);
 http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
//      doc["api_key"] = apiKey;   
//  doc["current"] = 7;
//  serializeJson(doc, jsondata);
//      String httpRequestData = "{\"api_key\":\"" + apikey + "\",\"field1\":\"" + String(random(3)) + "\"}";    
      int httpResponseCode = http.POST(jsondata);  
       Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      if(httpResponseCode==200){
         Serial.println("Sent data with success to server");
      }
      else {
    Serial.println("Error sending the data to server");
         }
      // Free resources
      http.end();
      delay(40000);
//      WiFi.disconnect();
    }
    else 
    {
      Serial.println("WiFi Disconnected");
    }
    
//   
//  }
//  else {
//    Serial.println("Error sending the data to serial port");
//  }
  
         
      // Free resources
// 
     delay(50000); 
  }
