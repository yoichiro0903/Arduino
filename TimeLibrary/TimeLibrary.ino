#include <Time.h>
#include <TimeLib.h>
//http://qiita.com/exabugs/items/fe46ec45ff2ffd6c5777

time_t t;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(now());
  t = second();
  Serial.println(t);
  delay(1000);

}
