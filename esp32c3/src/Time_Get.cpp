#include "Time_Get.h"

const char *ssid = "table";    
const char *password = "88888888"; 

#define NTP2  "ntp1.aliyun.com"
#define NTP1  "1.cn.pool.ntp.org"
#define NTP3  "ntp3.aliyun.com"

const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;

struct tm timeinfo1;


int Time_sec,Time_min,Time_hour,Time_week,Time_day,Time_month,Time_year;



void Time_Get(){

    WiFi.begin(ssid, password);
    WiFi.setTxPower(WIFI_POWER_5dBm);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial0.print(".");
    }
    Serial0.println("WiFi connected!");
    delay(200);
    // 从网络时间服务器上获取并设置时间
    // 获取成功后芯片会使用RTC时钟保持时间的更新
    configTime(gmtOffset_sec, daylightOffset_sec, NTP1, NTP2,NTP3);
    while (!getLocalTime(&timeinfo1))
    { 
      Serial0.println("Failed to obtain time");
      Serial0.println("rest to obtain time");
      
    }
    Time_write(timeinfo1);
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial0.println("WiFi disconnected!");
    Serial0.println(&timeinfo1, "%F %T %A"); // 格式化输出
    
}

void getTimertc(tm *time){
    getLocalTime(&timeinfo1);
    *time = timeinfo1; 
}
