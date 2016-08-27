int analogpin0 = 0;
int analogpin1 = 1;
int analogpin2 = 2;
int data;
float vol;
float g;

void setup(){
  Serial.begin(9600);
  Serial.println("Start");
}

void loop(){
  data = analogRead(analogpin0);
  data_out(data);
  data = analogRead(analogpin1);
  data_out(data);
  data = analogRead(analogpin2);
  data_out(data);
  
  Serial.println();
  delay(1000);


}

void data_out(int d){
  vol = (float)d / 1024.0 * 5.0;
  g = vol - 2.5 / 1.0;
  Serial.print(g);
  Serial.print(" , "); 
}
