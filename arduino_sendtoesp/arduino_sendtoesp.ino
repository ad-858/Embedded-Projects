#include <ArduinoJson.h>
String jsondata;
float nVPP_one;
float nVPPn;// Voltage measured across resistor
float nCurrThruResistorPP_one;
float nCurrThruResistorRMS_one;
float nCurrentThruWire_one;
int current_sensor=A1;
int voltage_sensor=A0;
int analogread;
int voltage;
int ac_voltage;
int voltagesens = A0;
float calibrate = 0.3606465028355388; // calibrate value
int a,b=0;
StaticJsonDocument<200> doc;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print(".....");
pinMode(A0,INPUT);

}
float current_cal()
{
  
  float result;
  float readValue=0;             //value read from the sensor
  float maxValue = 0;
 
  uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(A1);
       
      
       if (readValue > maxValue) 
       {
       
           maxValue = readValue;
       
       }
   }
   
   
   result = (maxValue * 5.0)/1024.0;  
   return result;
   
 }

 float voltage_cal(){
   analogread = analogRead(voltagesens); // read analog values from pin A0
  ac_voltage = (analogread * calibrate);
  //end- Voltage sensing code//
   delay(1000);

  //start- Serial printing code//
//  Serial.print(" Analog Value " ); Serial.print(analogread);
//  Serial.print(" - A.C Voltage "); Serial.print(ac_voltage);
//  Serial.println();
  return ac_voltage;
 }

void loop() {
  // put your main code here, to run repeatedly:
// voltage= voltage_cal();
//  nVPP_one = current_cal(); 



 nCurrThruResistorPP_one = (nVPP_one/200.0)*1000;
 nCurrThruResistorRMS_one = nCurrThruResistorPP_one * 0.707;
 nCurrentThruWire_one = nCurrThruResistorRMS_one *1000;



// Serial.println(  "nvpp: "+String( nVPP_one) );
// Serial.println(  "Current_one: "+String(nCurrentThruWire_one)+"mA RMS" );
// Serial.println(  "Current_one: "+String(nCurrThruResistorPP_one)+"mA RMS"); apiKey = "829G5SPQXORERTJU";

if (nCurrentThruWire_one==0 && a==0){
  jsondata = "";  //clearing String after data is being sent
  
//  doc["api_Key"] = "829G5SPQXORERTJU";  
//  doc["Device_ID"]=1;                                   
//  doc["current"] = nCurrentThruWire_one;
 doc["deviceId"] = "99WU6iaifDhLsSsxAFuWXg";  
  doc["voltage"]=0;
   doc["current"] = 0;  
  serializeJson(doc, jsondata); 


Serial.println((jsondata));
a=1;
b=0;
}
if (nCurrentThruWire_one>=100 && b==0){
  jsondata = "";  //clearing String after data is being sent
   
  doc["deviceId"] = "99WU6iaifDhLsSsxAFuWXg";  
  doc["voltage"]=true;
   doc["current"] = true;  
  serializeJson(doc, jsondata);

Serial.println((jsondata));
  a=0;
b=1;
}
//jsondata = "";  //clearing String after data is being sent
//   doc["current"] = nCurrentThruWire_one; 
//  serializeJson(doc, jsondata);
//  Serial.print("JSON:");
//Serial.println((jsondata));
jsondata = "";  //clearing String after data is being sent
   
  doc["deviceId"] = "99WU6iaifDhLsSsxAFuWXg";  
  doc["voltage"]=true;
   doc["current"] = true;  
  serializeJson(doc, jsondata);

Serial.println((jsondata));

delay(5000);

}
