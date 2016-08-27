#include "Arduino.h"
#include "Wire.h"
#include <LiquidCrystal.h>

//LCDのピン指定、5V(LCD 1)、GND(2)、コントラスト(3)
//ここから指定RS(4)、R/W(5)、E(6)、DATA BIT4(11)、５(12)、6(13)、7(14)
LiquidCrystal lcd(8,2,3,4,5,6,7); 

#define RTC_ADDRESS (0xa2 >> 1)
#define TMP_ADDRESS (0x80 >> 1)

int rtc[16];
float tmp[5];
int LED = 13;
String alarm_sec;
int alarm_sec_int;
//温度センサーの入力ピンをアナログ０番に指定
int a_pin = 0;
//アラームモードの切り替えボタン
int a_button = 12;
int alarm_switch;
int state = 0;
int old_val;

//alarm時刻設定用変数
int count;
int alarm_set = 11;
int alarm_set_min = 10;
int alarm_set_val;
int alarm_set_min_val;
int alarm_min;
int hour_zero;
int min_zero;
//char *alarm_h_char[20];
//int alarm_h_int;
byte alarm_min_dec = 56;
byte alarm_min_bcd;
byte alarm_hour_dec = 20;
byte alarm_hour_bcd;

////////////////////SETUP/////////////////////////


void setup() {
 
 Serial.begin(9600);
 Serial.println("Initializing RTC unit...Please wait...");
 delay(1000);
 
 //LED
 pinMode(LED, OUTPUT);
 
 //alarm button
 pinMode(a_button, INPUT);
 pinMode(alarm_set, INPUT);
 
 //LCD
 analogWrite(9, 80);
 lcd.begin(16, 2); 
 
 // Bus-MasterとしてI2Cを開始。
 Wire.begin();
 
 // RTCへの送信準備開始。
 Wire.beginTransmission(RTC_ADDRESS);
 // はじめにアドレス0x00を指定。次からはオートインクリメント。
 Wire.write(0x00);
 // コントロールレジスタ1。
 Wire.write(0x00);
 // コントロールレジスタ2。0x02でタイマー設定
 Wire.write(0x00);
 // 秒レジスタ。とりあえず、55秒。
 Wire.write(0x55);
 // 分レジスタ。とりあえず、55分。
 Wire.write(0x55);
 // 時レジスタ。とりあえず、20時。
 Wire.write(0x20);
 // 日レジスタ。とりあえず、23日。
 Wire.write(0x07);
 // 曜日レジスタ。とりあえず、月曜日。
 Wire.write(0x06);
 // 月レジスタ。とりあえず、7月。
 Wire.write(0x09);
 // 年レジスタ。取りあえず、12年。
 Wire.write(0x13);
 
 // アラーム設定。
 Wire.write(0x00);
      //minutes alarm = 0x21
 Wire.write(0x00);
      //hours alarm = 0x12
 Wire.write(0x00);
      //days alarm = 0x25
 Wire.write(0x00);
      //weekdays alarm = 0x04 (Thursday) 
 
 // Clock出力設定。1Hz。
 Wire.write(0x83);
 // キューの送信。通信終了。
 Wire.endTransmission(); 
 
 
 
  
  
 char *alarm_h_char;
 //alarm
 Wire.beginTransmission(RTC_ADDRESS);
 Wire.write(0x01);
 Wire.write(0x02);
 Wire.endTransmission();
 
 Wire.beginTransmission(RTC_ADDRESS);
 Wire.write(0x09);
 
 byte alarm_min_bcd = Dec2Bcd(alarm_min_dec);
 byte alarm_hour_bcd = Dec2Bcd(alarm_hour_dec);
 //alarm 分設定（or 0x80で無効）
 Wire.write(alarm_min_bcd);
 //alarm 時間設定（or 0x80で無効）
 Wire.write(alarm_hour_bcd);
 //alarm 日にち設定（or 0x80で無効）
 Wire.write(0x02 | 0x80);
 //alarm weekday設定（or 0x80で無効）
 Wire.write(0x02 | 0x80);
 Wire.endTransmission();
  
 delay(20);
 Serial.println("RTC Initialized.");
}



///////////////////////LOOP////////////////////////



