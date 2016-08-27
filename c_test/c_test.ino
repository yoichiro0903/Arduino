#include <stdio.h>


void setup(){
Serial.begin(9600);
}

void swap(int *k, int *t){
        int tmp;
        tmp = *k;
        *k = *t;
        *t = tmp;
}

void loop(){
  char c;
  if (Serial.available() > 0){
    c = Serial.read();
    if (c == 'a'){
      int a = 1;
      int b = 2;
      swap(&a,&b);
      Serial.println(a);
      Serial.println(b);
    }
  }
}
