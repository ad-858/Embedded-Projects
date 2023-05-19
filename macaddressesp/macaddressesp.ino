#include "WiFi.h"
//3C:61:05:2A:C4:70 mac adress of receiver
// AC:67:B2:37:44:60

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}
 
void loop(){

}
