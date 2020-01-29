#include <LiquidCrystal.h>
#include "LedControl.h"
LedControl lc=LedControl(12,11,10,1);
LiquidCrystal lcd(13, 8, 7, 5, 4, 3); 
void setup() {
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  lcd.begin(16, 2);
  analogWrite(6,60);
    lcd.print("meniu");


}


void loop() {
  lcd.setCursor(1,0);
  lcd.print("meniu");
  delay(5000);
}
