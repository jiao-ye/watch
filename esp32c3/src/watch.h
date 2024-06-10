#ifndef _watch_H
#define _watch_H
#include <Arduino.h>
#include "space_photo.h"
#include "SPI.h"
#include "TFT_eSPI.h"
#include <vector>
#include "RX8010SJ.h"
#include "Time_Get.h"
#include <esp32-hal-adc.h>
#include "chinese.h"
#include "time.h"
extern int i;

void tft_init();
void watch();
void tft_time();
void get_rtctime();
void tft_ota();
void adc_init();
float adc_read();
#endif // DEBUG