#include<Wire.h>
const int MPU=0x68;  // I2C indirizzo del registro dell'MPU6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; // Inizializzo le variabili che conterranno gli output del sensore

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // Indirizzo del registro che contiene il bit che avvia la comunicazione
  Wire.write(0);     // Inviamo un bit per avviare la comunicazione
  Wire.endTransmission(true); // Chiudiamo la comunicazione
  Serial.begin(9600); // Avviamo in monitor seriale con velocità di 9600 baud/s
}

float M1(int16_t x){
  float y = x;
  return (y*2)/(32768);
}
float M2(int16_t x){
  float y = x;
  return (y*250)/(32768);
}

void loop(){
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  //Partiamo dal registro 0x3B che contiene i dati relativi all'asse x dell'accelerometro
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // richiediamo la lettura di 14 registri
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Stampiamo i dati relativi ai tre assi dell'accelerometro:
  Serial.print("Accelerometro: ");
  Serial.print("X = "); Serial.print(M1(AcX));
  Serial.print(" | Y = "); Serial.print(M1(AcY));
  Serial.print(" | Z = "); Serial.print(M1(AcZ));Serial.println("   [g]");
  //Dal DS convertiamo la temperatura in C°
  Serial.print("Temperatura: "); Serial.print(Tmp/340.00+36.53); Serial.println(" C "); 

  //Stampiamo i dati relativi ai tre assi del giroscopio:
  Serial.print("Gyroscopio: ");
  Serial.print("X = "); Serial.print(M2(GyX));
  Serial.print(" | Y = "); Serial.print(M2(GyY));
  Serial.print(" | Z = "); Serial.print(M2(GyZ));Serial.println("  [gradi/s]");
  Serial.println(" ");
  
  // Ritardiamo di 100 ms ogni giro del loop per evitare overflow
  delay(100);
}
