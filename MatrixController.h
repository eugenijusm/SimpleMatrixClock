#ifndef MatrixController_h
#define MatrixController_h

class MatrixController
{
  public:
    MatrixController();
    void Setup();
    void DrawDigit(byte adr, byte charIndex);
    void DrawInt(uint8_t row, uint8_t value);
    void DrawChar(char character, uint8_t row, uint8_t column);
    void SetBrightness(uint8_t brightness);
    uint8_t GetBrightness();
};

#endif
