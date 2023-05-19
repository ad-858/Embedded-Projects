#include <ArduinoJson.h>
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
static const uint8_t msg_queue_len=5;
static QueueHandle_t msg_queue;
String jsondata;
StaticJsonDocument<200> doc;

//Serial.println(jsondata);
//struct AMessage
//{
//   char ucMessageID;
//   char ucData[ 20 ];
//} xMessage;
void printMessages(void *parameters){
  

  doc["abcd"]=1;
    doc["abcd"]=2;
  serializeJson(doc, jsondata);
  while(1){
    
  
  if(xQueueReceive(msg_queue,(void *) &jsondata,10)==pdTRUE){
  
   Serial.println(jsondata);
  }
  vTaskDelay(1000/portTICK_PERIOD_MS);
}

}
void setup() {
 
 Serial.begin(115200);
   vTaskDelay(1000/portTICK_PERIOD_MS); 
// Serial.println();unsigned char
 msg_queue=xQueueCreate(msg_queue_len,sizeof(char  ));
 xTaskCreatePinnedToCore(printMessages,"printmessages",2048,NULL,1,NULL,app_cpu);
}


void loop() {
  // put your main code here, to run repeatedly:
  static int num=0;
  //add items to queue
  if (xQueueSend(msg_queue,(void *) &num,10)!= pdTRUE){
    Serial.println("Queue full");

}
num++;
if (num==10){
  num=0;
}
//vTaskDelay(800 / portTICK_PERIOD_MS);
delay(500);

}
