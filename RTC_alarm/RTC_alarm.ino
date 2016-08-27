//
// 104-04 外部割込み実験スケッチ
//

#include <Wire.h>

#define I2C_ADDR (0xA2 >> 1)
int interruptPin = 2;

void message() {
  Serial.println("INT");
}

void setup() {
  Serial.begin(9600);
  Serial.println("RTC Test Start");

  attachInterrupt(0, message, FALLING);  // 外部割り込みを開始する。
                                         // 0 割り込みピン D2
                                         // message 割り込み時に実行される関数
                                         // FALLING ピンの状態が HIGH → LOW になった時に割り込み

  Wire.begin();
  delay(1000);

// 実験用に初期化
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x00);
  Wire.write(0x20); // 00
  Wire.write(0x00); // 01
  Wire.write(0x00); // 02
  Wire.write(0x00); // 03
  Wire.write(0x00); // 04
  Wire.write(0x01); // 05
  Wire.write(0x01); // 06
  Wire.write(0x84); // 07
  Wire.write(0x13); // 08
  Wire.write(0x00); // 09
  Wire.write(0x00); // 0A
  Wire.write(0x00); // 0B
  Wire.write(0x00); // 0C
  Wire.write(0x00); // 0D
  Wire.write(0x00); // 0E
  Wire.write(0x00); // 0F
  Wire.write(0x00);
  Wire.endTransmission();

// タイマーを停止
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x0E);
  Wire.write(0b00000000); // 0E
  Wire.endTransmission();

// Control 2 の設定
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x01);
  Wire.write(0b00010001); // 02 bit4 TI/TP 動作モードを繰り返しに設定
                          //    bit0 TIE   /INT端子へ出力
  Wire.endTransmission();

// タイマーのカウント数を設定
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x0F);
  Wire.write(0b00000010); // 0F カウンタの回数を指定
  Wire.endTransmission();

// タイマーを開始
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x0E);
  Wire.write(0b10000010); // 0E bit7 TE   タイマー割り込み開始
                          //    bit1 TD1  1周期の間隔を設定 TD1,0 = 1,0 = 1 秒
                          //    bit0 TD0
  Wire.endTransmission();
}

void loop() {
  
  delay(1000);
    if (digitalRead(interruptPin)) {
    Serial.print("HIGH ");
  } else {
    Serial.print("LOW  ");
  }
}

