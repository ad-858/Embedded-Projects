#include <SoftwareSerial.h>
#define tx 8
#define rx 9
#define  button_1 10
#define  button_2 11
#define  button_3 12
char c=' ';
int value1;
int value2;
int value3;
SoftwareSerial mySerial(rx, tx);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  mySerial.begin(9600);
   pinMode( button_1, INPUT_PULLUP);
   pinMode( button_2, INPUT_PULLUP);
   pinMode( button_3, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
value1=digitalRead( button_1);
value2=digitalRead( button_2);
value3=digitalRead( button_3);
Serial.println(value1);
Serial.println(value2);
Serial.println(value3);
delay(1000);
if( value1 == 0 )
  {
   Serial.println("A");
   mySerial.write("A");
   delay(500);
  }
  else if(  value2 == 0)
  {
    Serial.println("B");
    mySerial.write("B");
    delay(500);
  }
  else if(  value3 == 0)
  {
    Serial.println("C");
    mySerial.write("C");
    delay(500);
  }
  delay(200);
}
