#include <ArduinoJson.h>

//#include <ArduinoJson.h>
//#include <HTTPClient.h>
//#include <WiFiMulti.h>
// 
//const char *AP_SSID = "Redmi";
//const char *AP_PWD = "12345678";
//  
//WiFiMulti wifiMulti;
// 
//void setup() {
//  Serial.begin(115200);
//   
//  delay(4000);
//  wifiMulti.addAP(AP_SSID, AP_PWD);
//
//  
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
// postDataToServer();
// delay(20000);
//}
//void postDataToServer() {
// 
//  Serial.println("Posting JSON data to server...");
//  // Block until we are able to connect to the WiFi access point
//  if (wifiMulti.run() == WL_CONNECTED) {
//     
//    HTTPClient http;   
//     
////    http.begin("https://api.thingspeak.com/channels/<1674256>/bulk_update.json");  
//    http.begin("GET https://api.thingspeak.com/channels/1674256/status.json?api_key=YLVXH5RSVPPGCC1E");
//    http.addHeader("Content-Type", "application/json");         
//     
//    StaticJsonDocument<200> doc;
//    // Add values in the document
//    //
//    doc["sensor"] = "ph";
////    doc["time"] = 1351824120;
//   
//    // Add an array.
//    //
//    JsonArray data = doc.createNestedArray("data");
////    data.add(48.756080);
////    data.add(2.302038);
//      data.add(7);
//    String requestBody;
//    serializeJson(doc, requestBody);
//     
//    int httpResponseCode = http.POST(requestBody);
// 
//    if(httpResponseCode>0){
//       
//      String response = http.getString();                       
//       
//      Serial.println(httpResponseCode);   
//      Serial.println(response);
//     
//    }
//    else {
//     
//        Serial.println("Error occurred while sending HTTP POST: %s\n");
////        , HTTPClient.errorToString(statusCode).c_str()
//       
//    }
//     
//  }
//}
#include <WiFi.h>
#include <HTTPClient.h>
String jsondata;
StaticJsonDocument<200> doc;
const char* ssid = "Redmi";
const char* password = "12345678";

// Domain Name with full URL Path for HTTP POST Request
//const char* serverName = "http://api.thingspeak.com/update";
const char* serverName = "https://murmuring-reef-78253.herokuapp.com/device/updateDevice";
// Service API Key
String apiKey = "829G5SPQXORERTJU";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Set timer to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Timer set to 10 seconds (10000)
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200);
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


  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(analogRead(33));
}

void loop() {
  //Send an HTTP POST request every 10 seconds
 
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    String recv_token="Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MmM4NjVjNDNkYTZhNDU4YmJlYmUyMWUiLCJpYXQiOjE2NTc0MzM3MzB9.J09gXugPb0rd3b3b74sV-OL88qCD7Lpjbf_pj9DFLbE";
//            recv_token="Bearer "+recv_token;
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // Specify content-type header
//      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
//      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(random(40));           
//       Send HTTP POST request
//      int httpResponseCode = http.POST(httpRequestData);
      http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization","Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MmM4NjVjNDNkYTZhNDU4YmJlYmUyMWUiLCJpYXQiOjE2NTc0MzM3MzB9.J09gXugPb0rd3b3b74sV-OL88qCD7Lpjbf_pj9DFLbE");
//      doc["api_key"] = apiKey;   
//http.addHeader("Authorization",recv_token);
//      jsondata = "";  //clearing String after data is being sent
//  
doc["deviceId"] = "99WU6iaifDhLsSsxAFuWXg";  
  doc["voltage"]=3;
   doc["current"] = 3; 
//  doc["api_key"] = apiKey;   
//  doc["current"] = 3;
//   doc["current"] = 3;
  serializeJson(doc, jsondata);  //Serilizing JSON
//      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + String(random(10)) + "\"}";    
      int httpResponseCode = http.POST(jsondata);     
      /*
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      // JSON data to send with HTTP POST
      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + String(random(40)) + "\"}";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);*/
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
      delay(40000);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
