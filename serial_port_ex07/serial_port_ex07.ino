
const int SENSOR = 0; //フォトセンサが繋がっているピン
int val = 0; //センサからの値を記憶する変数

void setup(){
  Serial.begin(9600); //open serial port
  // 9600bit/sec data transmit
}

void loop(){
  val = analogRead(SENSOR); //read sensor value
  Serial.println(val); //output data to serial port
  delay(10000);
}
  
