void setup() {
  Serial.begin(31250);
  sendMidi(0xb0, 0x78, 0); // all sound off
}

void loop() {
  for (int i = 1; i < 7; ++i) {
    int note = 12 * i;
    sendMidi(0x90, note, 100); // note on
    delay(300);
    sendMidi(0x80, note, 100); // note off
  }
}

void sendMidi(char stat, char data1, char data2) {
  Serial.write(stat);
  Serial.write(data1);
  Serial.write(data2);
}
