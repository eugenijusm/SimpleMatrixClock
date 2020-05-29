#include <Wire.h>

#include "Rtc.h"
#include "Config.h"

uint8_t currentTemperatureH = 0;  // temperature in degC
uint8_t currentTemperatureL = 0; // 255 = 0.75, 128 = 0.5, 64 = 0,25, other = 0.0

Rtc::Rtc(){}

void Rtc::Setup(){
  Wire.begin();
}

void Rtc::Set() {  
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); //set 0 to first register

  Wire.write(decToBcd(0));    // seconds
  Wire.write(decToBcd(Minutes));
  Wire.write(decToBcd(Hours));
  Wire.write(decToBcd(DayOfWeek)); // 1=su, 2=mo, 3=tu
  Wire.write(decToBcd(DayOfMonth));
  Wire.write(decToBcd(Month));
  Wire.write(decToBcd(Year));
  Wire.endTransmission();
}

void Rtc::Get() {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);  //request - 7 bytes from RTC
  Seconds = bcdToDec(Wire.read() & 0x7f);
  Minutes = bcdToDec(Wire.read());
  Hours = bcdToDec(Wire.read() & 0x3f);
  DayOfWeek = bcdToDec(Wire.read());
  DayOfMonth = bcdToDec(Wire.read());
  Month = bcdToDec(Wire.read());
  Year = bcdToDec(Wire.read());
}

uint8_t Rtc::decToBcd(uint8_t val) {
  return((val / 10 * 16) + (val % 10));
}

uint8_t Rtc::bcdToDec(uint8_t val) {
  return((val / 16 * 10) + (val % 16));
}
