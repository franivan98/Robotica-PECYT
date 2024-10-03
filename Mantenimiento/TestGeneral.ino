 // 3 a 6 pines de motores
 // pin 8 triger 
 // pin 9 echo
 // 11 a 13 pines de leds (semaforo) solo programamos con 11 y 12, 13 funciona a la par con el led integrado en el arduino
 
 // funcion ultrasonico distancia
 long ultrason_8() {
   long duration, distance;
   digitalWrite(8,LOW);
   delayMicroseconds(2);
   digitalWrite(8, HIGH);
   delayMicroseconds(10);
   digitalWrite(8, LOW);
   duration = pulseIn(9, HIGH);
   distance = duration/58;
   return distance;
}

// funcion motores con sensor ultrasonico
void Motor_y_Sensores() {
  if (ultrason_8() > 20) {
    pinMode(6, OUTPUT);
     digitalWrite(6, 1);
    pinMode(5, OUTPUT);
     digitalWrite(5, 0);
    pinMode(4, OUTPUT);
     digitalWrite(4, 0);
    pinMode(3, OUTPUT);
     digitalWrite(3, 1);
    digitalWrite(11, 1);
    digitalWrite(12, 0);
  } else {
    pinMode(6, OUTPUT);
     digitalWrite(6, 0);
    pinMode(5, OUTPUT);
     digitalWrite(5, 1);
    pinMode(4, OUTPUT);
     digitalWrite(4, 1);
    pinMode(3, OUTPUT);
     digitalWrite(3, 0);
    digitalWrite(11, 0);
    digitalWrite(12, 1);
  }
}

void setup() {
  // Ultrasonico
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  // Leds
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
    Motor_y_Sensores();
}