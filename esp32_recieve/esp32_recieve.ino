#define RXD2 16
#define TXD2 17
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "VSMART ACADEMY-uedkn";
const char* password = "VSMART@123";

String jsondata;
StaticJsonDocument<200> doc;

String inString =" ";
  int a=0;
void setup() {
  // put your setup code here, to run once: pPdPU4rnVn5dYDXchQTToE
Serial.begin(115200);
Serial2.begin(9600,SERIAL_8N1,RXD2,TXD2); //serial2.begin(baud-rate,protocol,rxpin,tx pin
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


}

void loop() {
  
  // put your main code here, to run repeatedly:
  

while (Serial2.available()!=0) 
{

      char inChar = Serial2.read();
     
      inString +=(char) inChar;
 
}
//if (a==1){
// Serial.print("inside if");

//a=0;
Serial.println("data recieved :"+String(inString) );
jsondata=inString;
delay(5000);
if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      http.begin("https://murmuring-reef-78253.herokuapp.com/device/updateDevice");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("authorization","Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MmM4NjVjNDNkYTZhNDU4YmJlYmUyMWUiLCJpYXQiOjE2NTc0MzM3MzB9.J09gXugPb0rd3b3b74sV-OL88qCD7Lpjbf_pj9DFLbE");
      int httpResponseCode = http.POST(jsondata);    
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
      delay(5000);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    inString =" ";
}
