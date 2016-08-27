#define INAPIN	         (7)
#define INBPIN	         (6)
//#define TACTPIN          (8)
//#define VOLUMEPIN	     (0)

#define BASESTEPANGLE    (3.75) // 1ステップの角度
#define PulseWidth       (50.0)  // 1パルスの長さ msec

bool rotLock = false;
void setup()
{
    pinMode(INAPIN, OUTPUT);
    pinMode(INBPIN, OUTPUT);
    //pinMode(TACTPIN, OUTPUT);
    Serial.begin(9600);
}

void set_degree(float deg) 
{
    Serial.println(deg);
    int count = deg / BASESTEPANGLE / 4; // 1ループで4パルス分
    if(count > 0) {
        for(int i = 0; i < count; i++) {
            digitalWrite(INAPIN, HIGH);
            digitalWrite(INBPIN, HIGH);
            delay(PulseWidth);
            digitalWrite(INAPIN, LOW);
            digitalWrite(INBPIN, HIGH);
            delay(PulseWidth);
            digitalWrite(INAPIN, LOW);
            digitalWrite(INBPIN, LOW);
            delay(PulseWidth);
            digitalWrite(INAPIN, HIGH);
            digitalWrite(INBPIN, LOW);
            delay(PulseWidth);
        }
    } else {
        for(int i = count; i < 0; i++) {
            digitalWrite(INAPIN, LOW);
            digitalWrite(INBPIN, LOW);
            delay(PulseWidth);
            digitalWrite(INAPIN, LOW);
            digitalWrite(INBPIN, HIGH);
            delay(PulseWidth);
            digitalWrite(INAPIN, HIGH);
            digitalWrite(INBPIN, HIGH);
            delay(PulseWidth);
            digitalWrite(INAPIN, HIGH);
            digitalWrite(INBPIN, LOW);
            delay(PulseWidth);
        }
    }
}

void deg_test()
{
    if (Serial.available()>0){
      int iValue = Serial.read();
      if(iValue > 1023){
        iValue = 0;
      }
      //int iValue = analogRead(VOLUMEPIN); // 0 - 1023
      // Serial.println(iValue);
      // 0-1023の区間を4分割して、その4つの領域に角度を割り当てる
      if(iValue < 1023 * 0.25) { // 256
          set_degree(180.0);
      } else if(iValue < 1023 * 0.5) { // 512
          set_degree(90.0);
      } else if(iValue < 1023 * 0.75) { // 768
          set_degree(-90.0);
      } else {
          set_degree(-180.0);
      }
    }
}

void loop()
{
    if(Serial.available() > 0 && rotLock == false) {
        rotLock = true;
        deg_test();
    } else if(rotLock == true) {
       rotLock = false;
    }
}
