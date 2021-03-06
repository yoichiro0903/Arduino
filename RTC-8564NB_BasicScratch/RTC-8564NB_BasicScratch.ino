//http://baticadila.dip.jp/arduino_104.html
// 104-01 RTC実験スケッチ
//

#include <Wire.h>

#define I2C_ADDR (0xA2 >> 1)  // 1ビット目未使用のため1ビット右シフトする。
int interruptPin = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("RTC Test Start");

  Wire.begin();  // I2C の初期化
  delay(1000);   // 発振子の動作待機

  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x00); // データを転送する先頭のレジスタ番号を指定
  Wire.write(0x20); // 00 Control 1　STOP(bit5)-1 をセットし動作を停止させる。
  Wire.write(0x00); // 01 Control 2
  Wire.write(0x00); // 02 Seconds　初期値を転送（秒）0 ～ 59
  Wire.write(0x00); // 03 Minutes　　　 〃 　　（分）0 ～ 59
  Wire.write(0x00); // 04 Hours　　　　 〃 　　（時）0 ～ 23
  Wire.write(0x01); // 05 Days 　　　　 〃 　　（日）1 ～ 31
  Wire.write(0x01); // 06 Weekdays 　　 〃 　　（曜日）0 ～ 6
  Wire.write(0x84); // 07 Months 　　　 〃 　　（月）1 ～ 12
  Wire.write(0x13); // 08 Years　　　　 〃 　　（年）0 ～ 99
  Wire.write(0x00); // 09 Minutes Alarm　アラームの初期値を転送（分）0 ～ 59
  Wire.write(0x00); // 0A Hours Alarm　　　　　　 〃 　　　　　（時）0 ～ 23
  Wire.write(0x00); // 0B Days Alarm 　　　　　　 〃 　　　　　（日）1 ～ 31
  Wire.write(0x00); // 0C Weekdays Alarm　　　　　〃 　　　　　（曜日）0 ～ 6
  Wire.write(0x00); // 0D CLKOUT 　　　　タイマー用レジスタ
  Wire.write(0x00); // 0E Timer control　　　　　〃
  Wire.write(0x00); // 0F Timer　　　　　　　　　〃
  Wire.write(0x00); // 00 Control 1　STOP(bit5)-0 をリセットし動作を開始する。
                    //    アドレス 0F の次は先頭アドレスの 00 に戻る。
  Wire.endTransmission();

}

//
// 104-02 受信データのフィルタリング
//

void loop() {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x02);
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(I2C_ADDR, 7);
  int sec = Wire.read();
  int min = Wire.read();
  int hour = Wire.read();
  int day = Wire.read();
  int week = Wire.read();
  int month = Wire.read();
  int year = Wire.read();

  Serial.print(year, HEX);
  Serial.print("/");
  Serial.print(month & 0x1f, HEX);
  Serial.print("/");
  Serial.print(day &0x3f, HEX);
  Serial.print("(");
  Serial.print(week & 0x07, HEX);
  Serial.print(")");
  Serial.print(hour & 0x3f, HEX);
  Serial.print(":");
  Serial.print(min & 0x7f, HEX);
  Serial.print(":");
  Serial.println(sec & 0x7f, HEX);

  delay(1000);
    if (digitalRead(interruptPin)) {
    Serial.print("HIGH ");
  } else {
    Serial.print("LOW  ");
  }
}

