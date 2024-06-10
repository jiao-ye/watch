#ifndef eye_functions_H
#define eye_functions_H

#include <Arduino.h>
#include "config.h"
#include <TFT_eSPI.h>
#include <SPI.h>

// TFT_eSPI tft;           
// TFT_eSprite img = TFT_eSprite(&tft);

#define BUFFER_SIZE 128 
#define BUFFERS 1      



#define SCREEN_X_START 0
#define SCREEN_X_END   SCREEN_WIDTH   // Badly named, actually the "eye" width!
#define SCREEN_Y_START 0
#define SCREEN_Y_END   SCREEN_HEIGHT  // Actually "eye" height

// A simple state machine is used to control eye blinks/winks:
#define NOBLINK 0       // Not currently engaged in a blink
#define ENBLINK 1       // Eyelid is currently closing
#define DEBLINK 2       // Eyelid is currently opening


extern uint8_t Mode_set1;
  
void initEyes(void);
void updateEye (void);
void eye_setup(void);
void tft_s();
void split( // Subdivides motion path into two sub-paths w/randimization
  int16_t  startValue, // Iris scale value (IRIS_MIN to IRIS_MAX) at start
  int16_t  endValue,   // Iris scale value at end
  uint32_t startTime,  // micros() at start
  int32_t  duration,   // Start-to-end time, in microseconds
  int16_t  range);

#endif 
