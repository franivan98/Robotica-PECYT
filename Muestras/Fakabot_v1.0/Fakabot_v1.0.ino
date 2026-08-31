#include <SoftwareSerial.h>
SoftwareSerial Pblue(6,7);
//pines
int ledPin=13;
//motor izquierdo
int motor1_1=3;
int motor1_2=2;
//motor derecho
int motor2_1=4;
int motor2_2=5;
int buzzer=11;

void setup() {
  pinMode(ledPin,OUTPUT);
  //pines motor 1
  pinMode(motor1_1,OUTPUT);
  pinMode(motor1_2,OUTPUT);
  //pines motor2
  pinMode(motor2_1,OUTPUT);
  pinMode(motor2_2,OUTPUT);

  pinMode(buzzer,OUTPUT);
  //bluetooth
  delay(500);
  Serial.begin(9600);
  Pblue.begin(9600);
}

void loop() {
  if(Pblue.available()){
    char command=Pblue.read();
    switch(command){
      case 'w': adelante();break;
      case 'a': izquierda();break;
      case 'd': derecha();break;
      case 's': atras();break;
      case 'x': digitalWrite(ledPin,HIGH);break;
      case 'v': digitalWrite(ledPin,LOW);break;
      case 'c': digitalWrite(buzzer,HIGH);break;
      case '0': quieto(); 
         digitalWrite(buzzer,LOW);break;
    }
  }

}
void adelante(){
  digitalWrite(motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,HIGH);
  digitalWrite(motor2_2,LOW);
}

void atras(){
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,HIGH);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,HIGH);
}
void izquierda(){
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,HIGH);
  digitalWrite(motor2_1,HIGH);
  digitalWrite(motor2_2,LOW);
}
void derecha(){
  digitalWrite(motor1_1,HIGH);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,HIGH);
}
void quieto(){
  digitalWrite(motor1_1,LOW);
  digitalWrite(motor1_2,LOW);
  digitalWrite(motor2_1,LOW);
  digitalWrite(motor2_2,LOW);
}