void loop() {
 
 // RTCとのI2C通信開始。
 Wire.beginTransmission(RTC_ADDRESS);
 // レジスタアドレス0x00を指定。
 Wire.write(0x00);
 // キューの送信。
 Wire.endTransmission();
 
 // データ要求。
 Wire.requestFrom(RTC_ADDRESS, 16);
 // データ受信。
 for (int i = 0; i < 16; i++) {
  while (Wire.available() == 0);
  rtc[i] = Wire.read();
 }
 
 // （西暦）年。以下、数値類はBCD。
 Serial.print("20");
 Serial.print(rtc[8], HEX);
 Serial.print("/");
 // 月。下位9bit。
 Serial.print(rtc[7] & 0x1f, HEX);
 Serial.print("/");
 // 日。下位10bit。
 Serial.print(rtc[5] & 0x3f, HEX);
 Serial.print(" ");
 // 曜日。
 switch (rtc[6] & 0x07) {
  case 0:
   Serial.print("Sun");
   break;
  case 1:
   Serial.print("Mon");
   break;
  case 2:
   Serial.print("Tue");
   break;
  case 3:
   Serial.print("Wed");
   break;
  case 4:
   Serial.print("Thr");
   break;
  case 5:
   Serial.print("Fri");
   break;
  case 6:
   Serial.print("Sat");
   break;
  default:
   Serial.print("   ");
   break;
 }
 Serial.print("   ");
 // 時。時標示 上位２ビット不要（マスクすること）
 Serial.print(rtc[4] & 0x3f, HEX);
 Serial.print(":");
 // 分。二進数表示で111111でマスクするため（60が111100で表されるから）
 Serial.print(rtc[3] & 0x7f, HEX);
 Serial.print(":");
 // 秒。bit0,1,2,3（１から９）で1の位、bit4,5,6（１から５）で10の位を表現するので、上位1bitは不要
 Serial.print(rtc[2] & 0x7f, HEX);
 Serial.println();
 
 
 //alarm_sec = String(rtc[2] & 0x7f, HEX); 
 //alarm_sec_int = alarm_sec.toInt();
 
 
 //アラームストップ設定（rtc[3]は分設定）
 if(rtc[3] == 0x57){
   //アラームストップ命令送信
   Wire.beginTransmission(RTC_ADDRESS);
   Wire.write(0x01);
   Wire.write(rtc[1] & 0xf5);
   Wire.endTransmission();
 }
 
 
 //  //温度センサーの計算
  
  //for用の変数
  int i;
  //温度センサーの一回の電圧読み値
  int data;
  //５０回の合計値（電圧）
  int summary;
  //５０個の平均値（電圧）
  float input_avg;
  //温度の値（温度）
  float t_value;
  
  summary = 0;
  //５０回の高速測定平均計算
  for(i=0; i<50; i++){
    data = analogRead(a_pin);
    summary = summary + data;
    delay(2);
  }
  
  //平均算出
  input_avg = (float)summary/50.0;
  //電圧を温度に変換
  t_value = (input_avg / 1024.0 * 5.0 * 1000 - 600) / 10;
  Serial.println("Temp : ");
  Serial.println(t_value);

 //LCD
 lcd.setCursor(0,0);
 lcd.print("20");
 lcd.print(rtc[8], HEX);
 lcd.print("/");
 // 月。下位9bit。
 lcd.print(rtc[7] & 0x1f, HEX);
 lcd.print("/");
 // 日。下位10bit。
 lcd.print(rtc[5] & 0x3f, HEX);
 lcd.print("/");
 // 曜日。
 switch (rtc[6] & 0x07) {
  case 0:
   lcd.print("Sun");
   break;
  case 1:
   lcd.print("Mon");
   break;
  case 2:
   lcd.print("Tue");
   break;
  case 3:
   lcd.print("Wed");
   break;
  case 4:
   lcd.print("Thr");
   break;
  case 5:
   lcd.print("Fri");
   break;
  case 6:
   lcd.print("Sat");
   break;
  default:
   lcd.print("   ");
   break;
 }
 // 時。時標示 上位２ビット不要（マスクすること）
 lcd.setCursor(0, 1);
 //lcd.print("Temp:");
 //lcd.print(t_value);
 //lcd.print("  ");
 
 lcd.print(rtc[4] & 0x3f, HEX);
 lcd.print(":");
 // 分。二進数表示で111111でマスクするため（60が111100で表されるから）
 lcd.print(rtc[3] & 0x7f, HEX);
 lcd.print(":");
 // 秒。bit0,1,2,3（１から９）で1の位、bit4,5,6（１から５）で10の位を表現するので、上位1bitは不要
 if(rtc[2] < 0x10){
 lcd.setCursor(6,1);
 lcd.print("0");
 lcd.print(rtc[2] & 0x7f, HEX);
 }
 if(rtc[2] >= 0x10){
 lcd.setCursor(6,1);
 lcd.print(rtc[2] & 0x7f, HEX);
 }
 
 
 //alarm mode switch
 alarm_switch = digitalRead(a_button);
 if(alarm_switch == LOW && old_val == HIGH){
   state = 1 - state;
 }
 old_val = alarm_switch;
 
 if(state == 1){
   digitalWrite(LED,HIGH);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Alarm set");
   lcd.setCursor(0,1);
   
   
   //アラームの時刻設定ボタンが押された場合
   alarm_set_val = digitalRead(alarm_set);
   if(alarm_set_val == LOW){
     count++;
     if(count > 23){
     count = 0;
     }     
   }
     if(count < 10 ){
     hour_zero = 1;
     } else {
     hour_zero = 0;
     }
     
       
     if(hour_zero == 1){
       lcd.print("0");
     } else {
       lcd.setCursor(0,1);     
     }     
     lcd.print(count);
     lcd.print(":");
   
   //アラームの分設定
   alarm_set_min_val = digitalRead(alarm_set_min);
   if(alarm_set_min_val == LOW){
     alarm_min++;
     if(alarm_min > 59){
       alarm_min = 0;     
     }     
   
   }
     if(alarm_min < 10 ){
       min_zero = 1;
     } else {
     min_zero = 0;
     }     
     if(min_zero == 1 ){
       lcd.print("0");
     } else {
       lcd.setCursor(3,1);     
     }     
     
     lcd.print(alarm_min);
   
 } else {
   digitalWrite(LED,LOW);
   //RTCにアラーム時刻送信
     
 }
 
 
 
 delay(1000);
 
 //alarm hour conversion
 /*
itoa(56,alarm_h_char[20],16);
int alarm_h_int = atoi(alarm_h_char[20]);
 Serial.print(alarm_h_int);
*/
 //BT通信確認
 /*if(Serial.available()>0){
    char c = Serial.read();
    if(c == 'a'){
      digitalWrite(LED,HIGH);
    }
    if(c == 's'){
      digitalWrite(LED,LOW);
    }
  }
 */

  
}

byte Dec2Bcd(byte b) {
    return (( b / 10 * 16) + ( b % 10 )); 
  }
