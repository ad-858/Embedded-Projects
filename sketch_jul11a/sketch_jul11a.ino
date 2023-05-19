void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

Serial.print(".....");

pinMode(34,INPUT);
delay(5000);

}

void loop() {
  // put your main code here, to run repeatedly:
   analogSetPinAttenuation(34,ADC_6db);
//    analogSetSamples(5);   
    analogReadResolution(10); 
     
//      
//     analogSetWidth(12); 
Serial.println(analogRead(34));
 delay(2000);
//    
}

