const int PIN_ANT = 25;
const int FREQ = 800000;
const int RES_BITS = 4;
const int DUTY = 8; 

const int DOT = 250;
const int DASH = 750;
const int GAP_ELEM = 250;
const int GAP_LETTER = 750;
const int GAP_WORD = 1750;

void carrierOn() {
  ledcAttach(PIN_ANT, FREQ, RES_BITS);
  ledcWrite(PIN_ANT, DUTY);
}

void carrierOff() {
  ledcWrite(PIN_ANT, 0);
  ledcDetach(PIN_ANT);
}

void dot() {
  carrierOn(); delay(DOT);
  carrierOff(); delay(GAP_ELEM);
}

void dash() {
  carrierOn(); delay(DASH);
  carrierOff(); delay(GAP_ELEM);
}

void sendChar(char c) {
  switch(c) {
    case 'H': dot(); dot(); dot(); dot(); break;
    case 'E': dot(); break;
    case 'L': dot(); dash(); dot(); dot(); break;
    case 'O': dash(); dash(); dash(); break;
    case 'W': dot(); dash(); dash(); break;
    case 'R': dot(); dash(); dot(); break;
    case 'D': dash(); dot(); dot(); break;
    case ' ': delay(GAP_WORD - GAP_LETTER); break;
  }
  delay(GAP_LETTER - GAP_ELEM); 
}

void setup() {
  Serial.begin(115200);
  carrierOff();
}

void loop() {
  String msg = "HELLO WORLD";
  for (int i = 0; i < msg.length(); i++) {
    sendChar(msg[i]);
  }
  delay(3000);
}