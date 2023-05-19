#include <math.h>
float nVPP_one;
float nCurrThruResistorPP_one;// Peak Current Measured Through Resistor
float nCurrThruResistorRMS_one;// RMS current through Resistor
float nCurrentThruWire_one;  //CurrentThruWire

void setup()
{
  Serial.begin(9600);

Serial.print(".....");

pinMode(A7,INPUT);

}
float getVPP_one()
{
  
  float result;
  float readValue=0;             //value read from the sensor
  float maxValue = 0;
 
  uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(A7);
       
      // readValue2 = analogRead(33);
//       Serial.println(readValue);
       // see imaxValuef you have a new 
       if (readValue > maxValue) 
       {
//           /*record the maximum sensor value*/
           maxValue = readValue;
//         readValue =  maxValue;
       }
   }
   
   // Convert the digital data to a voltage
   //Serial.print("Value1: "+ String(readValue));
  // Serial.println("Value1: "+ String(readValue));
   result = (maxValue * 3.3)/1024.0;  
   return result;
   
 }

 
void loop() 
{
// Serial.println(analogRead(A7));
 delay(5000);
 nVPP_one = getVPP_one(); 
 nCurrThruResistorPP_one = ceil((nVPP_one/200.0)*1000);
 nCurrThruResistorRMS_one = nCurrThruResistorPP_one * 0.707;
 nCurrentThruWire_one = nCurrThruResistorRMS_one *1000;
// Serial.println(  "nvpp: "+String( nVPP_one) );
 Serial.println(  "Current through wire : "+String(nCurrentThruWire_one)+"mA RMS" );
// Serial.println(  "Current_one: "+String(nCurrThruResistorPP_one)+"mA RMS"); 

}


