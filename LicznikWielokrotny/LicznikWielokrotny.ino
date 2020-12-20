#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int l[3] = {0, 0, 0};         // zadekladowanie liczników 
int poz = 0;                        // zadeklarowanie pozycji 
const int p1 = 0, p2 = 6, p3 = 12;   // zadeklarowanie pozycji liczników
int x[3] = {1, 1, 0};
bool wait = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Licznik 3-krotny");
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  
  Wcisk();
  PuscDelay();
  SetLCD();
  
  if(wait)
  {
    delay(100);
    wait = false;
  }
  Serial.println(analogRead(A0));
  delay(100);
}

void SetLCD(){
  lcd.setCursor(p1, 1);
  lcd.print(l[0]);

  lcd.setCursor(p2, 1);
  lcd.print(l[1]);

  lcd.setCursor(p3, 1);
  lcd.print(l[2]);
}

void PuscDelay(){
  for(int i = 2; i < 5; i++)
  {
    if(x[i-2] != digitalRead(i) && digitalRead(i) == 1)    // odciśnięcie przycisku
    {
      wait = true;
    }
    x[i-2] = digitalRead(i);
  }
}

void Wcisk(){
  for(int i = 2; i <= 5; i++)
  {
    if(x[i-2] != digitalRead(i) && digitalRead(i) == 0)    // odciśnięcie przycisku
    {
      l[i-2]++;
    }
  }
}
