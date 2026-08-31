#include <Wire.h>
#include <LCD_1602_RUS.h>

LCD_1602_RUS lcd(0x27,16,2);

#define BUZZER 8  // Pin del buzzer

// --- Caracteres personalizados ---
byte heartFull[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte heartEmpty[] = {
  B00000,
  B01010,
  B10001,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000
};

byte smile[] = {
  B00000,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte wink[] = {
  B00000,
  B01000,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte arrow[] = {
  B00100,
  B00110,
  B11111,
  B11111,
  B00110,
  B00100,
  B00000,
  B00000
};

// --- Funciones de animación ---
void showMessage(String msg, int velocidad, int row) {
  for (int i=0; i<=msg.length(); i++) {
    lcd.setCursor(0,row);
    lcd.print(msg.substring(0,i));
    tone(BUZZER, 1000, 50); // beep corto por cada letra
    delay(velocidad);
  }
  delay(500);
}

void bounceText(String msg, int row, int speed) {
  int pos = 0;
  int dir = 1; 
  for (int i=0; i<30; i++) { 
    lcd.clear();
    lcd.setCursor(pos,row);
    lcd.print(msg);
    tone(BUZZER, 800, 80); // beep en cada rebote
    delay(speed);

    pos += dir;
    if (pos + msg.length() >= 16 || pos <= 0) {
      dir = -dir; 
      tone(BUZZER, 1500, 200); // beep más agudo al rebotar
    }
  }
}

void loadingBar(int row, int speed) {
  lcd.clear();
  lcd.setCursor(0,row);
  lcd.print("[");
  lcd.setCursor(15,row);
  lcd.print("]");

  for (int i=1; i<15; i++) {
    lcd.setCursor(i,row);
    lcd.print((char)255); 
    tone(BUZZER, 500 + i*50, 80); // sonido ascendente
    delay(speed);
  }
  delay(500);
  // mini “melodía” final 🎶
  tone(BUZZER, 1000, 200); delay(250);
  tone(BUZZER, 1200, 200); delay(250);
  tone(BUZZER, 1500, 300); delay(300);
}

void heartBeat(int times, int row) {
  for (int i=0; i<times; i++) {
    lcd.clear();
    lcd.setCursor(7,row);
    lcd.write(0); 
    tone(BUZZER, 600, 150); // bum
    delay(200);
    lcd.clear();
    lcd.setCursor(7,row);
    lcd.write(1); 
    tone(BUZZER, 400, 150); // bum-bum
    delay(300);
  }
}

void smileWink(int times, int row) {
  for (int i=0; i<times; i++) {
    lcd.clear();
    lcd.setCursor(7,row);
    lcd.write(2); 
    tone(BUZZER, 800, 200); // nota alegre
    delay(400);
    lcd.clear();
    lcd.setCursor(7,row);
    lcd.write(3); 
    tone(BUZZER, 1000, 200); // nota más aguda
    delay(400);
  }
}

void arrowMove(int row, int speed) {
  for (int pos=0; pos<16; pos++) {
    lcd.clear();
    lcd.setCursor(pos,row);
    lcd.write(4);
    tone(BUZZER, 200 + pos*50, 50); // sonido que sube
    delay(speed);
  }
}

// --- SETUP ---
void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(BUZZER, OUTPUT);

  lcd.createChar(0, heartFull);
  lcd.createChar(1, heartEmpty);
  lcd.createChar(2, smile);
  lcd.createChar(3, wink);
  lcd.createChar(4, arrow);
}

// --- LOOP ---
void loop() {
  showMessage("Hola Humano!",100,0);
  lcd.clear();
  showMessage("Bienvenido a la",100,0);
  showMessage("FCEFyN!!!!!!!!!",100,1);
  lcd.clear();
  showMessage("Veni a Jugar!:)",100,1);
  lcd.clear();

  heartBeat(3,0);
  smileWink(2,1);
  arrowMove(0,150);
  bounceText("Robotica!",1,150);
  loadingBar(0,150);
}
