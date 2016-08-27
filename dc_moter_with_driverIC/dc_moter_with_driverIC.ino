#define IN1PIN	(9)
#define IN2PIN	(10)
//#define VOLUMEPIN	(0)

void setup() 
{ 
	pinMode(IN1PIN, OUTPUT);
	pinMode(IN2PIN, OUTPUT);
        Serial.begin(9600);
} 

int Map( int iIn, int iIn1, int iIn2, int iOut1, int iOut2, boolean bConstrain = false )
{
  //int iMotor = Map(iValue, 0, 1023, -255, 255, true);
	double dValue = (double)(iIn - iIn1) * (iOut2 - iOut1) / (iIn2 - iIn1) + iOut1;
	int iValue = (0 < dValue) ? (int)(dValue + 0.5) : (int)(dValue - 0.5);
	if( bConstrain )
	{
		int iOutMin, iOutMax;
		if( iOut1 < iOut2 )
		{
			iOutMin= iOut1;
			iOutMax= iOut2;
		}
		else
		{
			iOutMin= iOut2;
			iOutMax= iOut1;
		}
		if( iOutMin > iValue )
		{
			return iOutMin;
		}
		if( iOutMax < iValue )
		{
			return iOutMax;
		}
	}
	return iValue;
}

void MotorDrive( int iIn1Pin, int iIn2Pin, int iMotor )
{
	if( -5 < iMotor
	 &&  5 > iMotor )
	{
		//digitalWrite(iIn1Pin, HIGH);
		//digitalWrite(iIn2Pin, HIGH);
		digitalWrite(iIn1Pin, LOW);
		digitalWrite(iIn2Pin, LOW);
	}
	else if( 0 < iMotor )
	{
		analogWrite(iIn1Pin, iMotor);
		analogWrite(iIn2Pin, 0);
	}
	else
	{
		analogWrite(iIn1Pin, 0);
		analogWrite(iIn2Pin, -iMotor);
	}
}

void loop() 
{ 
  if (Serial.available()>0){
      int iValue = Serial.read();
      if(iValue > 1023){
        iValue = 0;
      }
        //int iValue = analogRead(VOLUMEPIN);
	int iMotor = Map(iValue, 0, 1023, -255, 255, true);	

	MotorDrive( IN1PIN, IN2PIN, iMotor );
	delay(15);
  }
} 

