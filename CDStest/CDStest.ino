 void setup() {
     pinMode(13,OUTPUT) ;   // LED接続のピン(13番)をデジタル出力に設定
 }
 void loop() {
    int ans ;

     ans = analogRead(0) ;  // CDS接続のアナログピン０番を読み取る
     if (ans >= 700) {      // 700がしきい値です
          // 光がしきい値より暗く(大きく)なったなら処理
          digitalWrite(13, HIGH) ;  // LEDを点灯(HIGH（5V）)で出力
     } else {
          // 光がしきい値より明るく(小さく)なったなら処理
          digitalWrite(13, LOW) ;   // LEDを消灯(LOW（0V）)で出力
     }
 }
