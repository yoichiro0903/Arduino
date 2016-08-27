#include <Wire.h>
#include <LiquidCrystal.h>

// LiquidCrystal display with:
// rs on pin 12
// rw on pin 11
// enable on pin 10
// d0, d1, d2, d3 on pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

//global value
int RTC = 0xA2 >> 1;
byte sw_reg=0xff;
byte read_buff[7];

//initial time and date   sec,  min, hour,  day,  week,  man, year
byte write_buff[7]   =  {0x50, 0x59, 0x23, 0x31,  0x00, 0x12, 0x08};
// time is coded by BCD



void setup()
{
  Wire.begin(); // I2c begin
  lcd.begin(16, 2);
  lcd.clear();  // clear LCD
  init_RTC();	// set initial time (=write_buff)
}

void loop()
{
  read_RTC();
  if (read_buff[0] != sw_reg){
    lcd.clear();
    lcd.print("Date 20");
    put_date();
    lcd.setCursor(0, 1);
    lcd.print("Time   ");
    put_time();
    sw_reg=read_buff[0];
  }
}


void put_date()  // Put date string to LCD
{
  put(read_buff[6] & 0x3F);
  lcd.print("/");
  put(read_buff[5] & 0x1F);
  lcd.print("/");
  put(read_buff[3] & 0x3F);
}

void put_time() // Put time string to LCD
{
  put(read_buff[2] & 0x3F);
  lcd.print(":");
  put(read_buff[1] & 0x7F);
  lcd.print(":");
  put(read_buff[0] & 0x7F);
}

void put(byte buff)
{
  if(buff < 16) lcd.print("0");  //if upper 4bit is 0000
  lcd.print(buff, HEX);		// RTC data code is BCD
}  


/*
* The source code below is quotation from  "Arduino de RTC" at tokoya ("junk inn" blog).
*  http://tokoya.typepad.jp/blog/2008/11/arduinortc-6cdd.html
*/

void init_RTC() 
{
  Wire.beginTransmission(RTC);
  Wire.send(0x02);
  Wire.send(write_buff, 7);
  Wire.endTransmission();
}

void read_RTC()
{
  Wire.beginTransmission(RTC);  //  trasnmisson pre settings
  Wire.send(0x02);				//
  Wire.endTransmission();		//
  Wire.requestFrom(RTC, 7);		//
  for(int i = 0; i < 7; i++)
  {
    if(Wire.available())
    {
      read_buff[i] = Wire.receive(); // recicive data
    }
  }
}
