#include <stdint.h>

#include "Ldr.h"
#include "Config.h"

#define AVG_LIMIT 60

uint16_t AvgSum;  // 255*AVGLimit must fit in this type
uint8_t AvgCounter;
uint8_t AvgLdrLevel;
uint8_t BrightnessLevel;

Ldr::Ldr(){
  pinMode(LDR_PIN, INPUT);  
}

void Ldr::Measure(){
  if(AvgCounter >= AVG_LIMIT){
    AvgLdrLevel = AvgSum / AVG_LIMIT;
    BrightnessLevel = map(AvgLdrLevel, 0, 255, 0, 10 /* Matrix Max=15*/);
    AvgSum = 0;
    AvgCounter = 0;
  }
    
  AvgSum += analogRead(LDR_PIN);
  AvgCounter++;  
}

uint8_t Ldr::GetBrightness(){
  return BrightnessLevel; 
}
