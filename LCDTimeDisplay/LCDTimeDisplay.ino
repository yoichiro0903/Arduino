#include <Time.h>
#include <LiquidCrystal.h>

//LEDの出力ピン指定
const int out_pin = 12;
const int button = 11;
int val = 0;
int state = 0;

LiquidCrystal lcd(8,2,3,4,5,6,7); 

void setup() {
  
  lcd.begin(16, 2);
  analogWrite(9, 80);
  
  setTime(0);
  //setTmie(sec,min,hour,day,month,year);
  pinMode(out_pin, OUTPUT); //arduinoの出力がLEDだと定義
  pinMode(button, INPUT); //button
  
  Serial.begin(9600);


}

void loop() {
  char out_str[10];
  char out_str2[10];
  
  if(state == 0){
  sprintf(out_str,"%04d/%02d/%02d",year(),month(),day());
  lcd.setCursor(0,0);
  lcd.print(out_str);
  sprintf(out_str2,"%02d/%02d/%02d",hour(),minute(),second());
  lcd.setCursor(0, 1);
  lcd.print(out_str2);
  Serial.println(out_str);
  Serial.println(out_str2);
  }
  //アラームの鳴る秒数を指定
  int alarm_s;
  alarm_s = second();
  
  val = digitalRead(button);
  //
  if(alarm_s > 10 && state == 0){
  digitalWrite(out_pin,HIGH);
  }
  if (val == LOW){
    state = 1 - state;  
  }
  
  if(state == 1){
  digitalWrite(out_pin,LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("alarm stopped");
  sprintf(out_str2,"%02d/%02d/%02d",hour(),minute(),second());
  lcd.setCursor(0, 1);
  lcd.print(out_str2);

  }
  
  delay(1000);
}
