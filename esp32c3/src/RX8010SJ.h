#ifndef _RX8010SJ_H
#define _RX8010SJ_H

#include <Arduino.h>
#include <Wire.h>
#include "Time_Get.h"

#define Write 0x64
#define Read  0x65
#define SEC   0x10
#define MIN   0x11
#define HOUR  0x12
#define WEEk  0x13
#define DAY   0x14
#define MONTH 0x15
#define YEAR  0x16


void iic_init();
void Time_Read_RX8010(tm *time1);
void Time_write(tm time2);
void time_init();

#endif 
