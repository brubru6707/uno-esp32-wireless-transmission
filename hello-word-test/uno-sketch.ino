const int PIN_RX = A0;
const int THRESH_HIGH = 80; 
const int THRESH_LOW = 70; 
const int DOT_MS = 250; 

long lastTime = 0; 
bool active = false;   
String buffer = ""; 

String decode(String s) {
  if (s == "....") return "H";
  if (s == ".")    return "E";
  if (s == ".-..") return "L";
  if (s == "---")  return "O";
  if (s == ".--")  return "W";
  if (s == ".-.")  return "R";
  if (s == "-..")  return "D";
  if (s == "---.--") return "OW"; 
  if (s == "-......") return "DH";
  return "?"; 
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RX, INPUT);
}

void loop() {
  long minV = 1023, maxV = 0;
  
  for(int i=0; i<50; i++) { 
    int v = analogRead(PIN_RX);
    if(v < minV) minV = v;
    if(v > maxV) maxV = v;
  }
  int level = maxV - minV;

  if (level > THRESH_HIGH && !active) {
    long duration = millis() - lastTime;
    
    if (duration > (DOT_MS * 2)) {
      if (buffer.length() > 0) {
        String c = decode(buffer);
        if (c == "H") Serial.print(" ");
        Serial.print(c);
        buffer = ""; 
      }
    }
    lastTime = millis();
    active = true;
  }
  else if (level < THRESH_LOW && active) {
    long duration = millis() - lastTime;
    
    if (duration > (DOT_MS * 2.0)) buffer += "-"; 
    else buffer += "."; 
    
    lastTime = millis();
    active = false;
  }
}