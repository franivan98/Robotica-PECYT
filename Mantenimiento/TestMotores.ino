//Testeo de motores.
// Pin 6, 7 : MOTOR 1
// Pin 8, 9 : MOTOR 2
 
 void setup() {

}

void loop() {
    pinMode(6, OUTPUT);
     digitalWrite(6, 0);
    pinMode(7, OUTPUT);
     digitalWrite(7, 1);
    pinMode(8, OUTPUT);
     digitalWrite(8, 0);
    pinMode(9, OUTPUT);
     digitalWrite(9, 1);
    delay(1000);
    pinMode(6, OUTPUT);
     digitalWrite(6, 1);
    pinMode(7, OUTPUT);
     digitalWrite(7, 0);
    pinMode(8, OUTPUT);
     digitalWrite(8, 1);
    pinMode(9, OUTPUT);
     digitalWrite(9, 0);
    delay(1000);

} 
