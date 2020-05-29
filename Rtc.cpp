#include <Wire.h>

#include "Rtc.h"
#include "Config.h"

// Decimal part
// 255 = 0.75, 128 = 0.5, 64 = 0,25, other = 0.0
// TODO: if ever used, combine to float with Temperature
uint8_t temperatureDecimal;
const uint8_t temperatureOffset = 98; // 99 = -1 100 = 0 101 = +1

Rtc::Rtc(){}

void Rtc::Setup(){
  Wire.begin();
}

void Rtc::Set() {  
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);

  Wire.write(decToBcd(0));         // seconds
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

void Rtc::GetTemperature(){
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0x11);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_I2C_ADDRESS, 2);  //request - 2 bytes from RTC
  if (Wire.available()) {
    Temperature = Wire.read();
    temperatureDecimal = Wire.read();  

    // T correction
    Temperature = Temperature + temperatureOffset - 100;
  }
  else {  // error values
    Temperature = 0; 
    temperatureDecimal = 0;
  }
}

uint8_t Rtc::decToBcd(uint8_t val) {
  return((val / 10 * 16) + (val % 10));
}

uint8_t Rtc::bcdToDec(uint8_t val) {
  return((val / 16 * 10) + (val % 16));
}
