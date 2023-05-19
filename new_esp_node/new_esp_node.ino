#define RXD2 16
#define TXD2 17
#include <ArduinoJson.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
String jsondata;
String inString =" ";
int a=0;
uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x37, 0x44, 0x60};
StaticJsonDocument<200> doc;


void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\n Last Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
constexpr char WIFI_SSID[] = "Redmi";

int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}

void send_data()
{
 esp_err_t outcome =esp_now_send(broadcastAddress, (uint8_t *) jsondata.c_str(), sizeof(jsondata) + 100);
       if (outcome == ESP_OK)
       {
        Serial.println("Sent with success");
       }
      else 
      {
        Serial.println("Error sending the data");
      }
      esp_now_unregister_send_cb();
      if ( esp_now_unregister_send_cb() == ESP_OK) 
      {
        Serial.println("ESPNow esp_now_unregister_send_cbt Success");
      }
  WiFi.disconnect();
  esp_now_deinit() ;
       if (esp_now_deinit() == ESP_OK)
       {
        Serial.println("ESPNow deInit Success");
       }
      delay(10000);
      Serial.println("after delay");
}

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2); //serial2.begin(baud-rate,protocol,rxpin,tx pin
  WiFi.mode(WIFI_STA);
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
  int32_t channel = getWiFiChannel(WIFI_SSID);

  WiFi.printDiag(Serial); // Uncomment to verify channel number before
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);
  WiFi.printDiag(Serial); // Uncomment to verify channel change after
    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
  esp_now_register_send_cb(data_sent);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
      Serial.println("Failed to add peer");
      return;
    }
  
}
void loop() 
{
 Serial.println("Inside the loop ");
// while (Serial2.available()!=0) 
//{
//  char inChar = Serial2.read();
//  inString +=(char) inChar;
// }
//
//Serial.println("data recieved :"+String(inString) );  
//   

  

jsondata = "";  //clearing String after data is being sent
  
  doc["deviceId"] = "99WU6iaifDhLsSsxAFuWXg";  
  doc["voltage"]=1;
   doc["current"] = 1; 
//  DeserializationError error=deserializeJson(doc, inString);
//serializeJson(doc, jsondata);
//  if(error){
//    Serial.println("Deserialization Failed");
//     DeserializationError error=deserializeJson(doc, inString);
//  }
//  const char* deviceId=doc["deviceId"];
//  float voltage=doc["voltage"];
//  float current=doc["current"];
//    Serial.println(deviceId);
//     Serial.println(voltage);
//      Serial.println(current);
//      jsondata=inString;
//      if ( a==0){
         Serial.println("inside if ");
//        doc["deviceId"]=deviceId;
//  doc["voltage"]=voltage;
//  doc["current"]=current;
  serializeJson(doc, jsondata);
  Serial.println(jsondata);
      
   send_data();
  inString=" ";
  a=1;
//}
 delay(10000);
}
