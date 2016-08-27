int pinP1 = 4; // DIGITALの4番    : WHITE
int pinP2 = 5; // DIGITALの5番    : RED
int pinP1B = 6; // DIGITALの6番   : YELLOW
int pinP2B = 7; // DIGITALの7番   : GREEN
int count = 0; //回転のカウント

void setup()
{
  pinMode(pinP1, OUTPUT); // 出力に設定
  pinMode(pinP2, OUTPUT); // 出力に設定
  pinMode(pinP1B, OUTPUT); // 出力に設定
  pinMode(pinP2B, OUTPUT); // 出力に設定
  
}

void step1(int dtime)
{
  // first step
  digitalWrite(pinP1, HIGH);
  digitalWrite(pinP2, LOW);
  digitalWrite(pinP1B, LOW);
  digitalWrite(pinP2B, LOW); 
  delay(dtime);  

  // second step
  digitalWrite(pinP1, LOW);
  digitalWrite(pinP2, HIGH);
  delay(dtime);
  
  // third step
  digitalWrite(pinP2, LOW);
  digitalWrite(pinP1B, HIGH);
  delay(dtime);
  
  // second step
  digitalWrite(pinP1B, LOW);
  digitalWrite(pinP2B, HIGH);
  delay(dtime);
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

void loop()
{
  if(count < 100){
  step2(15);  // 15ミリごと
  count++;
  
}
}
