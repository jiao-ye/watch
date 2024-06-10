#ifndef _Time_Get_h
#define _Time_Get_h


#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
#include "RX8010SJ.h"

void Time_Get();
void getTimertc(tm *time);
extern int Time_sec, Time_min, Time_hour,Time_week,Time_day,Time_month,Time_year;


#endif 