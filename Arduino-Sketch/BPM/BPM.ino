int threshold = 60;
int oldvalue = 0;
int newvalue = 0;
unsigned long oldmillis = 0;
unsigned long newmillis = 0;
int cnt = 0;
int timings[16];

void setup() {
  Serial.begin(57600);
}

void loop() {
    Serial.println(cnt%16);
    cnt++;
    delay(500);
  }
 
