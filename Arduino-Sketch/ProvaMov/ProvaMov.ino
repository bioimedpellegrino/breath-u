int switchState = 0;
int pitch = 300;
int deadline = 5000;
int courrentTime = 0;

int previousTime = 0;
void setup() {
  Serial.begin(9600);
pinMode(6, INPUT);
pinMode(4, OUTPUT);
pinMode(2, OUTPUT);
digitalWrite(4, HIGH);
}

void loop() {
  
  switchState = digitalRead(6);
  
  if ( switchState == HIGH){
       
  if( switchState == LOW){
    courrentTime = millis();
    if(courrentTime-previousTime > deadline){
      
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  tone(8,pitch,3000);
        }
    }
    
   courrentTime = previousTime; 
   
   Serial.print("Courrent Time: ");
    Serial.print(courrentTime);
    Serial.println("Previous Time");
    Serial.println(previousTime);
 }
 
 

