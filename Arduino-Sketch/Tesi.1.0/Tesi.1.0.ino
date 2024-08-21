
int time = 0;
int courrentTime = 0;
int previousTime = 0;
int switchState = 0;
int deadline = 5000;
void setup() {
 Serial.begin(9600);
 pinMode(2, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(6, INPUT);
 
}

void loop() {
  time = millis();
  switchState = digitalRead(6);
  if(switchState == HIGH){
      courrentTime = time - previousTime;
      Serial.println(courrentTime);
 }
 if(switchState == LOW){
   previousTime = time;
   }
 if( courrentTime < deadline){
   digitalWrite(4, HIGH);
   digitalWrite(2, LOW);
   }
 if( courrentTime > deadline){
   digitalWrite(4, LOW);
   digitalWrite(2, HIGH);
   tone(8,300,1000);
   }
}
