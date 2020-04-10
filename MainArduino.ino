#include "ArduinoLcd.h"

Lcd lcd;
void setup() {
  lcd.begin();
  lcd.print("Hello, World");
  lcd.setCursor(1, 0);
  lcd.print("Ivan Biljan");
  lcd.blink();
}

void loop() {
}
