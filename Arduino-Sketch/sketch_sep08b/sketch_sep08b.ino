

int switchState = 0;


void setup() {
 pinMode(2,INPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
}

void loop() {
  switchState = digitalRead(2);
  
  if( switchState = LOW){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}



else{
  delay(250);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  delay(250);
    }
  }
