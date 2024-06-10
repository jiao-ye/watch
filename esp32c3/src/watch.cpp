#include "watch.h"


#define DEG2RAD 0.0174532925
TFT_eSPI tft1 = TFT_eSPI(240,240);
TFT_eSprite clk = TFT_eSprite(&tft1);

const uint16_t *a[]={people1,people2,people3,people4,people6,people7,people8,people9,people10,people11,people12,people13,people14,people15,people16,people17,people18,people19,people20,people21,people22,people23,people24,people25,people26,people27,people28};
int32_t Sum_location[2][12]={{20,34,49,63,78,92,107,121,136,150,165,179},{15,10,0,-5,-10,-15,-15,-10,-5,0,10,15}};
#define time 50

tm timeinfo;


void adc_init(){

    adcAttachPin(0);
    analogReadResolution(16);
    
}

float adc_read(){

    return ((analogRead(0)*3.3)/65535/33*(10+33));
}

void get_rtctime(){
      Time_Read_RX8010(&timeinfo);
      Serial0.print(timeinfo.tm_year);
      Serial0.print(":");
      Serial0.print(timeinfo.tm_mon);
      Serial0.print(":");
      Serial0.print(timeinfo.tm_mday);
      Serial0.print(":");
      Serial0.print(timeinfo.tm_hour);
      Serial0.print(":");
      Serial0.print(timeinfo.tm_min);
      Serial0.print(":");
      Serial0.print(timeinfo.tm_sec);
      Serial0.print(":");
      Serial0.println(timeinfo.tm_wday);
}



//屏幕初始化
void tft_init(){
    tft1.init();
    tft1.setRotation(1);  
    tft1.fillScreen(TFT_WHITE);
}

//太空人渲染函数
void Space_People(){
    for (int i = 0; i < 27; i++)
    {
        clk.pushImage(90,110,75,60,a[i]);
        delay(time);
    }
}

//基本框架渲染
void Base(){
    tft1.drawFastHLine(0,49,240,TFT_BLACK);
    tft1.drawFastHLine(0,48,240,TFT_BLACK);
    tft1.drawFastHLine(0,180,240,TFT_BLACK);
    tft1.drawFastHLine(0,181,240,TFT_BLACK);    
}

//时间渲染
void Time(){

    // 时
    if (timeinfo.tm_hour<10)
    {
        clk.createSprite(32, 64);//创建窗口
        clk.fillSprite(TFT_WHITE);   //填充率
        clk.setTextColor(TFT_BLACK);
        clk.setTextFont(7);
        clk.setTextSize(1);
        clk.println(timeinfo.tm_hour);
        clk.pushSprite(75,55);  //窗口位置
        clk.deleteSprite();

        clk.createSprite(78, 64);//创建窗口
        clk.fillSprite(TFT_WHITE);   //填充率
        clk.pushSprite(0,55);  //窗口位置
        clk.deleteSprite();             
    }
    else
    {
        clk.createSprite(64, 64);//创建窗口
        clk.fillSprite(TFT_WHITE);   //填充率
        clk.setTextColor(TFT_BLACK);
        clk.setTextFont(7);
        clk.setTextSize(1);
        clk.println(timeinfo.tm_hour);
        clk.pushSprite(45,55);  //窗口位置
        clk.deleteSprite();        
    }
    

    //冒号
    clk.createSprite(13, 60);//创建窗口
    clk.fillSprite(TFT_WHITE);   //填充率
    clk.setTextColor(TFT_BLACK);
    clk.setTextFont(7);
    clk.setTextSize(1);
    clk.println(":");
    clk.pushSprite(112,55);  //窗口位置
    clk.deleteSprite();
    //分
    if (timeinfo.tm_min<10)
    {
        clk.createSprite(32, 64);//创建窗口
        clk.fillSprite(TFT_WHITE);   //填充率
        clk.setTextColor(TFT_BLACK);
        clk.setTextFont(7);
        clk.setTextSize(1);
        clk.println(0);
        clk.pushSprite(125,55);  //窗口位置
        clk.deleteSprite(); 

        clk.createSprite(32, 64);//创建窗口
        clk.fillSprite(TFT_WHITE);   //填充率
        clk.setTextColor(TFT_BLACK);
        clk.setTextFont(7);
        clk.setTextSize(1);
        clk.println(timeinfo.tm_min);
        clk.pushSprite(157,55);  //窗口位置
        clk.deleteSprite();   
    }
    else
    {
        clk.createSprite(64, 64);//创建窗口
        clk.fillSprite(TFT_WHITE);   //填充率
        clk.setTextColor(TFT_BLACK);
        clk.setTextFont(7);
        clk.setTextSize(1);
        clk.println(timeinfo.tm_min);
        clk.pushSprite(125,55);  //窗口位置
        clk.deleteSprite();        
    }

    clk.createSprite(80,16);//创建窗口
    clk.fillSprite(TFT_WHITE);   //填充率
    clk.setTextColor(TFT_BLACK);
    clk.loadFont(num_16);
    clk.print(timeinfo.tm_mon);
    clk.print("-");
    clk.print(timeinfo.tm_mday);
    clk.pushSprite(180,140);  //窗口位置
    clk.unloadFont();
    clk.deleteSprite();  

}

