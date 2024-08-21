
const int sensorPin = A0;
const int motorPin = 9;
const float baselineTemp = 19;

void setup() {
 Serial.begin(9600);
 pinMode(motorPin, OUTPUT);

}

void loop() {
  int sensorVal = analogRead(sensorPin);
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  
  float voltage = (sensorVal/1024.0)*5.0;
  
  Serial.print(", volts: ");
  Serial.print(voltage);
  
  Serial.print(", degrees C: ");
  
  float temperature = (voltage - .5)*100;
  Serial.println(temperature);
  
  if(temperature > baselineTemp){
    digitalWrite(motorPin, HIGH);
}
   else{
     digitalWrite(motorPin, LOW);
     }
     
     }
   
