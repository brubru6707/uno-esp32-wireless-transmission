const int PIN = A0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN, INPUT);
}

void loop() {
  long minV = 1023, maxV = 0;
  
  for(int i=0; i<400; i++) { 
    int v = analogRead(PIN);
    if(v < minV) minV = v;
    if(v > maxV) maxV = v;
  }
  
  int noise = maxV - minV;
  Serial.println(noise);
}