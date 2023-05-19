#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define tx 8
#define rx 9
#define in1 7
#define button_1 10
#define enA 3
#define led 12
int value;
int a=0;
int b=0;
int c=0;
int count=0;
int pwm=50;
char val;
int x=0;
int y=0;
int z=0;
SoftwareSerial mySerial(rx, tx); // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
void setup() {
  // put your setup code here, to run once:
pinMode( button_1, INPUT_PULLUP);
pinMode(in1,OUTPUT);
pinMode(enA,OUTPUT);
pinMode(led,OUTPUT);
Serial.begin(9600);
mySerial.begin(9600);
lcd.init(); // initialize the lcd
lcd.backlight();
digitalWrite(in1,LOW);
lcd.print("Vehicle Speed ") ;
lcd.setCursor(0, 1);
lcd.print("Limit controller");  
delay(3000);
lcd.clear();
lcd.setCursor(3, 0);
lcd.print("Speed  0mph"); 
digitalWrite(in1,LOW); 
}

char bt(){
 
   char val = mySerial.read();
    Serial.println(val);
    if(val == 'A' )
    {
      digitalWrite(led, HIGH);
       if(pwm >40)
       {
        Serial.print("Over speed ");
        lcd.clear();
        lcd.print("Over speed") ;
        lcd.setCursor(0, 1);
        lcd.print("Detection");
        pwm=40;
        analogWrite(3,pwm); 
        delay(2000);
        lcd.clear();   
        lcd.print("mapping speed to") ;
        lcd.setCursor(4, 1);
        lcd.print(pwm);
        lcd.print("mph");
        digitalWrite(in1,HIGH);
        analogWrite(enA,50);
     }
    digitalWrite(led, LOW);
    a=1;
    b=0;
    c=0;
   }
    else if(val == 'B')
    {
       digitalWrite(led, HIGH);
       if(pwm >60)
       {
        Serial.print("Over speed ");
        lcd.clear();
        lcd.print("Over speed") ;
        lcd.setCursor(0, 1);
        lcd.print("Detection");
        pwm=60;
        analogWrite(3,pwm); 
        delay(2000);
        lcd.clear();   
        lcd.print("mapping speed to") ;
        lcd.setCursor(4, 1);
        lcd.print(pwm);
        lcd.print("mph");
        digitalWrite(in1,HIGH);
        analogWrite(enA,80);
     }
     digitalWrite(led, LOW);
     a=0;
     b=1;
     c=0;
}
 else if(val == 'C')
    {
       digitalWrite(led, HIGH);
       if(pwm >80)
       {
        Serial.print("Over speed ");
        lcd.clear();
        lcd.print("Over speed") ;
        lcd.setCursor(0, 1);
        lcd.print("Detection");
        pwm=80;
        analogWrite(3,pwm); 
        delay(2000);
        lcd.clear();   
        lcd.print("mapping speed to") ;
        lcd.setCursor(4, 1);
        lcd.print(pwm);
        lcd.print("mph");
        digitalWrite(in1,HIGH);
        analogWrite(enA,100);
     }
     digitalWrite(led, LOW);
     a=0;
     b=0;
     c=1;
}
return val;
}
void changeSpeed()
{
  if(value==0 && a==0 && b==0 && c==0){
  count++;
  switch(count){
    case 1:
    digitalWrite(in1,HIGH);
    analogWrite(enA,pwm);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    pwm=pwm-30;
    lcd.print(pwm);
    lcd.print("mph");
    break;
    case 2:
    pwm=70;
    digitalWrite(in1,HIGH);
    analogWrite(enA,pwm);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    pwm=pwm-30;
    lcd.print(pwm);
    lcd.print("mph");
    break; 
    case 3:
    pwm=90;
    digitalWrite(in1,HIGH);
    analogWrite(enA,pwm);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    pwm=pwm-30;
    lcd.print(pwm);
    lcd.print("mph");
    break;
    case 4:
    pwm=110;
    digitalWrite(in1,HIGH);
    analogWrite(enA,pwm);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    pwm=pwm-30;
    lcd.print(pwm);
    lcd.print("mph");
    break;
    case 5:
    pwm=130;
    digitalWrite(in1,HIGH);
    analogWrite(enA,pwm);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    pwm=pwm-30;
    lcd.print(pwm);
    lcd.print("mph");
    break;
    case 6:
    pwm=250;
    digitalWrite(in1,HIGH);
    analogWrite(enA,pwm);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    pwm=pwm-130;
    lcd.print(pwm);
    lcd.print("mph");
    break;
  }
}
 delay(1000);
  
}

void incSpeed(){
 if(value==0)
 {
  x=pwm+10;
  switch(x){
    case 30:
    pwm=x;
    digitalWrite(in1,HIGH);
    analogWrite(enA,55);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    lcd.print(pwm);
    lcd.print("mph");
    delay(1000);
   
    break;
    case 40:
     pwm=x;
    digitalWrite(in1,HIGH);
    analogWrite(enA,60);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    lcd.print(pwm);
    lcd.print("mph");
   
    break;
    case 50:
     pwm=x;
    digitalWrite(in1,HIGH);
    analogWrite(enA,65);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    lcd.print(pwm);
    lcd.print("mph");
   
    break;
    case 60:
     pwm=x;
    digitalWrite(in1,HIGH);
    analogWrite(enA,79);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    lcd.print(pwm);
    lcd.print("mph");
   
    break;
    case 70:
     pwm=x;
    digitalWrite(in1,HIGH);
    analogWrite(enA,85);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    lcd.print(pwm);
    lcd.print("mph");
   
    break;
    case 80:
     pwm=x;
    digitalWrite(in1,HIGH);
    analogWrite(enA,100);
    lcd.clear();
    lcd.setCursor(0, 0);   
    lcd.print("speed ") ;
    lcd.print(pwm);
    lcd.print("mph");
   
    break;
}
 }
}
void loop() 
{
//   lcd.clear();   
  value=digitalRead( button_1);
  Serial.print(value);

  if(mySerial.available())
  {
  val=bt();
  Serial.println(value);
  
 }
  if(pwm<40 && val=='A')
  {
     digitalWrite(led, HIGH);
    delay(500);
     incSpeed();
    digitalWrite(led,LOW);
    
  } 
  
else if(pwm<60 && val=='B'){
    digitalWrite(led, HIGH);
    delay(500);
     incSpeed();
    digitalWrite(led,LOW);
  }
  else if(pwm<80 && val=='C'){
    digitalWrite(led, HIGH);
    delay(500);
     incSpeed();
    digitalWrite(led,LOW);
  }
 
changeSpeed();

  
}
//********
