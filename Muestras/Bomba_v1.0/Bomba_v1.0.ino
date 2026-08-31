#include <Wire.h>
#include <LCD_1602_RUS.h>
#include <Keypad.h>

#define BUZZER 13

LCD_1602_RUS lcd(0x27,16,2);

// --- Configuración del teclado matricial ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 10, 12, 11}; 
byte colPins[COLS] = {5, 6, 7, 8};    

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- Juego ---
struct Question {
  String text;
  char answer;
};

Question allQuestions[30] = {
  {"2+3=?", '5'}, {"1+4=?", '5'}, {"3+2=?", '5'}, {"5-2=?", '3'}, {"6-1=?", '5'},
  {"7-3=?", '4'}, {"8-2=?", '6'}, {"9-4=?", '5'}, {"10-6=?", '4'}, {"2*3=?", '6'},
  {"4*2=?", '8'}, {"6/2=?", '3'}, {"9/3=?", '3'}, {"12/4=?", '3'}, {"15/5=?", '3'},
  {"7+2=?", '9'}, {"8+1=?", '9'}, {"10-7=?", '3'}, {"14-9=?", '5'}, {"20/5=?", '4'},
  {"3*3=?", '9'}, {"5*2=?", '0'}, {"12-3=?", '9'}, {"11-2=?", '9'}, {"18/9=?", '2'},
  {"4+5=?", '9'}, {"6+3=?", '9'}, {"9-8=?", '1'}, {"8/4=?", '2'}, {"7*1=?", '7'}
};

// Preguntas seleccionadas para esta partida
Question gameQuestions[5];

int currentQuestion = 0;
int timeLeft = 60; 
unsigned long lastBeep = 0;

// --- Funciones ---
void showStatus() {
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(timeLeft);
  lcd.print("s Preg:");
  lcd.print(currentQuestion+1);
  lcd.print("/5   ");
}

void playBuzzer(int freq, int duration){
  tone(BUZZER, freq, duration);
  delay(duration);
  noTone(BUZZER);
}

void tickBuzzer() {
  unsigned long now = millis();
  int interval = (timeLeft > 10) ? 1000 : 300; 
  if(now - lastBeep >= interval) {
    lastBeep = now;
    tone(BUZZER, 1000, 100); 
  }
}

void explosionSound() {
  for(int f=1000; f>100; f-=50) {
    tone(BUZZER, f, 50);
    delay(60);
  }
  noTone(BUZZER);
}

void gameOver() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   BOOM!!   ");
  lcd.setCursor(0,1);
  lcd.print("Bomba exploto");
  explosionSound();
  delay(2000);
}

void gameWin() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BombaDESACTIVADA");
  lcd.setCursor(0,1);
  lcd.print("Felicidades!");
  for(int i=0;i<3;i++){
    playBuzzer(1200,200);
    delay(200);
  }
  delay(2000);
}

char getKeyInput() {
  char key = 0;
  while(!key) {
    key = keypad.getKey();
  }
  playBuzzer(800,100);
  return key;
}

void selectRandomQuestions() {
  bool used[30] = {false};
  for(int i=0; i<5; i++) {
    int idx;
    do {
      idx = random(0,30);
    } while(used[idx]);
    used[idx] = true;
    gameQuestions[i] = allQuestions[idx];
  }
}

// --- SETUP ---
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(BUZZER, OUTPUT);
  randomSeed(analogRead(A0)); // semilla aleatoria
}

// --- LOOP ---
void loop() {
  currentQuestion = 0;
  timeLeft = 60;
  lastBeep = millis();
  selectRandomQuestions();

  while(timeLeft > 0 && currentQuestion < 5) {
    lcd.clear();
    showStatus();
    lcd.setCursor(0,1);
    lcd.print(gameQuestions[currentQuestion].text);

    unsigned long start = millis();
    char key = 0;
    while(!key && (millis()-start)<1000) { 
      key = keypad.getKey();
      tickBuzzer(); 
    }

    if(key) {
      playBuzzer(800,100);
      if(key == gameQuestions[currentQuestion].answer) {
        currentQuestion++;
        playBuzzer(1500,150);
      } else {
        timeLeft -= 5;
        playBuzzer(400,300);
      }
    }

    if(millis()-start >= 1000){
      timeLeft--;
    }
  }

  if(currentQuestion >= 5){
    gameWin();
  } else {
    gameOver();
  }

  delay(2000);
}
