int voltagesens = A0; //input pin no
int analogread;
int ac_voltage;
float calibrate = 0.3706465028355388; // calibrate value
void setup()
{
  Serial.begin(9600);// begin serial communication between arduino and pc
  pinMode(voltagesens, INPUT); // set pin as input pin
}

void loop()
{

  //start- Voltage sensing code//
  analogread = analogRead(voltagesens); // read analog values from pin A0
  ac_voltage = (analogread * calibrate);
  //end- Voltage sensing code//
   delay(1000);

  //start- Serial printing code//
  Serial.print(" Analog Value " ); Serial.print(analogread);
  Serial.print(" - A.C Voltage "); Serial.print(ac_voltage);
  Serial.println();
  //end- Serial printing code//

}
