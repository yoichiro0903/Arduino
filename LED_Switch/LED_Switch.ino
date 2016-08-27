//Test 1
const int LED = 13;
const int button = 7; //ボタンが接続されているピン

int val = 0; //入力ピンの情報がここに格納される
int old_val = 0; //以前のvalの値を保存しておく
int state = 0; //LEDの状態（０でオフ、１でオン）



void setup()
{
  pinMode(LED, OUTPUT); //arduinoの出力がLEDだと定義
  pinMode(button, INPUT); //buttonは入力として設定
}

void loop()
{
  val = digitalRead(button); //入力を読み取り、valに格納
  //入力がHighか否か
  if ((val == HIGH) && (old_val == LOW)){
  state = 1 - state;
  delay(500);
  } 
  old_val = val;
  if (state == 1){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW); //LED off
  }
}
  
  
