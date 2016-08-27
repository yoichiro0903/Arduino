#include <Stepper.h>
#define STEPS 288// ステッピングモータの１回転あたりのステップ数

//デバッグ用LED
const int LED = 13;
const int LED2 = 9;
int val = 0; //入力ピンの情報がここに格納される
const int button = 8; //ボタンが接続されているピン
int old_val = 0; //以前のvalの値を保存しておく
int state = 0; //LEDの状態（０でオフ、１でオン）
//リードセンサー
const int reed_a = 10; //リードセンサーが接続されているピン
const int reed_b = 11; //リードセンサーが接続されているピン
const int reed_c = 12; //リードセンサーが接続されているピン
int reed_val_a = 0; //入力ピンの情報がここに格納される
int reed_val_b = 0; //入力ピンの情報がここに格納される
int reed_val_c = 0; //入力ピンの情報がここに格納される
int old_reed_val_a = 0; //入力ピンの情報がここに格納される
int old_reed_val_b = 0; //入力ピンの情報がここに格納される
int old_reed_val_c = 0; //入力ピンの情報がここに格納される
int count_a = 0;//ステッピングモーターの回転数制御用変数
int count_b = 0;//ステッピングモーターの回転数制御用変数
int count_c = 0;//ステッピングモーターの回転数制御用変数
int count_a_limit = 1;//ステッピングモーターの回転数
int count_b_limit = 1;//ステッピングモーターの回転数
int count_c_limit = 1;//ステッピングモーターの回転数
int reed_state = 0;//駒の初期位置
int old_reed_state = 1;//駒の前回の位置
int one_go = 50;
int two_go = 200;
int one_back = -50;
int two_back = -200;
//jsonデータ用変数
char trans[20]; // 数字（文字列）の送信用配列
char trans2[20]; // 数字（文字列）の送信用配列
char recv[10]; // 数字（文字列）の受信用配列
//ステッピングモーター
int pinP1 = 4; // DIGITALの4番    : WHITE
int pinP2 = 5; // DIGITALの5番    : RED
int pinP1B = 6; // DIGITALの6番   : YELLOW
int pinP2B = 7; // DIGITALの7番   : GREEN

// stepperクラスのインスタンスを生成する
Stepper Motor(STEPS, pinP1, pinP1B, pinP2, pinP2B) ;

void setup()
{
  //LED for debug
  pinMode(LED, OUTPUT); //arduinoの出力がLEDだと定義
  pinMode(LED2, OUTPUT); //arduinoの出力がLED2だと定義
  pinMode(button, INPUT); //buttonは入力として設定
  //Reed sensor
  pinMode(reed_a, INPUT); //reedは入力として設定
  pinMode(reed_b, INPUT); //reedは入力として設定
  pinMode(reed_c, INPUT); //reedは入力として設定
  //ステッピングモーターの出力端子指定
  pinMode(pinP1, OUTPUT); // 出力に設定
  pinMode(pinP2, OUTPUT); // 出力に設定
  pinMode(pinP1B, OUTPUT); // 出力に設定
  pinMode(pinP2B, OUTPUT); // 出力に設定
  Motor.setSpeed(40); // モータの速さを毎分の回転数(RPM)で設定する

  // シリアル通信速度
  Serial.begin(9600);
}

