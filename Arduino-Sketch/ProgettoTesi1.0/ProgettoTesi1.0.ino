/*



Progetto dispositivo per il monitoraggio del respiro

Author: Alessandro Pellegrino 

Aggiornato al 13/12/2016



*/




#include<Wire.h> // Importa la libreria per comunicare con l'accelerometro tramite protocollo I2C

extern unsigned long timer0_millis; // Variabile esterna necessaria per il funzionamento del metodo resetMillis()

const int MPU=0x68;  // I2C indirizzo dell' MPU-6050

int16_t Acc,Tmp; // Inizializzo le variabili intere AcX, AcY, AcZ, Tmp

/*---------------VARIABILI GLOBALI RELATIVE AL METODO Babytemperature()--------------*/

float celsius = 0 ; // Inizializzo la variabile flottante celsius

float millivolts; // Inizializzo la variabile flottante millivolts

int LM35; //Inizializzo la variabile flottante LM35

/*----------VAARIABILI RELATIVE AL CONTROLLO E AL FILTRAGGIO DEI VALORI DELL'ACCELEROMETRO--------*/

unsigned long time, courrent_Time, previous_Time = 0;  // Inizializzo la variabili unsigned di tipo long a 32 bit 

float courrent_Value, previous_Value = 0; //Inizializzo le variabili intere courrent_Value e previous_Value

int deadline = 10000; //Inizializzo la variabile intera deadline con valore 10000

int valori[5]; //Inizializzo l'array in cui salvo i valori letti dall'accelerometro

int T_campionamento = 10; //Inizializzo la variabile Tempo di Campionamento

int somma; //Inizializzo la variabile intera somma

float media; //Inizializzo la variabile flottante media

/*---------VARIABILI GLOBALI RELATIVE AL METODO Frequenza()---------*/

int f_time, f_prevTime, value , pr_value , tempoRespiro , numero_respiri , numero_inspirazioni , numero_espirazioni = 0; // Inizializzo le variabili intere

float frequenza; //Inizializzo la variabile flottante media

                                                /**********************-------INIZIO SETUP-------**********************/
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

  
//Avvio la comunicazione con il monitor seriale
Serial.begin(57600);
//
}                                               /**********************-------FINE SETUP-------**********************/



/* Metodo per la lettura della temperatura del bambino: per prima cosa leggo i valori del sensore. Poiche' leggo un valore analogico, sara'  compreso tra 0 e 1023. Sottraendo
a questo valore 0.5(massima accuratezza) e dividendo dunque questo valore per 1024 e moltiplicandolo per la tensione ai capi dell'LM5(5000 millivolts) ottengo la sua 
tensione in millivolts. Poiche' il sensore restituisce 10mV per grado
basta dividere il valore per 10 per ottenere la temperatura in C°. 
*/

float BabyTemperature(){
  LM35 = analogRead(A0);
  millivolts = (LM35/1024.0)*5000.0;
  celsius  = (millivolts-.5)/10;
  return celsius;
}


/* Metodo per  richiedere all'accelerometro i dati relativi all'accelerazione.
L'indirizzo in questione è 0x3F
*/
int AccRequest(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3F);   //Comincia a registrare dall'indirizzo 0x3F (ACCEL_ZOUT_H) (AcZ)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,2,true);   //Richiesta di 2 registrazioni 
  return Acc = (Wire.read()<<8|Wire.read())/1000;
}
  
  
/* Metodo per  richiedere all'accelerometro i dati relativi alla temperatura.
L'indirizzo in questione è 0x41
*/ 
float RoomTemperature(){
  Wire.beginTransmission(MPU);
  Wire.write(0x41);  // Starting with register 0x3F (ACCEL_ZOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,2,true);
  Tmp = ((Wire.read()<<8|Wire.read())/340)+33.53;
  return Tmp;
  }

 
 /*
 Metodo per calcolare la frequenza di respirazione.
 */
float Frequenza(int A, int B){
 
value = A;
f_time = B;

if ( value > pr_value ) {
     tempoRespiro = f_time - f_prevTime;  // bisogna rimuovere questa funzione e utilizzare lo stesso metodo usato per i respiri
     numero_inspirazioni++;
     }  
      if ( value < pr_value ) {
          f_prevTime = f_time;
          numero_espirazioni++;
          numero_respiri++;
          }
           frequenza = 60000/tempoRespiro; 
           pr_value = value;
        
Serial.print("Duration of breath: ");Serial.print(tempoRespiro);Serial.println(" ms ");
Serial.print("Number of inspirations: ");Serial.println(numero_inspirazioni);
Serial.print("Number of exhalations: ");Serial.println(numero_espirazioni);
Serial.print("Number of breaths: ");Serial.println(numero_respiri);
Serial.print("Breath frequency: ");Serial.print(frequenza);Serial.println(" respiri/min");   
return frequenza;
delay(150);
}
  
                                                /**********************-------INIZIO LOOP-------**********************/
void loop(){
  //Funzione millis che tiene traccia del tempo trascorso
  time = millis();
  //
    
  /* FILTRAGGIO DEL SEGNALE-CONTROLLORE
  Salvo i valori dell'accelerometro (divisi per 1000) su un array per poi fare la media ogni 5 acquisizioni. In questo modo i valori da gestire sono stabili.
  Successivamente salvo il dato su una variabile e lo confronto con il dato acquisito nel loop precedente.  Se sono diversi c'è stato movimento e ad ogni movimento  
  rilevato il cronometro si azzera. Se invece i dati sono uguali, non c'è stato movimento e
  il cronometro continua a scorrere. Se il cronometro supera i 10 s, scatta l'allarme.
  */
   for( int i = 0 ; i < 5 ; i++ ){
       valori[i]=AccRequest();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L
       delay(T_campionamento);
       }
        somma = 0;
        for( int j = 0 ; j < 5 ; j++ ){
            somma = somma + valori[j];
            }
        media = somma/5;
        courrent_Value = media;
  
            if(courrent_Value == previous_Value){
               courrent_Time = time - previous_Time;
               }
      
                if(courrent_Value != previous_Value){
                   previous_Time = time;
                   }
                   
        previous_Value = courrent_Value;
        
        delay(10);
        
        if( courrent_Time < deadline ){
           digitalWrite(3, HIGH);
           digitalWrite(2, LOW);
           }
   
            if( courrent_Time > deadline){
               digitalWrite(3, LOW);
               digitalWrite(2, HIGH);
               tone(4,147,100);
               delay(50);
               }  
 
delay(50);
Frequenza(media,time); 
//Stampo su monitor la temperatura del bambino e  i valori estrapolati dall'accelerometro 

Serial.print(" Accelerometer value: "); Serial.println(media);
Serial.print(" Time elapsed since the last movement : ");Serial.print(courrent_Time/1000);Serial.println(" s ");

//Stampo su monitor la temperatura della stanza e del bambino. 
Serial.print("Room Temperature: ");Serial.print(RoomTemperature()); Serial.println(" C "); 
Serial.print("Baby's Temperature: ");Serial.print(BabyTemperature()); Serial.println(" C ");
Serial.println(" ");
//Ritardo di mezzo secondo il loop 
delay(500);
}                                               /**********************-------FINE LOOP-------**********************/


