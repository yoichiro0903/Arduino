
const int LED = 9;
const int button = 7; //ボタンのピン番号
int i = 0;
int val = 0;
int old_val = 0;
int state = 0;
int e =0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);
}

void loop(){
  val = digitalRead(button); //インプットを読み込み、状態をvalに格納
  if ((val == HIGH) && (old_val == LOW)) { //ボタンが押されて、前状態が消えていたなら明暗を繰り返す
    state = 1 - state;
    delay(50);
  }

  
  old_val = val;
  
    
      
    if (state == 1) {
  //ボタン押したらちかちかして、もっかい押したらきえる
/*
  for (i = 0; i<255; i++) { //0から254までループ、どんどん明るくする
    analogWrite(LED, i); //LEDの明るさをセット
    delay(10);
  }

  for (i = 255; i > 1; i--) { //255から1までループ、暗くする
    analogWrite(LED, i);
    delay(10);
  }
  state = 0;
  */
  
  analogWrite(LED, 120);
  } else { //消したいときにボタンを押されたならLEDを消す
  analogWrite(LED, 0);
  }  
}
    
