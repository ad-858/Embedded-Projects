#include <b64.h>
#include <HttpClient.h>





//#include <ssl_client.h>
//#include <WiFiClientSecure.h>


#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
const char* ssid = "Redmi";
const char* password = "12345678";
// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";
// Service API Key
String apiKey = "829G5SPQXORERTJU";


String jsondata;
StaticJsonDocument<200> doc;
AsyncWebServer server(80);
//AsyncEventSource events("/events");

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

  char* buff = (char*) incomingData;        //char buffer
  jsondata = String(buff);                  //converting into STRING
  Serial.print("Recieved ");
  Serial.println(jsondata);    //Complete JSON data will be printed here
}
void check_connection()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  
  randomSeed(analogRead(33));
}

void send_data()
{
  if(WiFi.status()== WL_CONNECTED)
  {
      WiFiClient client;
     HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");
     int httpResponseCode = http.POST(jsondata);  
       Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
      delay(1000);
    }
    else 
    {
      Serial.println("WiFi Disconnected");
    }

}


void setup() {

  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP);
    pinMode(5,OUTPUT);
  if (esp_now_init() != ESP_OK) {       //Init ESPNOW
        Serial.println("Error initializing ESP-NOW");
        return;
  }
 
esp_now_register_recv_cb(OnDataRecv);  //Reciever CallBack function
//       DeserializationError error = deserializeJson(doc, jsondata);
//        if (!error) {
//        int a   = doc["Device_ID"]; 
//       float b  =   doc["current"]; 
//        Serial.println(a);                   //values of a
//        Serial.println(b); 
           
//        
// 
       check_connection();
       send_data(); 
//      
//  }
//else {
//        Serial.print(F("deserializeJson() failed: "));  //Just in case of an ERROR of ArduinoJSon
//        Serial.println(error.f_str());
//        return;
//  }
    
}

void loop() {
    
      
//  
//  
 
delay(5000);

}
