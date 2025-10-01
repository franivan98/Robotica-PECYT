//Testeo de motores.
// Pin 6, 7 : MOTOR 1
// Pin 8, 9 : MOTOR 2
 
 void setup() {

}

void loop() {
    pinMode(3, OUTPUT);
     digitalWrite(3, 0);
    pinMode(4, OUTPUT);
     digitalWrite(4, 1);
    pinMode(5, OUTPUT);
     digitalWrite(5, 0);
    pinMode(6, OUTPUT);
     digitalWrite(6, 1);
    delay(1000);
    pinMode(3, OUTPUT);
     digitalWrite(3, 1);
    pinMode(4, OUTPUT);
     digitalWrite(4, 0);
    pinMode(5, OUTPUT);
     digitalWrite(5, 1);
    pinMode(6, OUTPUT);
     digitalWrite(6, 0);
    delay(1000);

} 
