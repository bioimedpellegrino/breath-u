void setup() {
  Serial.begin(115200);

}

void loop() {
  int vibrazioni = analogRead(A0);
  Serial.println(vibrazioni);
  delay(10);

}