//太阳与月亮
void Sun(){
    int x;
    clk.createSprite(240, 48);//创建窗口
    clk.fillSprite(TFT_WHITE);   //填充率
    clk.pushSprite(0,0);  //窗口位置
    clk.deleteSprite();  
    if (timeinfo.tm_hour >=19 || timeinfo.tm_hour <=7)
    {
        x=timeinfo.tm_hour-19;
        tft1.pushImage(Sum_location[0][x],Sum_location[1][x],45,42,Moon_Image);
        Base();               
    }
    else 
    {
        x=timeinfo.tm_hour-7;
        //白天
        tft1.pushImage(Sum_location[0][x],Sum_location[1][x],45,42,Sun_Image);
        Base();         
    }
 
             
}

//文字渲染
void words(){

    clk.createSprite(48,24);//创建窗口
    clk.fillSprite(TFT_WHITE);   //填充率
    clk.setTextColor(TFT_BLACK);
    clk.loadFont(chinese_24);
     switch (timeinfo.tm_wday)
      {
        case 1: clk.print("周日");break;
        case 2: clk.print("周一");break;
        case 4: clk.print("周二");break;
        case 8: clk.print("周三");break;    
        case 10: clk.print("周四");break;  
        case 20: clk.print("周五");break;  
        case 40: clk.print("周六");break;  
      default:
        break;
      }  
    clk.pushSprite(180,115);  //窗口位置
    clk.unloadFont();
    clk.deleteSprite();

    clk.createSprite(96,50);//创建窗口
    clk.fillSprite(TFT_WHITE);   //填充率
    clk.setTextColor(TFT_BLACK);
    clk.loadFont(chinese_24);
    
    if (timeinfo.tm_mon == 11 && timeinfo.tm_mday== 4)
    {
        clk.print("生日快乐");
    }
    else if (timeinfo.tm_mon == 1 && timeinfo.tm_mday == 1)
    {
        clk.print("元旦快乐");
    }
    else
    {
        if (timeinfo.tm_hour>=22 || timeinfo.tm_hour<=7)
        {
            clk.print("注意休息");
        }
        else if ((timeinfo.tm_hour>=9 && timeinfo.tm_hour<=12) || (timeinfo.tm_hour>=14 && timeinfo.tm_hour<=17))
        {
            clk.print("元气满满");
        }
        else
        {
            clk.print("保持开心");
        }
        
    }

    clk.pushSprite(80,200);  //窗口位置
    clk.unloadFont();
    clk.deleteSprite();  
    
}

void electricity(){

    if (timeinfo.tm_mon == 11 && timeinfo.tm_mday == 4) 
    {
        clk.pushImage(15,100,32,48,cake);
    }
    else
    {
        clk.pushImage(15,100,32,48,flower);花
    }
    clk.createSprite(40,16);//创建窗口
    clk.fillSprite(TFT_WHITE);   //填充率
    clk.setTextColor(TFT_BLACK);
    clk.loadFont(num_16);
    clk.print(adc_read());
    clk.pushSprite(20,160);  //窗口位置
    clk.unloadFont();
    clk.deleteSprite();  
}

void watch(){
    Base();
    Time();
    words();
    Sun();   
    electricity();
    Space_People();
}

/********************对时表盘**************************/

void tft_time(){

    tft1.fillScreen(TFT_BLACK);
    tft1.pushImage(70,20,100,100,wifi_photo);

    clk.createSprite(200,120);//创建窗口
    clk.fillSprite(TFT_BLACK);   //填充率
    clk.setTextColor(TFT_WHITE);
    clk.loadFont(chinese_20);
    if (WiFi.status() != WL_CONNECTED)
    {
        clk.println("请开启热点");
        clk.println("ssid:table");
        clk.println("pswd:88888888");
    }
    else
    {
        clk.println("对时中....");
    }
    
    
    clk.pushSprite(70,110);  //窗口位置
    clk.unloadFont();
    clk.deleteSprite();  
}

/****************ota表盘***************/

void tft_ota(){
    tft1.fillScreen(TFT_BLACK);
    clk.createSprite(200,120);//创建窗口
    clk.fillSprite(TFT_BLACK);   //填充率
    clk.setTextColor(TFT_WHITE);
    clk.loadFont(num_16);
    clk.printf("IP ");
    clk.println(WiFi.localIP());
    clk.println("User:jiaoye");
    clk.printf("Pswd:jiaoye");
    clk.pushSprite(50,80);
    clk.unloadFont();
    clk.deleteSprite();
}