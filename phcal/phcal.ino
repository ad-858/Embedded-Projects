#include <SoftwareSerial.h>
SoftwareSerial  gprsSerial(4,5);
#define SensorPin A3          // the pH meter Analog output is connected with the Arduino’s Analog

unsigned long int avgValue;  //Store the average value of the sensor feedback
float calibration_value = 21.34 - 0.7;
int phval = 0; 
float b;
 float phValue;
int buf[10],temp;

void setup()

{


 gprsSerial.begin(9600);      
  Serial.begin(9600);  
delay(15000);
pinMode(13,OUTPUT);
  Serial.println("Ready");    //Test the serial monitor

}

void loop()

{

  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value

  {

    buf[i]=analogRead(SensorPin);

    delay(10);

  }

  for(int i=0;i<9;i++)        //sort the analog from small to large

  {

    for(int j=i+1;j<10;j++)

    {

      if(buf[i]>buf[j])

      {

        temp=buf[i];

        buf[i]=buf[j];

        buf[j]=temp;

      }

    }

  }

  avgValue=0;

  for(int i=2;i<8;i++)                      //take the average value of 6 center sample

    avgValue+=buf[i];

 phValue=(float)avgValue*5.0/1024.0/6.0; //convert the analog into millivolt
// Serial.println(phValue);
  phValue=2.5*phValue;                      //convert the millivolt into pH value
//phValue=-5.70 * phValue+ calibration_value;
 
  Serial.print("    pH:");  

  Serial.println(phValue,2);

//  delay(2000);

  
  
 
  sendData();
  
   delay(15000);
} 
void ShowSerialData()
{
  while(gprsSerial.available()!=0)
  Serial.write(gprsSerial.read());
  delay(2000); 
}
void sendData(){
//  if (gprsSerial.available()){
//     Serial.println(" gsm ");
//    Serial.write(gprsSerial.read());
  gprsSerial.println("AT");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
 
  gprsSerial.println("AT+CPIN?");
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);
 
  gprsSerial.println("AT+CREG?");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
 
  gprsSerial.println("AT+CGATT?");
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);
 
//  gprsSerial.println("AT+CIPSHUT");
//  digitalWrite(LED_BUILTIN, HIGH);
//  delay(1000);
 
  gprsSerial.println("AT+CIPSTATUS");
  digitalWrite(LED_BUILTIN, LOW); 
  delay(2000);
 
  gprsSerial.println("AT+CIPMUX=0");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIICR");//bring up wireless connection
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIFSR");//get local IP adress
  digitalWrite(LED_BUILTIN, LOW); 
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSPRT=0");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
 
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  digitalWrite(LED_BUILTIN, LOW); 
  delay(2000);
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSEND");//begin send data to remote server
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  ShowSerialData();
  String str="GET https://api.thingspeak.com/update?api_key=829G5SPQXORERTJU&field1=" + String( phValue) ;
  Serial.println(str);
  gprsSerial.println(str);//begin send data to remote server
  digitalWrite(LED_BUILTIN, LOW); 
  
  delay(2000);
  ShowSerialData();
// 
  gprsSerial.println((char)26);//sending
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);//waitting for reply, important! the time is base on the condition of internet 
  gprsSerial.println();
 
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");//close the connection
  delay(100);digitalWrite(LED_BUILTIN, LOW); 
  ShowSerialData();
  }
  

  
