
#include<Wire.h> // Importa la libreria per comunicare con l'accelerometro tramite protocollo I2C

const int MPU=0x68;  // I2C indirizzo dell' MPU-6050

int cnt;
int somma;
float media;
int  switchState; 
int prevTime;
int time;
int tempoRespiro;
int  prevSwitchState = 0;
int numero_respiri = 0;
int numero_inspirazioni = 0;
int numero_espirazioni = 0;
int numero_respiri2 = 0;
float frequenza;
//SETUP
void setup(){
  //Avvio e imposto la comunicazione con l'accelerometro usando il protocollo I2C
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // Setto l'ndirizzo 
  Wire.write(0);     // Invio un bit per avviare la comunicazione con lo slave (wakes up the MPU-6050)
  Wire.endTransmission(true);
  //
  
  //Avvio la comunicazione con il monitor seriale
  Serial.begin(9600);
  //
}
//LOOP
void loop(){
  //Funzione millis che tiene traccia del tempo trascorso
time = millis();
  //Avvio una comunicazione tra MASTER(arduino) e SLAVE(accelerometro)
  Wire.beginTransmission(MPU);
  Wire.write(0x3D);  // Starting with register 0x3F (ACCEL_ZOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,2,true);  // Request a total of 2 registers
  //
  switchState = (Wire.read()<<8|Wire.read())/3000; 
  
        if ( switchState > prevSwitchState ) {
          tempoRespiro = time - prevTime;
          
          numero_inspirazioni++;
          }  
        if ( switchState < prevSwitchState ) {
          prevTime = time;
          numero_espirazioni++;
          numero_respiri++;
          }
       
        frequenza = 60000/tempoRespiro; 
        prevSwitchState = switchState;
        cnt++;
  Serial.print("Tempo ultimo respiro: ");Serial.println(tempoRespiro);
  Serial.print("Numero inspirazini ");Serial.println(numero_inspirazioni);
  Serial.print("Numero espirazioni ");Serial.println(numero_espirazioni);
  Serial.print("Numero respirazioni ");Serial.println(numero_respiri);
  Serial.print("Valori accelerometro ");Serial.println(switchState);
  Serial.print("Frequenza Respiratoria ");Serial.print(frequenza);Serial.println(" respiri/min");   
  delay(300);
}
