//http://tsukutta.hatenablog.com/entry/2013/08/31/161753
// モーター制御
const int motorA = 7;
const int motorB = 8;
const int PWM_mot = 9;
int bean_st = 0;
void setup(){
  Serial.begin(9600);
  pinMode(motorA,OUTPUT); //信号用ピン
  pinMode(motorB,OUTPUT); //信号用ピン
  pinMode(13,OUTPUT) ;  
  pinMode(6,INPUT) ;  
}

void loop(){
if(digitalRead(6) == HIGH){
  bean_st = 1;
  digitalWrite(13,HIGH);
  Serial.println(digitalRead(6));     
  delay(500);
} else if (digitalRead(6) == LOW){
  bean_st = 0;
  digitalWrite(13,LOW);      
  Serial.println(digitalRead(6));     
  delay(500);
}
if (bean_st == 1) {     
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,LOW);
    delay(100);
    digitalWrite(motorA,HIGH);
    digitalWrite(motorB,LOW);
    analogWrite(PWM_mot,255); 
    delay(300);
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,LOW);
    delay(100);
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,HIGH);
    analogWrite(PWM_mot,255); 
    delay(300);
} else if (bean_st == 0) {
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,LOW);
}
}
