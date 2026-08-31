#include <SoftwareSerial.h>

#define MOTORA_1 2
#define MOTORA_2 3
#define MOTORB_1 4
#define MOTORB_2 5

const int TX = 6;
const int RX = 7;

SoftwareSerial BT(RX, TX); 

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);
}

void setupVel(int v)
{
  analogWrite(9, v);
  analogWrite(10, v);
}

void forward()
{
  setupVel(255);
  digitalWrite(MOTORA_1, 1);
  digitalWrite(MOTORA_2, 0);
  digitalWrite(MOTORB_1, 1);
  digitalWrite(MOTORB_2, 0);
}

void backward()
{
  setupVel(200);
  digitalWrite(MOTORA_1, 0);
  digitalWrite(MOTORA_2, 1);
  digitalWrite(MOTORB_1, 0);
  digitalWrite(MOTORB_2, 1);
}

void left()
{
  setupVel(125);
  digitalWrite(MOTORA_1, 1);
  digitalWrite(MOTORA_2, 0);
  digitalWrite(MOTORB_1, 0);
  digitalWrite(MOTORB_2, 1);
}

void right()
{ 
  setupVel(125);
  digitalWrite(MOTORA_1, 0);
  digitalWrite(MOTORA_2, 1);
  digitalWrite(MOTORB_1, 1);
  digitalWrite(MOTORB_2, 0);
}

void stop()
{
  digitalWrite(MOTORA_1, 0);
  digitalWrite(MOTORA_2, 0);
  digitalWrite(MOTORB_1, 0);
  digitalWrite(MOTORB_2, 0);
}

void loop() {

  if (BT.available())
  {
    char comando = BT.read();

    Serial.println(comando);

    if (comando == 'w')
    {
      forward();
    }
    else if (comando == 's')
    {
      backward();
    }
    else if (comando == 'a')
    {
      left();
    }
    else if (comando == 'd')
    {
      right();
    }
    else
    {
      stop();
    }
  }
}
