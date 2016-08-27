int a_pin = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("start");
  
}


void loop(){
  int i;
  int data;
  int summary;
  float t_value;
  float input_avg;
  
  summary = 0;
  for(i=0; i<50; i++){
    data = analogRead(a_pin);
    summary = summary + data;
    delay(2);
  }
  
  input_avg = (float)summary/50.0;
  t_value = (input_avg / 1024.0 * 5.0 * 1000 - 600) / 10;
  Serial.println("Temp : ");
  Serial.println(t_value);
  delay(1000);
}

