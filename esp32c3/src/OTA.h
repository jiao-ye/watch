#ifndef OTA_H
#define OTA_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

void otaBegin();
void otaRun();

#endif 
