#include <LedControl.h>

#include "MatrixController.h"
#include "Font.h"
#include "Config.h"


LedControl leds = LedControl(LEDS_DIN_PIN, LEDS_CLK_PIN, LEDS_CS_PIN, MATRICES_COUNT);
uint8_t Brightness;

MatrixController::MatrixController(){}

void MatrixController::Setup(){
  for (uint8_t address = 0; address<MATRICES_COUNT; address++) {
    leds.shutdown(address, false);      //powersaving
    leds.setIntensity(address, 0);  // initial brightness = 0
    leds.clearDisplay(address);
  }  
}

void MatrixController::SetBrightness(uint8_t brightness){
   Brightness = brightness;
   for (uint8_t address = 0; address<MATRICES_COUNT; address++) {
    leds.setIntensity(address, Brightness);
   }   
}

void MatrixController::DrawDigit(uint8_t adr, uint8_t charIndex) {
  for (uint8_t i = 0; i < 8; i++) {    
    uint8_t row = (fontNumbers[charIndex] >> i * 8) & 0xFF;  //just some magic - extract one row from all symbol
    leds.setRow(adr, 7-i /*use i to flip symbols upside-down*/, /*ByteRevers(row)*/ row);
  }
}

void MatrixController::DrawInt(uint8_t row, uint8_t value){
  DrawDigit(MATRICES_PER_LINE * row, (value / 10));
  DrawDigit((MATRICES_PER_LINE * row) + 1, (value % 10));  
}

// TODO: probably can be unified with DrawDigit by passing in font array pointer
void MatrixController::DrawChar(char character, uint8_t row, uint8_t column)
{
  uint8_t adr = (row * 2) + column;
  uint8_t charIndex = 0;
  if(character >= 65 && character <= 90){
    charIndex = character - 65;
  }
  else if (character >= 97 && character <= 122){
    charIndex = character - 97 + 26; // + lower case offset    
  }
  #ifdef DEBUG
      Serial.print(F("Chr idx:"));
      Serial.println(charIndex);
  #endif
  for (uint8_t i = 0; i < 8; i++) {    
    uint8_t matrixRow = (fontCharacters[charIndex] >> i * 8) & 0xFF;  //just some magic - extract one row from all symbol
    leds.setRow(adr, 7-i /*use i to flip symbols upside-down*/, /*ByteRevers(row)*/ matrixRow);
  }
}

uint8_t MatrixController::GetBrightness(){
  return Brightness;
}
/*
 byte ByteRevers(byte in) {
 //font rotating
  if ((rotateFont1 == 1 && verticalMode == 0) || (rotateFont1 == 0 && verticalMode == 1)) {
    //do not rotate
    return(in);
  }

  byte out;
  out = 0;
  if (in & 0x01) out |= 0x80;
  if (in & 0x02) out |= 0x40;
  if (in & 0x04) out |= 0x20;
  if (in & 0x08) out |= 0x10;
  if (in & 0x10) out |= 0x08;
  if (in & 0x20) out |= 0x04;
  if (in & 0x40) out |= 0x02;
  if (in & 0x80) out |= 0x01;
  return(out);
}
*/
