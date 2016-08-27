// Example 06A : アナログ入力の値に応じてLEDの点滅レートを変化させる


const int LED = 13; //LEDピンを指定
int val = 0; //センサーからの値を記憶する変数

void setup(){
  pinMode(LED, OUTPUT); //出力としてLED（13ピン）を指定
  //　アナログピンは自動的に入力として選択される
}

void loop(){
  val = analogRead(0); //0ピンから値を読み込む
  
  digitalWrite(13, HIGH); //LEDをつける
  delay(val); //アナログセンサーの値に応じて遅延（フォトセンサ）
  
  digitalWrite(13, LOW); //LED OFF
  delay(val);
}

  
