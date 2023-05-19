#include <HTTPClient.h>
#define RXD2 16
#define TXD2 17
#include <ArduinoJson.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>
String jsondata;
String inString =" ";
const char* ssid = "Redmi";
const char* password = "12345678";
int a=0;
//uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x37, 0x44, 0x60};
//StaticJsonDocument<200> doc;


//void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//  Serial.print("\r\n Last Send Status:\t");
//  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//}
//constexpr char WIFI_SSID[] = "Redmi";
//
//int32_t getWiFiChannel(const char *ssid) {
//  if (int32_t n = WiFi.scanNetworks()) {
//      for (uint8_t i=0; i<n; i++) {
//          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
//              return WiFi.channel(i);
//          }
//      }
//  }
//  return 0;
//}
void setup() {
  Serial.begin(115200);
   Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2); //serial2.begin(baud-rate,protocol,rxpin,tx pin
//  WiFi.mode(WIFI_STA);
// Serial.print("Wi-Fi Channel: ");
//  Serial.println(WiFi.channel());
//  int32_t channel = getWiFiChannel(WIFI_SSID);
//
//  WiFi.printDiag(Serial); // Uncomment to verify channel number before
//  esp_wifi_set_promiscuous(true);
//  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
//  esp_wifi_set_promiscuous(false);
//  WiFi.printDiag(Serial); // Uncomment to verify channel change after
//
//  if (esp_now_init() != ESP_OK) {
//    Serial.println("Error initializing ESP-NOW");
//    return;
//  }
//  
//  esp_now_register_send_cb(data_sent);
//  
//  esp_now_peer_info_t peerInfo;
//  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//  peerInfo.channel = 0;  
//  peerInfo.encrypt = false;
//         
//  if (esp_now_add_peer(&peerInfo) != ESP_OK){
//    Serial.println("Failed to add peer");
//    return;
//  }
//WiFi.begin(ssid, password);
//  Serial.println("Connecting");
//  while(WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.print("Connected to WiFi network with IP Address: ");
//  Serial.println(WiFi.localIP());
//  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
//  Serial.println("");
//  Serial.print("Wi-Fi Channel: ");
//  Serial.println(WiFi.channel());
}
void loop() {
 
//  message.ID = 1;
//  message.integer = random(0,20);
//
//  esp_err_t outcome = esp_now_send(broadcastAddress, (uint8_t *) &message, sizeof(message));
while (Serial2.available()!=0) 
{
  char inChar = Serial2.read();
  inString +=(char) inChar;
 }
jsondata=inString;
Serial.println("data recieved :"+String(inString) );
//   
//jsondata = "";  //clearing String after data is being sent
//  
//  doc["deviceId"] = "99WU6iaifDhLsSsxAFuWXg";  
//  doc["voltage"]=3;
//   doc["current"] = 4; 
//  serializeJson(doc, jsondata);
//   esp_err_t outcome =esp_now_send(broadcastAddress, (uint8_t *) jsondata.c_str(), sizeof(jsondata) + 60);
//  Serial.println(jsondata);     
//  if (outcome == ESP_OK && a==0) {
//    Serial.println("Sent with success");
//    a=1;
//  }
//  else {
//    Serial.println("Error sending the data");
//  }
//  delay(40000);
//  inString=" ";
//if(WiFi.status()== WL_CONNECTED)
//{
//  for  (int j=0; j<10; j++)
//{
// Serial.println("entering http ");
//   Serial.println(my_arr[i]);
// WiFiClient client;
// HTTPClient http;
// http.begin("https://murmuring-reef-78253.herokuapp.com/device/updateDevice");
// http.addHeader("Content-Type", "application/json");
// http.addHeader("authorization","Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MmM4NjVjNDNkYTZhNDU4YmJlYmUyMWUiLCJpYXQiOjE2NTc0MzM3MzB9.J09gXugPb0rd3b3b74sV-OL88qCD7Lpjbf_pj9DFLbE");
// int httpResponseCode = http.POST(jsondata);  
// Serial.print("HTTP Response code: ");
// Serial.println(httpResponseCode);
// if(httpResponseCode==200)
//   {
//     Serial.println("Sent data with success to server");
//     Serial.println(jsondata);
//   }
// else 
//   {
//     Serial.println("Error sending the data to server");
//     Serial.println(jsondata);
//   }
// http.end();
// delay(4000);
//}
delay(5000);
}
