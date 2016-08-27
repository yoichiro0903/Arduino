//Test 1
const int LED = 13;
const int LED2 = 3;
const int button = 8; //ボタンが接続されているピン
const int reed_a = 11; //リードセンサーが接続されているピン
const int reed_b = 10; //リードセンサーが接続されているピン
const int reed_c = 12; //リードセンサーが接続されているピン
int blink_time_a = 0;
int blink_time_b = 0;
int blink_time_c = 0;


int val = 0; //入力ピンの情報がここに格納される
int reed_val_a = 0; //入力ピンの情報がここに格納される
int reed_val_b = 0; //入力ピンの情報がここに格納される
int reed_val_c = 0; //入力ピンの情報がここに格納される
int old_val = 0; //以前のvalの値を保存しておく
int state = 0; //LEDの状態（０でオフ、１でオン）
char trans[20]; // 数字（文字列）の送信用配列
char recv[10]; // 数字（文字列）の受信用配列

int pinP1 = 4; // DIGITALの4番    : WHITE
int pinP2 = 5; // DIGITALの5番    : RED
int pinP1B = 6; // DIGITALの6番   : YELLOW
int pinP2B = 7; // DIGITALの7番   : GREEN
int count = 0; //回転のカウント

void setup()
{
  pinMode(LED, OUTPUT); //arduinoの出力がLEDだと定義
  pinMode(LED2, OUTPUT); //arduinoの出力がLED2だと定義
  pinMode(button, INPUT); //buttonは入力として設定
  pinMode(reed_a, INPUT); //reedは入力として設定
  pinMode(reed_b, INPUT); //reedは入力として設定
  pinMode(reed_c, INPUT); //reedは入力として設定
  pinMode(pinP1, OUTPUT); // 出力に設定
  pinMode(pinP2, OUTPUT); // 出力に設定
  pinMode(pinP1B, OUTPUT); // 出力に設定
  pinMode(pinP2B, OUTPUT); // 出力に設定
  // シリアル通信速度
  Serial.begin(9600);
}

void loop()
{
  val = digitalRead(button); //入力を読み取り、valに格納
  reed_val_a = digitalRead(reed_a); //入力を読み取り、valに格納
  reed_val_b = digitalRead(reed_b); //入力を読み取り、valに格納
  reed_val_c = digitalRead(reed_c); //入力を読み取り、valに格納

  if(reed_val_a == LOW){
    digitalWrite(LED2, HIGH);  
    //Serial.print("ok");
    delay(500);
    digitalWrite(LED2, LOW);  
    delay(500);
    digitalWrite(LED2, HIGH);  
  }
  if(reed_val_a == HIGH){
   digitalWrite(LED2, LOW);  
  }

  if(reed_val_b == LOW){
   //Stepping motor
   if(blink_time_b < 50){
   step2(150);  // 15ミリごと
   blink_time_b++; 
   }
  }

  if(reed_val_c == LOW){
   //Stepping motor
   if(blink_time_c < 100){
   step2(15);  // 15ミリごと
   blink_time_c++; 
   }
  }

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
/*  if (strcmp("1", p) == 0) { //"on"だとだめ
    digitalWrite(LED2, HIGH);
  } else if (strcmp("2", p) == 0) { //"off"だとだめ
    digitalWrite(LED2, LOW);
  }
*/


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

void step2(int dtime)
{
  // 初期設定 + first step
  digitalWrite(pinP1, HIGH);
  digitalWrite(pinP2, LOW);
  digitalWrite(pinP1B, LOW);
  digitalWrite(pinP2B, HIGH); 
  delay(dtime);  

  // second step
  digitalWrite(pinP2B, LOW); 
  digitalWrite(pinP2, HIGH);
  delay(dtime);  
  
  // third step
  digitalWrite(pinP1, LOW);
  digitalWrite(pinP1B, HIGH);
  delay(dtime);  

  // forth step
  digitalWrite(pinP2, LOW);
  digitalWrite(pinP2B, HIGH);
  delay(dtime);  
}

