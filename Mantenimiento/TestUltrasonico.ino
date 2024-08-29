const int trigPin = 8;
const int echoPin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Limpiar el pin trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Iniciar la medición enviando un pulso de 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer la duración del pulso desde el pin echo
  long duration = pulseIn(echoPin, HIGH);

  // Convertir la duración del pulso en distancia (cm)
  float distance_cm = duration * 0.034 / 2;

  // Imprimir la distancia por el puerto serie
  Serial.print("Distancia: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Esperar 500 milisegundos antes de la próxima medición
  delay(200);
}
