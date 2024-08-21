
float Valore_analogico;
float Volt;
float Temperatura;

void setup() {
 Serial.begin(9600); // Avvio comunicazione seriale
}

void loop() {
  Valore_analogico = analogRead(A0); // Lettura del valore analogico
  Volt = (Valore_analogico/1024)*5000; // Conversione in volt
  Temperatura = Volt/10; // Conversione in C°
  
  Serial.print(Temperatura);Serial.println(" C"); // Stampa sul monitor la temperatura espressa in gradi Celsius
}

