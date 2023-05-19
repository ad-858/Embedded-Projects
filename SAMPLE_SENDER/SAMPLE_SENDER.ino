/*  Codes that Sends  JSON data using ESPNOW Protocol

*   Developed by  Jay Joshi 
*   github.com/JayJoshi16
*   
*   Modified by Sachin Soni
*   
*   Developed for techiesms 
*   https://www.youtube.com/techiesms
*/

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x37, 0x44, 0x60}; //Destination ESP32's MAC Address //3C:61:05:2A:C4:70  AC:67:B2:37:44:60

int x=0;
#include <ArduinoJson.h>
String jsondata;
StaticJsonDocument<200> doc;


//function for Sending data
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) { 
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;   
    delay(10000);
  }

// Register peer
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  for (int ii = 0; ii < 6; ++ii )
  {
    peerInfo.peer_addr[ii] = (uint8_t) broadcastAddress[ii];
  }
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  
  esp_now_register_send_cb(OnDataSent);

}

void loop() 
{ 
  if(x==1){
  jsondata = "";  //clearing String after data is being sent
  
  doc["a"] = 1;   
  doc["b"] = "ON";
  serializeJson(doc, jsondata);  //Serilizing JSON
  /*
   * {
   *   "a" : 1,
   *   "b" : "ON"
   *   
   *  }
   * 
   * 
   */
  esp_now_send(broadcastAddress, (uint8_t *) jsondata.c_str(), sizeof(jsondata) + 6);  //Sending "jsondata"  
  Serial.println(jsondata);                                                     
  x=0;
  }
   delay(5000);
  if (x==0){
  jsondata = "";  //clearing String after data is being sent
  
  doc["a"] = 0;
  doc["b"] = "OFF";
  serializeJson(doc, jsondata);
  esp_now_send(broadcastAddress, (uint8_t *) jsondata.c_str(), sizeof(jsondata) + 6);
  Serial.println(jsondata);  
  x=1;
  }
  delay(5000);
}
