#include<Wire.h> // Importa la libreria per comunicare con l'accelerometro tramite protocollo I2C

const int MPU=0x68;  // I2C indirizzo dell' MPU-6050


int16_t AcX,AcY,AcZ,Tmp; // Inizializzo le variabili intere AcX, AcY, AcZ, Tmp

float celsius = 0 ; // Inizializzo la variabile flottante celsius

float millivolts; // Inizializzo la variabile flottante millivolts

int sensor; // Inizializzo la variabile intera sensor


unsigned long time = 0;  // Inizializzo la variabile unsigned di tipo long a 32 bit per time

unsigned long courrentTime = 0;  //Inizializzo la variabile unsigned di tipo long a 32 bit per courrentTime

unsigned long previousTime = 0; //Inizializzo la variabile unsigned di tipo long a 32 bit per previousTime

int switchState [1]; //Inizializzo la variabile intera switchState

int prevSwitchState [1]; //Inizializzo la variabile intera prevSwitchState

int deadline = 7000; //Inizializzo la variabile intera deadline

//SETUP
void setup(){
  //Setto il pin 2 e 3 ( LED ROSSO e LED VERDE ) come output
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);
  // 
  
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

// Metodo per la lettura della temperatura del bambino: per prima cosa leggo i valori del sensore. PoichÃƒÂ¨ leggo un valore analogico, sarÃƒÂ  compreso tra 0 e 1023. Sottraendo
//a questo valore 0.5(massima accuratezza) e dividendo dunque questo valore per 1024 e moltiplicandolo per la tensione ai capi dell'LM5(5000 millivolts) ottengo la sua 
//tensione in millivolts. PoichÃƒÂ¨ il sensore restituisce 10mV per grado
//basta dividere il valore per 10 per ottenere la temperatura in CÃ‚Â°.
float BabyTemperature(){
  sensor = analogRead(A0);
  millivolts = (sensor/1024.0)*5000.0;
  celsius  = (millivolts-.5)/10;
  return celsius;
  }
//

//LOOP
void loop(){
  //Funzione millis che tiene traccia del tempo trascorso
  time = millis();
  //
  
  //Avvio una comunicazione tra MASTER(arduino) e SLAVE(accelerometro)
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // Request a total of 14 registers
  //
  
  //Leggo i dati forniti dall'accelerometro
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  //
  Serial.print("AcX:");Serial.print(AcX);Serial.print("AcY:");Serial.print(AcY);
  // FILTRAGGIO DEL SEGNALE; CONTROLLORE
  switchState [0] = AcX;
  switchState [1] = AcY;
  
  for(int j = 0; j<2 ; j++){
    for(int k = 0; k<2 ; k++){
      if( j == k){
  if(switchState[j] == prevSwitchState[k]){
    courrentTime = time - previousTime;
      }
  if(switchState[j] != prevSwitchState[k]){
      previousTime = time;
      }
   prevSwitchState[k] = switchState[j];
   //Serial.println(prevSwitchState[k]);
   //Serial.println(switchState[j]);
   
   }
  }
 }
      
             
   if( courrentTime < deadline ){
   digitalWrite(3, HIGH);
   digitalWrite(2, LOW);

   }
 if( courrentTime > deadline){
   digitalWrite(3, LOW);
   digitalWrite(2, HIGH);
   delay(100);
   digitalWrite(2,LOW);
   delay(100);
   //tone(4,300,1000);
   }
   
  //
 // Stampo su monitor la temperatura del bambino e  i valori estrapolati dall'accelerometro 
 // Serial.print("Baby's Temperature: ");  Serial.print(BabyTemperature()); Serial.print(" C° ");
 // Serial.print(" Accelerometer: ");
 // Serial.print("X = "); Serial.print(AcX/1000);
 // Serial.print(" | Y = "); Serial.print(AcY/1000);
  Serial.print(" | Z = "); Serial.println(AcZ);
 // 
 //Serial.println(courrentTime);
  //Stampo su monitor la temperatura della stanza. PoichÃƒÂ¨ il sensore si trova sull'accelerometro, uso  l'equazione che mi da il DS per trasdurre volts in celsius 
  //Serial.print("Room Temperature: "); Serial.print(Tmp/340.00+36.53); Serial.println(" C° "); 
  
  //Ritardo di mezzo secondo il loop 
  delay(500);
  
}


