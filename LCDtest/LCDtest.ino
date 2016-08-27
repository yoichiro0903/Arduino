#include <LiquidCrystal.h>

const int out_pin = 12;

LiquidCrystal lcd(1,2,3,4,5,6,7); 
void setup() {
analogWrite(9, 80);
lcd.begin(16, 2);

}

void loop() {
lcd.setCursor(0,0);
lcd.print("hello world");
lcd.setCursor(0, 1);
lcd.print(millis()/1000);
tone(out_pin,523U,523U);
}
