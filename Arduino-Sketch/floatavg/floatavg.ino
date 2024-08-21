
#include<Wire.h> // Importa la libreria per comunicare con l'accelerometro tramite protocollo I2C

const int MPU=0x68;  // I2C indirizzo dell' MPU-6050


int16_t AcX,AcY,AcZ,Tmp; // Inizializzo le variabili intere AcX, AcY, AcZ, Tmp

int valori[5]; //Array in cui ci salvi i valori letti
int T_campionamento;
int somma;
float media;

float avg(){
    for(int i = 0; i<5; i++){
    
  valori[i]=(Wire.read()<<8|Wire.read())/1000;  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L
  delay(T_campionamento);
  //
 }
 somma = 0;
 for( int j = 0; j < 5; j++){
   somma = somma + valori[j];
   }
   
   media = somma/5;
  return media;
  }
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
  //
  
  //Avvio una comunicazione tra MASTER(arduino) e SLAVE(accelerometro)
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // Request a total of 14 registers
  //
  
  //Leggo i dati forniti dall'accelerometro
   Serial.println(avg());
   delay(500);
}


