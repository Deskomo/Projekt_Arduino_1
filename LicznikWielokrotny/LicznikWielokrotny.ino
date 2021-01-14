#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int p1 = 0, p2 = 6, p3 = 12;   // zadeklarowanie pozycji liczników

int l[2] = {0, 0};         // zadekladowanie liczników 
int l2 = 0;
int x[2] = {1, 1};         // zapamiętuje poprzednią pozycję portu, żeby porównać czy się zmienił
bool wait[2] = {false, false};
bool wait2[2] = {false, false};

int n = 0; 
int m[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   // zadeklarowanie zmiennych do uśredniania
float micro = 0;
bool m1 = false, m2 = false;

long d[2] = {0, 0};        // czas od puszczenia
long d3 = 0;

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Licznik 3-krotny");
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() 
{
  NieCzekaj();
  Wcisk();
  Pusc();
  micro = mean();
  Mikrofon();
  SetLCD();
}

void SetLCD()
{
  lcd.setCursor(p1, 1);
  lcd.print(l[0]);

  lcd.setCursor(p2, 1);
  lcd.print(l[1]);

  lcd.setCursor(p3, 1);
  lcd.print(l2);
}

void Pusc()
{
  for(int i = 0; i < 2; i++)
  {
    if(x[i] != digitalRead(i+2) && digitalRead(i+2) == 1 && !wait[i] && !wait2[i])    // odciśnięcie przycisku
    {
      wait[i] = true;
      wait2[i] = true;
      d[i] = millis();
    }
    x[i] = digitalRead(i+2);
  }
}

void Wcisk()
{
  for(int i = 0; i <= 2; i++)
  {
    if(x[i] != digitalRead(i+2) && digitalRead(i+2) == 0 && !wait[i])    // wciśnięcie przycisku
    {
      l[i]++;
      wait2[i] = false;
    }
  }
}

void NieCzekaj()
{
  for (int i = 0; i <= 1; i++)
  {
    if(wait[i] && millis() - d[i] > 50)      //ZMIEŃ WARTOŚĆ ŻEBY ZMIENIĆ DELAY
    {
      wait[i] = false;
    }
  }
}

float mean()
{
  float sum = 0;
  m[n] = digitalRead(4);
  n++;
  if(n >=16)
    n = 0;
  for(int i = 0; i < 16; i++)
  {
    sum += m[i];
  }
  return sum / 16.0f;
  
}

void Mikrofon()
{
  if(m2 && millis() - d3 > 500)         // MAKSYMALNY ODSTĘP MIĘDZY KLAŚNIĘCIAMI
  {
    m2 = false;
  }
  if(micro >= 0.15 && !m1 && !m2)       // ZMIEŃ WARTOŚĆ ŻEBY ZMIENIĆ CZUŁOŚĆ MIKROFONU
  {
    m1 = true;
    d3 = millis();
    Serial.println(l2);
    return;
  }
  if(micro == 0.0f && m1)
  {
    if(millis() - d3 < 100)   // ZMIEŃ CZAS KLAŚNIĘCIA
    {
  Serial.print(millis() - d3);
  Serial.print(" Zaliczyło  ");
  Serial.println(micro);
      m1 = false;
      Serial.println("coś");
      l2++;
      m2 = true;
      d3 = millis();
    }
    else
    {
      m1 = false;
    }
  }
}
