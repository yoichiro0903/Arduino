#include <MIDI.h>
 
//ピン設定
#define analogPin 0
 
//初期化===========================================================
int Ch = 0;
 
void setup()
{
  MIDI.begin();
 
}
 
void loop()
{
    //チャンネル選択
    int beforCh = Ch;
    Ch = analogRead(analogPin);
    Ch = (Ch / 64 ) + 1;
    if(beforCh != Ch){
        Serial.print(Ch,OCT);
        Serial.println(" ");
    }
 
    uint8_t data1,data2;
    if (MIDI.read()) {
        MIDI.setInputChannel(Ch);   //読み込むチャンネルを設定
 
        switch(MIDI.getType()) {
            case NoteOn:        //鍵盤を押す
                data1 = MIDI.getData1();    // ノートNo.（音階）
                data2 = MIDI.getData2();    // ベロシティ（音の強さ）
 
                Serial.print(data1,HEX);
                Serial.println(" ");
                Serial.print(data2,HEX);
            break;
            case NoteOff:       //鍵盤を離す
                data1 = MIDI.getData1();    // ノートNo.（音階）
                data2 = MIDI.getData2();    // ベロシティ（音の強さ）
 
                Serial.print(data1,HEX);
                Serial.println(" ");
                Serial.print(data2,HEX);
            break;
            case ProgramChange: //音色の切り替え
                data1 = MIDI.getData1();    //プログラムNo.（音色）
 
                Serial.print(data1,HEX);
            break;
            case PitchBend:     //音程（ピッチ）
                data1 = MIDI.getData1();    // ＭＳＢ
                data2 = MIDI.getData2();    // ＬＳＢ
 
                int Pitch = data2;
                Pitch = Pitch * 128 + data1 - 8192;
 
                Serial.print(Pitch);
                Serial.println(" ");
            break;
 
        }
    }
}

