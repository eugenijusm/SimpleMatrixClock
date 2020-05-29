#include "Buttons.h"
#include "Config.h"

Buttons::Buttons(){
  pinMode(BUTTON_A_PIN, INPUT);
  pinMode(BUTTON_B_PIN, INPUT);
}

bool Buttons::IsButtonAPressed(){
  return digitalRead(BUTTON_A_PIN);
}

bool Buttons::IsButtonBPressed(){
  return digitalRead(BUTTON_B_PIN);
}
