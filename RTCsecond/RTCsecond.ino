#include <Wire.h>
#define I2C_RTC_ADRS 0x51     // スレーブ・アドレス(7bit)

void setup() {
  Wire.begin();
}

void loop() {
  int sec;
  Wire.beginTransmission(I2C_RTC_ADRS);  // (1)  スタート
  Wire.write(0x02);                                       // (2)  "秒"の レジスタアドレス
  Wire.endTransmission();                            // (3)  ストップ
  Wire.requestFrom(I2C_RTC_ADRS, 1);       // (4)  スタート、受信
  sec  = Wire.read() & 0x7F;                     // (5)  データ取り出し
  
}
