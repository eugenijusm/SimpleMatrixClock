// Based on ideas from https://github.com/mylms/Arduino-Matrix-Clock

#include "Config.h"
#include "MatrixController.h"
#include "Rtc.h"
#include "Buttons.h"
#include "Ldr.h"
#include "SystemState.h"

MatrixController matrix = MatrixController();
Rtc rtc = Rtc();
Buttons buttons = Buttons();
Ldr ldr = Ldr();
uint8_t ldrBrightness;

SystemState systemState = DISPLAY_TIME;
unsigned long currentMillis;
unsigned long refreshMillis;

uint8_t periodCounter;
#define SYSTEM_TICK 250 // ms
#define MAX_PERIOD 12   // every 3s, when system_tick = 250ms

uint8_t daysInMonth = 1;

void setup() {
  #ifdef DEBUG
    Serial.begin(9600);
  #endif  
  matrix.Setup();
  rtc.Setup();  
}

void loop() {
  currentMillis = millis();

  if (currentMillis >= refreshMillis){
    
    switch(systemState){
      case DISPLAY_TIME:
        if (periodCounter == 0){
          ldr.Measure();
          ldrBrightness = ldr.GetBrightness();
          if(matrix.GetBrightness() != ldrBrightness){
            matrix.SetBrightness(ldrBrightness);
            Serial.println(ldrBrightness);
          }        
          rtc.Get();        
          matrix.DrawInt(0, rtc.Hours);
          matrix.DrawInt(1, rtc.Minutes);          
  
          if(buttons.IsButtonAPressed()){
            #ifdef DEBUG
            Serial.println(F("State => Set hours"));
            #endif            
            matrix.DrawChar('H', 0, 0);
            matrix.DrawChar('r', 0, 1);
            systemState = SET_HOURS;            
          }
  
          if(buttons.IsButtonBPressed()){
            #ifdef DEBUG
            Serial.println(F("State => Show TEMPERATURE"));
            #endif
            systemState = DISPLAY_TEMPERATURE;
          }
        }
        break;
      case DISPLAY_TEMPERATURE:
        // TODO: IMPLEMENT
        systemState = DISPLAY_TIME;        
        break;
      case SET_HOURS:
        matrix.DrawInt(1, rtc.Hours);        
        
        if(buttons.IsButtonAPressed() && periodCounter == MAX_PERIOD-1){
          matrix.DrawChar('M', 0, 0);
          matrix.DrawChar('i', 0, 1);
          systemState = SET_MINUTES;          
        }
        if(buttons.IsButtonBPressed()){
          if(rtc.Hours == 23){            
            rtc.Hours = 0;
          }
          else{
            rtc.Hours++;            
          }          
        }
        break;      
      case SET_MINUTES:
        matrix.DrawInt(1, rtc.Minutes);

        if(buttons.IsButtonAPressed() && periodCounter == MAX_PERIOD-1){
          matrix.DrawChar('Y', 0, 0);
          matrix.DrawChar('r', 0, 1);
          systemState = SET_YEAR;
        }
        
        if(buttons.IsButtonBPressed()){
          if(rtc.Minutes == 59){
            rtc.Minutes = 0;
          }
          else{
            rtc.Minutes++;            
          }          
        }
        break;
      case SET_YEAR:
        matrix.DrawInt(1, rtc.Year);        
        
        if(buttons.IsButtonAPressed() && periodCounter == MAX_PERIOD-1){
          matrix.DrawChar('M', 0, 0);
          matrix.DrawChar('o', 0, 1);
          systemState = SET_MONTH;
        }
        
        if(buttons.IsButtonBPressed()){
          if(rtc.Year == 30){
            rtc.Year = 20;
          }
          else{
            rtc.Year++;          
          }          
        }
        break;
      case SET_MONTH:
        matrix.DrawInt(1, rtc.Month);

        if(buttons.IsButtonAPressed() && periodCounter == MAX_PERIOD-1){          
          matrix.DrawChar('D', 0, 0);
          matrix.DrawChar('a', 0, 1);
          daysInMonth = GetDaysInMonth();
          systemState = SET_DAY;
        }
        
        if(buttons.IsButtonBPressed()){
          if(rtc.Month == 12){
            rtc.Month = 1;
          }
          else{
            rtc.Month++;            
          }          
        }
        break;
      case SET_DAY:
        matrix.DrawInt(1, rtc.DayOfMonth);        
        
        if(buttons.IsButtonAPressed() && periodCounter == MAX_PERIOD-1){
          matrix.DrawChar('W', 0, 0);
          matrix.DrawChar('D', 0, 1);
          systemState = SET_WEEKDAY;
        }
        
        if(buttons.IsButtonBPressed()){
          if(rtc.DayOfMonth == daysInMonth){
            rtc.DayOfMonth = 1;
          }
          else{
            rtc.DayOfMonth++;          
          }          
        }
        break;
      case SET_WEEKDAY:
        matrix.DrawInt(1, rtc.DayOfWeek);

        if(buttons.IsButtonAPressed() && periodCounter == MAX_PERIOD-1){
          rtc.Set();
          matrix.DrawChar('O', 1, 0);
          matrix.DrawChar('K', 1, 1);
          systemState = DISPLAY_TIME;
          periodCounter = 0;
        }
        
        if(buttons.IsButtonBPressed()){
          if(rtc.DayOfWeek == 7){
            rtc.DayOfWeek = 1;
          }
          else{
            rtc.DayOfWeek++;            
          }          
        }
        break;
    }
    
    periodCounter++;    
    if(periodCounter >= MAX_PERIOD){
      periodCounter = 0;
    }

    refreshMillis = currentMillis + SYSTEM_TICK;
  }
}

uint8_t GetDaysInMonth(){
  if(rtc.Month == 1 || rtc.Month == 3 || rtc.Month == 5 || rtc.Month == 7 || rtc.Month == 8 || rtc.Month == 10 || rtc.Month == 12){
    return 31;
  }
  if(rtc.Month == 4 || rtc.Month == 6 || rtc.Month == 9 || rtc.Month == 11){
    return 30;
  }
  if(rtc.Month == 2){
    if(rtc.Year != 20 && rtc.Year != 24 && rtc.Year != 28){
      return 28;
    }
    return 29;
  }
}
