/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int cds_val = 0;
int cds = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  cds_val = analogRead(cds);
  Serial.println(cds_val);
/*  digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println(100);
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  Serial.println(1000);
  delay(1000);               // wait for a second
*/delay(50);
}
