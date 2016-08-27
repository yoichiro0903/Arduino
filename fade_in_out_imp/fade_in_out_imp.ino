
const int LED = 9;
const int button = 7; //ボタンのピン番号
int i = 0;
int val = 0;
int old_val = 0;
int state = 0;
int brightness = 0;
unsigned long start_time = 0; //押し始めた時間 

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
}

void loop(){
  val = digitalRead(button); //インプットを読み込み、状態をvalに格納
  if ((val == HIGH) && (old_val == LOW)) { //ボタンが押されて、前状態が消えていたなら明暗を繰り返す
    state = 1 - state;
    start_time = millis();
    delay(50);
  }

  
  //ボタン押しっぱなし
  if ((val == HIGH) && (old_val == HIGH)){
    if (state == 1 && millis() > 500) {
      brightness++;
      delay(1000);
      if(brightness > 255){
        brightness = 0;
      }
    }
  }
  
  old_val = val;
  
  if (state == 1){
    analogWrite(LED, brightness);
  } else {
    analogWrite(LED, 0);
  }
}
    
      
/*
    if (state == 1) {
  //ボタン押したらちかちかして、もっかい押したらきえる

  for (i = 0; i<255; i++) { //0から254までループ、どんどん明るくする
    analogWrite(LED, i); //LEDの明るさをセット
    delay(10);
  }

  for (i = 255; i > 1; i--) { //255から1までループ、暗くする
    analogWrite(LED, i);
    delay(10);
  }
  
  
  analogWrite(LED, 120);
  } else { //消したいときにボタンを押されたならLEDを消す
  analogWrite(LED, 0);
  delay(50);
  }  
}
  */
    