void loop()
{
  //LEDのオンオフのボタン
  val = digitalRead(button); //入力を読み取り、valに格納
  //リードセンサーの状態の読み取り
  reed_val_a = digitalRead(reed_a); //入力を読み取り、valに格納
  reed_val_b = digitalRead(reed_b); //入力を読み取り、valに格納
  reed_val_c = digitalRead(reed_c); //入力を読み取り、valに格納
  //リードセンサーa
  if(reed_val_a == LOW && old_reed_val_a == HIGH){
    reed_state = 1;
    //シリアル送信のjsonデータ生成
    memset(trans, 0, 20);
    char *json = &trans[0];
    char *message = "\"one\""; 
    sprintf(json, "{\"code\":%s}",message);
    Serial.println(json);
  }
  old_reed_val_a = reed_val_a; 

  if(old_reed_state == 1){
    //do nothing
    
    //Serial.print("same position");
  }
  if(old_reed_state == 2 && reed_state == 1){ 
    for(count_a = 0; count_a < count_a_limit; count_a++){
    //stepping(15);  // 150ミリごと、かなりゆっくり
    //Stepping motor by library
    Motor.step(one_back);
    Serial.print("2 to 1");
    Serial.println();
   }
   old_reed_state = reed_state;
  }
  if(old_reed_state == 3 && reed_state == 1){
    for(count_a = 0; count_a < count_a_limit; count_a++){
    //stepping(15);  // 150ミリごと、かなりゆっくり
    //Stepping motor by library
    Serial.print("3 to 1");
    Serial.println();
    Motor.step(two_back);
   }
   old_reed_state = reed_state;
  }
  
  if(reed_val_a == HIGH){
    //do nothing    
  }
///////////////
  //リードセンサーb
  if(reed_val_b == LOW && old_reed_val_b == HIGH){
    reed_state = 2;
    //シリアル送信のjsonデータ生成
    memset(trans, 0, 20);
    char *json = &trans[0];
    char *message = "\"two\""; 
    sprintf(json, "{\"code\":%s}",message);
    Serial.println(json);
  }
  old_reed_val_b = reed_val_b; 

  if(old_reed_state == 2){
    //do nothing
    //Serial.print("same position");
  }
  if(old_reed_state == 1 && reed_state == 2){ 
    for(count_b = 0; count_b < count_b_limit; count_b++){
    //stepping(15);  // 150ミリごと、かなりゆっくり
    //Stepping motor by library
    Serial.print("1 to 2");
    Serial.println();
    Motor.step(one_go);
   }
   old_reed_state = reed_state;
  }
  if(old_reed_state == 3 && reed_state == 2){
    for(count_b = 0; count_b < count_b_limit; count_b++){
    //stepping(15);  // 150ミリごと、かなりゆっくり
    //Stepping motor by library
    Serial.print("3 to 2");
    Serial.println();
    Motor.step(one_back);
   }
   old_reed_state = reed_state;
  }
  
  if(reed_val_b == HIGH){
    //do nothing    
  }
/////////////
  //リードセンサーc
  if(reed_val_c == LOW && old_reed_val_c == HIGH){
    reed_state = 3;
    //シリアル送信のjsonデータ生成
    memset(trans, 0, 20);
    char *json = &trans[0];
    char *message = "\"three\""; 
    sprintf(json, "{\"code\":%s}",message);
    Serial.println(json);
  }
  old_reed_val_c = reed_val_c; 

  if(old_reed_state == 3){
    //do nothing
    //Serial.print("same position");
  }
  if(old_reed_state == 2 && reed_state == 3){ 
    for(count_c = 0; count_c < count_c_limit; count_c++){
    //stepping(15);  // 150ミリごと、かなりゆっくり
    //Stepping motor by library
    Serial.print("2 to 3");
    Serial.println();
    Motor.step(one_go);
   }
   old_reed_state = reed_state;
  }
  if(old_reed_state == 1 && reed_state == 3){
    for(count_a = 0; count_a < count_a_limit; count_a++){
    //stepping(15);  // 150ミリごと、かなりゆっくり
    //Stepping motor by library
    Serial.print("1 to 3");
    Serial.println();
    Motor.step(two_go);
   }
   old_reed_state = reed_state;
  }
  
  if(reed_val_c == HIGH){
    //do nothing    
  }

//    Motor.step(288);
  //  delay(1000);
  
/////////////////////////////////////
  // jsonデータ受信部分
  memset(recv, 0, 10);
  char *p = &recv[0]; //このpにオンオフの指令が代入されている
  recvStr(p);
  if(p > 0){
  Serial.print(p);
  }
  
/////////////////////////////////////
  //LED debug
  //スイッチが押されるたびに一度だけ実行される（入力がHighかLowを判定）
  if ((val == HIGH) && (old_val == LOW)){
  state = 1 - state;
  //ON
  /*if(state == 1){
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
  //シリアル送信のjsonデータ生成
        memset(trans, 0, 20);
         char *json = &trans[0];
         char *message = "\"off\""; 
         sprintf(json, "{\"code\":%s}",message);
         Serial.println(json);
         delay(50);
  }
  delay(50);
  */} 
  old_val = val;

  if (state == 1){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW); 
  }

  //シリアルデータからオンオフするLED
  if (strcmp("1", p) == 0) { //"on"だとだめだった。数字だと機能する
    digitalWrite(LED2, HIGH);
  } else if (strcmp("2", p) == 0) { //"off"だとだめだった。数字だと機能するの
    digitalWrite(LED2, LOW);
  }

}//loop end

// jsonデータ受信関数
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


//ステッピングモーター制御関数
void stepping(int dtime)
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
