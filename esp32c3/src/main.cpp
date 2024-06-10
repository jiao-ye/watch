#include <Arduino.h>
#include "watch.h"
#include "Time_Get.h"
#include "RX8010SJ.h"
#include "config.h"
#include "eye_functions.h"
#include "OTA.h"
#include "Preferences.h"

//修改
uint8_t Mode_set1, Mode_set2;

void TaskBone( void *pvParameters1 );
void TaskBtwo( void *pvParameters2 );

void setup(){
  Serial0.begin(115200); 
  pinMode(1,INPUT_PULLUP);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  analogWrite(7,80);
  iic_init();
  adc_init();
  xTaskCreatePinnedToCore(
    TaskBone
    ,  "Taskone"   // 任务名
    ,  8*1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
    ,  NULL 
    ,  1);
  xTaskCreatePinnedToCore(
    TaskBtwo
    ,  "Tasktwo"   // 任务名
    ,  8*1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
    ,  NULL 
    ,  0);
}

void TaskBone(void *pvParameters1)  // This is a task.
{
  (void) pvParameters1;
  while (1)
  {
    while(Mode_set1!=1){
      get_rtctime();
      vTaskDelay(1100);
    }
    
  }
  
}

void TaskBtwo(void *pvParameters2) 
{
  (void) pvParameters2;
  int i;
  while (1)
  {
    if (digitalRead(1) == LOW)
    {
      delay(20);
      if(digitalRead(1) == LOW){
        i=0;
        while (digitalRead(1) == LOW)
        {
          delay(20);
          if(i<=50) i++;

        }

        if(i>=50){
          Mode_set2=1;
        }
        else Mode_set1++;
      }  
          
    }
    if(Mode_set1 > 2) Mode_set1 = 0;
    vTaskDelay(10);
  }
  
}
void loop(){

   if (Mode_set1 == 0 &&Mode_set2 !=1) 
  {
    tft_init();
    while(Mode_set1 == 0 &&Mode_set2 !=1) watch();

      // if (RX_hour <=6 || (RX_hour>=23 && RX_min >=30))
      // {
      //   analogWrite(7,8);
      // }
      // else analogWrite(7,80);
      
    
  }
  else if (Mode_set1 == 1&&Mode_set2 !=1)
  {

    tft_time();  
    Time_Get();
    delay(1000);
    tft_init();
    Mode_set1 = 0;
    ESP.restart();
   
  }
  else if (Mode_set2 == 1)
  {
    
    otaBegin();
    tft_ota();
    while (Mode_set2 == 1)
    {
      otaRun();
    }
    Mode_set2=0;
  }

}
