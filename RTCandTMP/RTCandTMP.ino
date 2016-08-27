#include "Arduino.h"
#include "Wire.h"


#define RTC_ADDRESS (0xa2 >> 1)
#define TMP_ADDRESS (0x80 >> 1)

int rtc[16];
float tmp[5];
int LED = 13;
String alarm_sec;
int alarm_sec_int;

void setup() {
 
 Serial.begin(9600);
 Serial.println("Initializing RTC unit...Please wait...");
 delay(1000);
 
 //LED
 pinMode(LED, OUTPUT);
 
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
 // 秒レジスタ。とりあえず、58秒。
 Wire.write(0x55);
 // 分レジスタ。とりあえず、59分。
 Wire.write(0x20);
 // 時レジスタ。とりあえず、23時。
 Wire.write(0x12);
 // 日レジスタ。とりあえず、23日。
 Wire.write(0x23);
 // 曜日レジスタ。とりあえず、月曜日。
 Wire.write(0x01);
 // 月レジスタ。とりあえず、7月。
 Wire.write(0x07);
 // 年レジスタ。取りあえず、12年。
 Wire.write(0x12);
 
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
 
 
 //alarm
 Wire.beginTransmission(RTC_ADDRESS);
 Wire.write(0x01);
 Wire.write(0x02);
 Wire.endTransmission();

 Wire.beginTransmission(RTC_ADDRESS);
 Wire.write(0x09);
 //alarm min
 Wire.write(0x21);
 //alarm hour
 Wire.write(0x12);
 //alarm day
 Wire.write(0x02 | 0x80);
 //alarm wday
 Wire.write(0x02 | 0x80);
 Wire.endTransmission();
  
 delay(20);
 Serial.println("RTC Initialized.");
}

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
 ///Serial.print(alarm_sec);
 if(rtc[3] == 0x22){
   //digitalWrite(LED,HIGH);
   Wire.beginTransmission(RTC_ADDRESS);
   Wire.write(0x01);
   Wire.write(rtc[1] & 0xf5);
   Wire.endTransmission();
 }
 
 // TMPとのI2C通信開始。
 Wire.beginTransmission(RTC_ADDRESS);
 // レジスタアドレス0x00を指定。
 Wire.write(0x00);
 // キューの送信。
 Wire.endTransmission();
 
 // データ要求。
 Wire.requestFrom(TMP_ADDRESS, 5);
 // データ受信。
 for (int k = 0; k < 5; k++) {
  while (Wire.available() == 0);
  tmp[k] = Wire.read();
 }

 float temperature;
 temperature = tmp[1] * 0.03125 + 273.15;
 
 Serial.println("byte1");
 Serial.println(tmp[1],5);
 Serial.println("byte2");
 Serial.println(temperature,5);
 /*Serial.println("byte3");
 Serial.println(tmp[2]);
 Serial.println("byte4");
 Serial.println(tmp[3]);
 Serial.println("byte5");
 Serial.println(tmp[4]);
 */
 
 delay(10000);
 
 
}
