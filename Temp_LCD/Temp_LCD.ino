#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int a_pin = 0;

void setup(){
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("LM");
}

void loop(){
  int i;
  int data;
  int summary;
  float t;
  int t1;
  int t2;
  float input_avg;
  
  summary = 0;
  for (i=0;i<50;i++){
    data = analogRead(a_pin);
    summary = summary + data;
    delay(2);
  }
  
  input_avg = (float)summary / 50.0;
  t = input_avg / 1024.0 * 5.0 * 100.0;
  t1 = (int)t;
  t2 = (int)(t * 10.0) - t1 * 10;
  lcd.setCursor(0,1);
  lcd.print(t1);
  lcd.print(t2);
  delay(1000);
}
