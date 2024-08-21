
/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2012 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// Include la libreria I2C
#include "I2Cdev.h"

//Include la libreria "MPU6050.h" 
#include "MPU6050_6Axis_MotionApps20.h"


// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
  #endif

MPU6050 mpu;



#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// VARIABILI DATI OUTPUT
float off_ax , off_ay , off_az , off_gx , off_gy , off_gz ;
int16_t ax, ay, az;
int16_t gx, gy, gz;
float A_x,A_y,A_z,G_x,G_y,G_z;

//VARIABILI UTILI PER IL MONITORAGGIO
unsigned long tempo, t_t_mov, t_u_mov = 0;  // Inizializzo la variabili unsigned di tipo long a 32 bit
int t_ins ,t_ins_real,t_esp_real, t_esp , t_resp , timer_i , timer_e = 0 ;
int frequenza_resp;
int Deadline = 10000;
// ================================================================
// ===               METODI UTILI                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}
// ================================================================
// ===                       SETUP                       ===
// ================================================================



void setup() {
  // ================================================================
// ===PARTE DI CODICE RELATIVA AL CORRETTO FUNZIONAMENTO DEL DMP
// ================================================================

    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(57600);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
    // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
    // the baud timing being too misaligned with processor ticks. You must use
    // 38400 or slower in these cases, or use some kind of external separate
    // crystal solution for the UART timer.

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // wait for ready
   // Serial.println(F("\n Send any character to begin DMP programming and demo: "));
 //   while (Serial.available() && Serial.read()); // empty buffer
   // while (!Serial.available());                 // wait for data
   // while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
// Calcolo degli off_set
            for ( int i = 0 ; i < 30 ; i++ ){
            mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
            off_ax = off_ax + ax;
            off_ay = off_ay + ay;
            off_az = off_az + az;
            off_gx = off_gx + gx;
            off_gy = off_gy + gy;
            off_gz = off_gz + gz;
            }
            off_ax = off_ax/491520;
            off_ay = off_ay/491520;
            off_az = off_az/491520;
            off_gx = off_gx/3932.16;
            off_gy = off_gy/3932.16;
            off_gz = off_gz/3932.16;
// Stampo su monitor serial gli offset
           Serial.print("Offset: ");
            Serial.print(off_ax);
            Serial.print("\t");
            Serial.print(off_ay);
            Serial.print("\t");
            Serial.print(off_az);
            Serial.print("\t");
            Serial.print(off_gx);
            Serial.print("\t");
            Serial.print(off_gy);
            Serial.print("\t");
            Serial.println(off_gz); 

    // SETTO I PIN D'INTERESE COME OUTPUT. 
    pinMode(LED_PIN, OUTPUT);
    pinMode(3, OUTPUT); //LED BLU
    pinMode(4, OUTPUT); //LED ROSSO
   // pinMode(5, OUTPUT); //PIEZO
}



// ================================================================
// ===                      LOOP                     ===
// ================================================================

void loop() {

    // se il DMP non è pronto, non eseguire nulla
    if (!dmpReady) return;

    // aspetta il primo interrupt
    while (!mpuInterrupt && fifoCount < packetSize) {
      
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // metodo per contare i FIFO
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
      //  Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

//------COMPENSAZIONE VALORI------
/* Utilizzando il DMP(Digital Motion Processor) interno dell'MPU6050 ottengo già i valori filtrati con il filtro di Kalman */
       
            mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); //Comando per richiedere i valori dell'accelerometro e del giroscopio processati dal DMP
              A_x = ax;
              A_y = ay;
              A_z = az;
              G_x = gx;
              G_y = gy;
              G_z = gz;
/* Divido il valore ottenuto per 16384. Questo perchè il sensore è di 16 bit e quindi il range dei valori è  [-32768;+32768]. Essendo i valori di fondo scala "+/-2g"
per l'accelerometro e "+/-250 gradi/s" per il giroscopio, la più piccola variazione o risoluzione si calcola come range di misura diviso il valore di fondo scala.
Per l'accelerometro avrò 32768/2 = 16384;
Per il giroscopio invece 32768/250 = 131.072;
Dividendo quindi i valori forniti dai sensori per i valori appena ottenuti avremo i valori nelle loro rispettive unità di misura.
Successivamente sottraggo l'offset precedentemente calcolato */
            A_x = (A_x/16384)- off_ax;
            A_y = (A_y/16384) - off_ay;
            A_z = (A_z/16384) - off_az;
            G_x = (G_x/131.072) - off_gx;
            G_y = (G_y/131.072) - off_gy;
            G_z = (G_z/131.072) - off_gz;
//------FINE COMPENSAZIONE VALORI------

/*A questo punto avremo i valori filtrati e in qualunque posizione si trovi il sensore i suoi valori da fermo saranno settati a 0. Finita questa parte di 
filtraggio del segnale possiamo occuparci del controllo*/

//------INIZIO MONITORAGGIO------
    tempo = millis ();
    
 if( G_x > 0.6 ){
 timer_i = tempo;
 t_ins = tempo - timer_e;
 t_esp_real = t_esp;
 //Serial.print("Fase inspiratoria ");Serial.print(" ");Serial.println(t_ins);  
 }
 if(G_x < -0.6 ){
 timer_e = tempo;
 t_esp = tempo - timer_i;
 t_ins_real = t_ins;
 //Serial.print("Fase espiratoria ");Serial.print(" ");Serial.println(t_esp);
 }
 
 if ( G_x < -0.6 || G_x > 0.6) {
  t_u_mov = tempo;
}

if ( G_x > -0.55 && G_x < 0.55 ){
  t_t_mov = tempo - t_u_mov;
}

if(t_t_mov > 5000){
 Serial.print("Nessun movimento rilevato da ");Serial.print(t_t_mov/1000);Serial.println(" s ");
}

if ( t_t_mov < Deadline ) {
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
}
if ( t_t_mov > Deadline ) {
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
 // tone(5,150,100);
}

t_resp = t_ins_real + t_esp_real;
frequenza_resp= 60000/(t_resp);

Serial.print("Frequenza Respiratoria ");Serial.print(frequenza_resp);Serial.print(" respiri/min ");Serial.println(" ");
//Serial.print("Durata ultimo respiro ");Serial.print(t_resp);Serial.println(" s ");
 
// Stampo sul monitor i valori aventi come unit di misura "g" per i valori forniti dall'accelerometro e "gradi/s" per i valori forniti dal giroscopio.
            /*Serial.print("ax,ay,az \t");
            Serial.print(A_x);
            Serial.print("\t");
            Serial.print(A_y);
            Serial.print("\t");
            Serial.print(A_z);
            Serial.print("\t");
            Serial.print(" g ") ;
            Serial.print("\t"); 
            Serial.print("gx,gy,gz \t"); */
           Serial.println(G_x);
        /*    Serial.print("\t");
            Serial.print(G_y);
            Serial.print("\t");
            Serial.print(G_z);
            Serial.print("\t"); */
           //Serial.println(" gradi/s");  
        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
        
    }
    delay(50);
}
