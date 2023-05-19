float nVPP_one;

float nVPPn;// Voltage measured across resistor

float nCurrThruResistorPP_one;

float nCurrThruResistorRMS_one;

float nCurrentThruWire_one;


// Actual RMS current in Wire

//float nCurrThruResistorPPn; // Peak Current Measured Through Resistor
//float nCurrThruResistorRMSn; // RMS current through Resistor
//float nCurrentThruWiren;void setup() {
  // put your setup code here, to run once:

void setup(){
  Serial.begin(9600);

Serial.print(".....");
pinMode(A0,INPUT);

}
void loop() {
  // put your main code here, to run repeatedly:
 nVPP_one = getVPP_one(); 



 nCurrThruResistorPP_one = (nVPP_one/10000.0)*1000;
 nCurrThruResistorRMS_one = nCurrThruResistorPP_one * 0.707;
 nCurrentThruWire_one = nCurrThruResistorRMS_one *1000;



// Serial.println(  "nvpp: "+String( nVPP_one) );
 Serial.println(  "Current_one: "+String(nCurrentThruWire_one)+"mA RMS" );
// Serial.println(  "Current_one: "+String(nCurrThruResistorPP_one)+"mA RMS"); 




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
       
      // readValue2 = analogRead(34);
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
   result = (maxValue * 5.0)/1024.0;  
   return result;
   
 }

 
