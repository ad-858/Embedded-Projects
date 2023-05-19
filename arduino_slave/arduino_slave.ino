int id=99;
#include <SoftwareSerial.h>

SoftwareSerial sw(0, 1); // RX, TX

void setup() {
 Serial.begin(9600);
 Serial.println("Interfacfing arduino with nodemcu");
 sw.begin(9600);
}

void loop() {
// Serial.println("Sending data to nodemcu");
// int adc=analogRead(A0);
 Serial.print("{\"sensorid\":");
 Serial.print(id);//sensor id
 Serial.print(",");
 Serial.print("\"adcValue\":");
 Serial.print(100);//offset
 Serial.print("}");
// Serial.println();
 
// sw.print("{\"sensorid\":");
// sw.print(id);//sensor id
// sw.print(",");
// sw.print("\"adcValue\":");
// sw.print(100);//offset adc value
// sw.print("}");
// sw.println();
 delay(5000);
}

