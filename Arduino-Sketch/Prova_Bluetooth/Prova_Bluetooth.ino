 //Includo libreria SoftwareSerial
 #include <SoftwareSerial.h>
 
//definisco pin RX e TX da Arduino verso modulo BT
#define BT_TX_PIN 12
#define BT_RX_PIN 11
 
//istanzio oggetto SoftwareSerial (il nostro futuro bluetooth)
SoftwareSerial bt =  SoftwareSerial(BT_RX_PIN, BT_TX_PIN);
String message;
const int Led = 13;
void setup() {
 
  //definisco modalità pin
  pinMode(BT_RX_PIN, INPUT);
  pinMode(BT_TX_PIN, OUTPUT);
 
  //inizializzo comunicazione Seriale
  Serial.begin(9600);
 
  //inizializzo comunicazione Bluetooth
  bt.begin(9600);
 
}
void loop() {
           bt.println("ciao");
       delay(500); //delay 
    }
