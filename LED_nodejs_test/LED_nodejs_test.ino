//Test 1
const int LED = 13;
const int LED2 = 10;
const int button = 7; //ボタンが接続されているピン
const int reed = 11; //リードセンサーが接続されているピン

int val = 0; //入力ピンの情報がここに格納される
int reed_val = 0; //入力ピンの情報がここに格納される
int old_val = 0; //以前のvalの値を保存しておく
int state = 0; //LEDの状態（０でオフ、１でオン）
char trans[20]; // 数字（文字列）の送信用配列
char recv[10]; // 数字（文字列）の受信用配列


void setup()
{
  pinMode(LED, OUTPUT); //arduinoの出力がLEDだと定義
  pinMode(LED2, OUTPUT); //arduinoの出力がLED2だと定義
  pinMode(button, INPUT); //buttonは入力として設定
  pinMode(reed, INPUT); //reedは入力として設定
  // シリアル通信速度
  Serial.begin(9600);
}

void loop()
{
  val = digitalRead(button); //入力を読み取り、valに格納
  reed_val = digitalRead(reed); //入力を読み取り、valに格納
/*
  if(reed_val == LOW){
    digitalWrite(LED2, HIGH);  
    //Serial.print("ok");
  }
  if(reed_val == HIGH){
    digitalWrite(LED2, LOW);  
    //Serial.print("ff");
  }
  */
  //入力がHighか否か、スイッチが押されるたびに一度だけ実行される
  if ((val == HIGH) && (old_val == LOW)){
  state = 1 - state;
  //ON
  if(state == 1){
  //Serial.print("ON");
  //Serial.println("");
  //シリアル送信のjsonデータ生成
         memset(trans, 0, 20);
         char *json = &trans[0];
         char *message = "\"on\""; 
         sprintf(json, "{\"code\":%s}",message);
         Serial.println(json);
         delay(50);
  }
  //OFF
  if(state == 0){
  //Serial.print("OFF");
  //Serial.println("");
  //シリアル送信のjsonデータ生成
         memset(trans, 0, 20);
         char *json = &trans[0];
         char *message = "\"off\""; 
         sprintf(json, "{\"code\":%s}",message);
         Serial.println(json);
         delay(50);
  }
  delay(500);
  } 
  old_val = val;
  if (state == 1){
    digitalWrite(LED, HIGH);
  } else {
    //digitalWrite(LED2, LOW);
    digitalWrite(LED, LOW); //LED off
  }

  // シリアルからのデータ受信
  memset(recv, 0, 10);
  char *p = &recv[0];
  recvStr(p);
  if(p > 0){
  Serial.print(p);
//    digitalWrite(LED2, HIGH);
  }
  if (strcmp("1", p) == 0) { //"on"だとだめ
    digitalWrite(LED2, HIGH);
  } else if (strcmp("2", p) == 0) { //"off"だとだめ
    digitalWrite(LED2, LOW);
  }

}
  
// データ受信
void recvStr(char *buf)
{
  int i = 0;
  char c;
  while (Serial.available()) {
      c = Serial.read();
      buf[i] = c;
      i++;
  }
}  
