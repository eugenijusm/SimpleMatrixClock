#ifndef Rtc_h
#define Rtc_h

class Rtc{
  public:
    Rtc();
    void Setup();
    void Get();
    void GetTemperature();
    void Set();
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hours;
    uint8_t DayOfWeek;    // TODO: rename to WeekDay and Day
    uint8_t DayOfMonth;
    uint8_t Month;
    uint8_t Year;
    uint8_t Temperature;  // Decimal part available inside, but not exposed

  private:
    uint8_t decToBcd(uint8_t val);
    uint8_t bcdToDec(uint8_t val);
};

#endif
