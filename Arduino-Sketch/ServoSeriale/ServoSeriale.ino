
#include <Servo.h>

Servo myServo;
int val = 10;
int angle;
void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}

void loop() {

  for(int i = 0; i < 10; i++){
  myServo.write(val);
  val += 5;
  delay(1000);
  }
  
  for(int i = 0; i < 10; i++){
  myServo.write(val);
  val -= 5;
  delay(1000);
  }
}
