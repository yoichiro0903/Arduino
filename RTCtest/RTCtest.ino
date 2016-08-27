#include <Wire.h>

#include <RTC8564.h>

void setup()
{
  Serial.begin(9600);
  Rtc.begin();
  byte date_and_time[7]; 
  date_and_time[0] = 0x59;	// 59秒 
  date_and_time[1] = 0x08;	// 08分 
  date_and_time[2] = 0x15;	// 15時 
  date_and_time[3] = 0x24;	// 24日 
  date_and_time[4] = 0x06;	// 日曜日(00)土曜日(06) 
  date_and_time[5] = 0x08;	// 8月 
  date_and_time[6] = 0x13;	// 2000 + 13 = 2013 
  Rtc.sync(date_and_time); 
}

void loop()
{
  delay(1000);
  Rtc.available();
  
  Serial.print(0x2000+Rtc.years(),HEX);
  Serial.print("/");
  Serial.print(Rtc.months(),HEX);
  Serial.print("/");
  Serial.print(Rtc.days(),HEX);
  Serial.print(" ");
  Serial.print(Rtc.hours(),HEX);
  Serial.print(":");
  Serial.print(Rtc.minutes(),HEX);
  Serial.print(":");
  Serial.println(Rtc.seconds(),HEX);
}
