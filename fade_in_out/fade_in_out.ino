
const int LED = 9;
int i = 0;

void setup(){
  pinMode(LED, OUTPUT);
}

void loop(){
  for (i = 0; i<255; i++) { //0から254までループ、どんどん明るくする
    analogWrite(LED, i); //LEDの明るさをセット
    delay(10);
  }
  
  for (i = 255; i > 1; i--) { //255から1までループ、暗くする
    analogWrite(LED, i);
    delay(10);
  }
}
  
    
