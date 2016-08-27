/*
  PrintHex routines for Arduino: to print byte or word data in hex with
  leading zeroes.
  Copyright (C) 2010 Kairama Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

void setup() 
{
        Serial.begin(9600);
        Serial.print("Setup: Examples of PrintHex usage\n\n"); 
}

void loop() 
{
        uint8_t ByteData[5]={0x01, 0x0F, 0x10, 0x11, 0xFF};
        Serial.print("With uint8_t array:  "); PrintHex8(ByteData,5); Serial.print("\n"); 

        uint8_t ByteDatum=0x01;
        Serial.print("With uint8_t scalar: "); PrintHex8(&ByteDatum,1); Serial.print("\n"); 
 
        uint16_t Shorts[5]={0x0001, 0x00FF, 0x0100, 0xAAAA, 0xFFFF};
        Serial.print("With uint16_t array: "); PrintHex16(Shorts,5); Serial.print("\n"); 

        Serial.print("==========================================\n");
        delay(10000);
}
void PrintHex8(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
        Serial.print("0x"); 
        for (int i=0; i<length; i++) { 
          if (data[i]<0x10) {Serial.print("0");} 
          Serial.print(data[i],HEX); 
          Serial.print(" "); 
        }
}

void PrintHex16(uint16_t *data, uint8_t length) // prints 16-bit data in hex with leading zeroes
{
        Serial.print("0x"); 
        for (int i=0; i<length; i++)
        { 
          uint8_t MSB=byte(data[i]>>8);
          uint8_t LSB=byte(data[i]);
          
          if (MSB<0x10) {Serial.print("0");} Serial.print(MSB,HEX); Serial.print(" "); 
          if (LSB<0x10) {Serial.print("0");} Serial.print(LSB,HEX); Serial.print(" "); 
        }
}

