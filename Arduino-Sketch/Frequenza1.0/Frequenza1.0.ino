extern unsigned long timer0_millis;

int switchState; 
int tempoRespiro;
int prevSwitchState = 0;
int numero_respiri = 0;
int numero_inspirazioni = 0;
int numero_espirazioni = 0;
int numero_respiri2 = 0;
float frequenza;

void resetMillis() {
  cli();
  timer0_millis = 0;
  sei();
}

float Frequenza(int A){

  switchState = A;
  
        if ( switchState > prevSwitchState ) {
          resetMillis();
          numero_inspirazioni++;
          }  
        if ( switchState < prevSwitchState ) {
          tempoRespiro = millis();
          numero_espirazioni++;
          numero_respiri++;
          }
        return frequenza = 60000/tempoRespiro; 
        prevSwitchState = switchState;
        
  Serial.println(tempoRespiro);
  Serial.print("Numero inspirazini ");Serial.println(numero_inspirazioni);
  Serial.print("Numero espirazioni ");Serial.println(numero_espirazioni);
  Serial.print("Numero respirazioni ");Serial.println(numero_respiri);
  Serial.print("Valori accelerometro ");Serial.println(switchState);
  Serial.print("Frequenza Respiratoria ");Serial.print(frequenza);Serial.println(" respiri/min");   
  delay(300);
}
