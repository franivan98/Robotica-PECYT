 // 3 a 6 pines de motores
 // pin 8 triger 
 // pin 9 echo
 // 11 a 13 pines de leds (semaforo) solo programamos con 11 y 12, 13 funciona a la par con el led integrado en el arduino
 
 // Pines LED
#define GREEN_LED 11
#define YELLOW_LED 12
#define RED_LED 13
//  Pines ultrasonico
#define TRIG_PIN 8
#define ECHO_PIN 9
//  Pines motores
//  Motor A
#define MOTORA_1 3
#define MOTORA_2 4
//  Motor B
#define MOTORB_1 5
#define MOTORB_2 6

 // Funcion ultrasonico distancia
 long ultrason_8() {
   long duration, distance;
   digitalWrite(TRIG_PIN,LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
   duration = pulseIn(ECHO_PIN, HIGH);
   distance = duration/58;
   return distance;
}

// Led VERDE (11) encendido (apaga el resto):
void only_green(){
  digitalWrite(GREEN_LED, 1);
  digitalWrite(YELLOW_LED, 0);
  digitalWrite(RED_LED, 0);
}

// Led AMARILLO (12) encendido (apaga el resto):
void only_yellow(){
  digitalWrite(GREEN_LED, 0);
  digitalWrite(YELLOW_LED, 1);
  digitalWrite(RED_LED, 0);
}

// Led ROJO (13) encendido (apaga el resto):
void only_red(){
  digitalWrite(GREEN_LED , 0);
  digitalWrite(YELLOW_LED, 0);
  digitalWrite(RED_LED, 1);
}

// Función ADELANTE
void forward(){
  // Rueda IZQUIERDA:
  digitalWrite(6, 0);
  digitalWrite(5, 1);
  // Rueda DERECHA:
  digitalWrite(4, 0);
  digitalWrite(3, 1);
  // Enciende verde
  //only_green();
}

// Función GIRAR
void turn(){
  // Rueda IZQUIERDA:
  digitalWrite(MOTORA_1, 1);
  digitalWrite(MOTORA_2, 0);
  // Rueda DERECHA:
  digitalWrite(MOTORB_1, 0);
  digitalWrite(MOTORB_2, 1);
  // Enciende el amarillo
  //only_yellow();
}

// Función PARAR
void stop(){
  // Rueda IZQUIERDA:
  digitalWrite(MOTORA_1, 0);
  digitalWrite(MOTORA_2, 0);
  // Rueda DERECHA:
  digitalWrite(MOTORB_1, 0);
  digitalWrite(MOTORB_2, 0);
  // Enciende el rojo
  //only_red();
}

// Funcion motores con sensor ultrasonico:
void dodge() {
  // Si el sensor está a una distancia MAYOR a (>) 20cm, entonces:
  if (ultrason_8() > 20) {
    //Va hacia ADELANTE
    forward();
  } 
  // De lo contrario (si está a una distancia MENOR a 20cm):
  else {
    // Que ESPERE y prenda el LED ROJO por 2 SEGUNDOS:
    stop();
    delay(1000);
    // Que GIRE y prenda el LED AMARILLO por 2 SEGUNDOS:
    turn();
    delay(75);
  }
}

void setup() {
  // Motores
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);

  // Ultrasonico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Leds
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
    dodge();
}