#ifndef KEY_H
#define KEY_H

#include <Arduino.h>

//按键状态
typedef enum {

    KeyCheck = 0,
    KeyHigh = 1,
    KeyLow = 2,
    
}KeyState;


//按键类型

typedef enum {

    NullKey = 0,
    ShortKey = 1,
    LongKey = 2,

}KeyType;



#endif 
