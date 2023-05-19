#include <HTTPClient.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>
#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
const char* ssid = "Redmi";
const char* password = "12345678";
String jsondata;
String my_arr[5];
int i=0;
 char macStr[18];
StaticJsonDocument<200> doc;
String prvMacAddress;
String cur_mac;
AsyncWebServer server(80);
void data_receive(const uint8_t * mac_addr, const uint8_t *incomingData, int len) 
{
//  char macStr[18];
  Serial.print("Received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  char* buff = (char*) incomingData;        //char buffer
  jsondata = String(buff);                  //converting into STRING
//    my_arr[i]=String(jsondata); 
//  Serial.println(jsondata); 
   char* current_mac=macStr;
  cur_mac=String(current_mac);
 
//  for (int i=0; i<10; i++)
//  {
    if( cur_mac!=prvMacAddress){
      Serial.print("inside if of for loop");
       Serial.println(cur_mac);
       Serial.print(i);
      my_arr[i]=String(jsondata); 
       send_data();
      Serial.print(i);
   Serial.println( my_arr[i]);
  
   i++;
   Serial.println(i);
    prvMacAddress= cur_mac;
    }
     Serial.println("array 0");
   Serial.println( my_arr[0]);
   Serial.println("array 1");
   Serial.println( my_arr[1]);
}
  
//   Serial.println( my_arr);


void wifi_connect()
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
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
  Serial.println("");
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
}
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  wifi_connect();
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
}
void send_data(){
  if(WiFi.status()== WL_CONNECTED)
{
//  for  (int j=0; j<10; j++)
//{
 Serial.println("entering http ");
   Serial.println(my_arr[i]);
 WiFiClient client;
 HTTPClient http;
 http.begin("https://murmuring-reef-78253.herokuapp.com/device/updateDevice");
 http.addHeader("Content-Type", "application/json");
 http.addHeader("authorization","Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MmM4NjVjNDNkYTZhNDU4YmJlYmUyMWUiLCJpYXQiOjE2NTc0MzM3MzB9.J09gXugPb0rd3b3b74sV-OL88qCD7Lpjbf_pj9DFLbE");
 int httpResponseCode = http.POST(my_arr[i]);  
 Serial.print("HTTP Response code: ");
 Serial.println(httpResponseCode);
 if(httpResponseCode==200)
   {
     Serial.println("Sent data with success to server");
     Serial.println(my_arr[i]);
   }
 else 
   {
     Serial.println("Error sending the data to server");
     Serial.println(my_arr[i]);
   }
 http.end();
 delay(4000);
}
}
void loop()
{
  esp_err_t outcome = esp_now_register_recv_cb(data_receive);
  delay(10000);
   
  }
  
