#include <LiquidCrystal.h>

#include <DateTimeStrings.h>

#include <DateTime.h>

LiquidCrystal lcd = LiquidCrystal(12,11,10,5,4,3,2);
time_t prevtime;

void setup() {
  prevtime = DateTime.makeTime(0,0,9,17,1,2009);
  DateTime.sync(prevtime);
}

void loop() {
  while( prevtime == DateTime.now() ){
    delay(100);
  }
  DateTime.available();
  digitalClockDisplay();
}

void digitalClockDisplay(){
  lcd.setCursor(0,0);
  lcd.print(DateTimeStrings.dayStr(DateTime.DayofWeek));
  lcd.print(" ");
  lcd.print(DateTimeStrings.monthStr(DateTime.Month));
  lcd.print(" ");
  lcd.print(DateTime.Day,DEC);
  lcd.print(" ");
  lcd.print(DateTime.Year+1900,DEC);

  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.print(DateTime.Hour,DEC);
  printDigits(DateTime.Minute);
  printDigits(DateTime.Second);
}

void printDigits(byte digits){
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits,DEC);
}
