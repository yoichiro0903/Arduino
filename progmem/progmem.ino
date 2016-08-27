
#include <avr/pgmspace.h>


// Then set up a table to refer to your strings.


void setup()			  
{
  Serial.begin(9600);
}

PROGMEM prog_uint16_t charSet[] =
  { 0x90,0x1E, 0x45, 0x90, 0x1F, 0x00 };
void loop()			  
{
  /* Using the string table in program memory requires the use of special functions to retrieve the data.
     The strcpy_P function copies a string from program space to a string in RAM ("buffer"). 
     Make sure your receiving string in RAM  is large enough to hold whatever
     you are retrieving from program space. */
unsigned int displayInt1;
unsigned int displayInt2;
unsigned int displayInt3;
char myChar;
for (int k = 0; k< 2; k++){
int l = 3*k+1;
int m = 3*k+2;
displayInt1 = pgm_read_word_near(charSet + 3*k);
displayInt2 = pgm_read_word_near(charSet + l);
displayInt3 = pgm_read_word_near(charSet + m);
Serial.println(displayInt1,HEX);
Serial.println(displayInt2,HEX);
Serial.println(displayInt3,HEX);

delay(500);
}

}//end loop


