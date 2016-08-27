// モーター制御
const int motorA = 7;//in1
const int motorB = 8;//in2
const int PWM_mot = 9;//PWM用、ここで速度を調整する
void setup(){
  pinMode(motorA,OUTPUT); //信号用ピン
  pinMode(motorB,OUTPUT); //信号用ピン
}

void loop(){
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,LOW);
    delay(1000);
    digitalWrite(motorA,HIGH);
    digitalWrite(motorB,LOW);
    analogWrite(PWM_mot,1000); 
    delay(3000);
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,LOW);
    delay(1000);
    digitalWrite(motorA,LOW);
    digitalWrite(motorB,HIGH);
    analogWrite(PWM_mot,1000); 
    delay(3000);
}
