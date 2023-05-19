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
void jsonCreateTask(void *pvParameters){
  struct message{
    String a="1"
  }

  
  while(1){
     vTaskDelay(5000/portTICK_PERIOD_MS);
    doc["abcd"]=1;
    doc["abcd"]=2;
    char *rendered;
  serializeJson(doc, jsondata);
  
  if(xQueueReceive(msg_queue,(void *) &jsondata,10)==pdTRUE){
  
   Serial.println(jsondata);
  }
//cJson *root,*fmt;
//char *rendered;
//root=cJSON_CreateObject();
//cJSON_AddIyemToObject(root,"a",cJSON_CreateString("by9985");
//rendered=cJSON_Print(root);
//printf("json created:%s \n",rendered);
//c_JSON_Delete(root);
// 
}
//printf("end of task \n");
//vTaskDelete(NULL);
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
   vTaskDelay(1000/portTICK_PERIOD_MS); 
// Serial.println();unsigned char
 msg_queue=xQueueCreate(msg_queue_len,sizeof(char  ));
 xTaskCreatePinnedToCore(&jsonCreateTask,"jsonCreateTask",2048,NULL,10,NULL,0);
}

void loop() {
  // put your main code here, to run repeatedly:
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
