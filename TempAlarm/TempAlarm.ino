#include <Time.h>
#include <LiquidCrystal.h>

//LEDの出力ピン指定
const int out_pin = 12;
//アラームを切るスイッチの入力ピン
const int button = 11;
//温度センサーの入力ピンをアナログ０番に指定
int a_pin = 0;
//ボタンの状況を記録する変数
int val = 0;
//ボタンが押されたか否かを判定する変数、押されたら１になる
int state = 0;

//LCDのピン指定、5V(LCD 1)、GND(2)、コントラスト(3)、RS(4)、R/W(5)、E(6)
//DATA BIT4(11)、５(12)、6(13)、7(14)
LiquidCrystal lcd(8,2,3,4,5,6,7); 

void setup() {
  
  lcd.begin(16, 2);
  //コントラスト調整
  analogWrite(9, 80);
  
  //時間の初期化
  setTime(0);
  //setTmie(sec,min,hour,day,month,year);
  
  //LEDをつけるピン指定
  pinMode(out_pin, OUTPUT); //arduinoの出力がLEDだと定義
  //ボタンの電圧判定の入力ピン指定
  pinMode(button, INPUT); //button
  
  //シリアル通信開始
  Serial.begin(9600);


}

void loop() {
  //年月、時間変数
  char out_str[10];
  char out_str2[10];
  
  //アラームストップボタンが押されていなかったら
  if(state == 0){
    //時間を変数に代入してLCDに表示
    sprintf(out_str,"%04d/%02d/%02d",year(),month(),day());
    lcd.setCursor(0,0);
    lcd.print(out_str);
    sprintf(out_str2,"%02d/%02d/%02d",hour(),minute(),second());
    lcd.setCursor(0, 1);
    lcd.print(out_str2);
    //Serial.println(out_str);
    //Serial.println(out_str2);
  }
  
  //アラームのなりはじめる秒数の変数
  int alarm_s;
  alarm_s = 10;
    
  //アラーム開始時刻より経過していて、かつボタンが押されていなかったら
  if(alarm_s < second() && state == 0){
    //LEDをつける
    digitalWrite(out_pin,HIGH);
  }
  
  
  //温度センサーの計算
  
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
  //温度をLCDに表示
  lcd.setCursor(10, 1);
  lcd.print(t_value);

  
  
  //ボタンの状況を判定
  val = digitalRead(button);
  
  //アラーム起動後に、スイッチが押されたか、温度が２５℃以上になったら
  if ((val == LOW or t_value > 25) && alarm_s < second() && state == 0){
    state = 1 - state;  
  }
  
  //アラームを止める動作（ボタン、温度）がなされたら
  if(state == 1){

    //LEDを消す（アラームを止める）
    digitalWrite(out_pin,LOW);

    //年月の代わりにアラーム止めたLCD表示をする
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("alarm stopped");
    sprintf(out_str2,"%02d/%02d/%02d",hour(),minute(),second());
    lcd.setCursor(0, 1);
    lcd.print(out_str2);
    
    //温度をLCDに表示
    lcd.setCursor(10, 1);
    lcd.print(t_value);

  }


  
  delay(1000);
}
