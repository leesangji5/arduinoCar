#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int trig = 8;
int echo = 9;

float check_length = 10.0;
bool check = false;
int count = 0;
float m = 99999.9;
float p = 5.0;
float accuracy = 0.0;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}
 
void loop() {
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  unsigned long duration = pulseIn(echo, HIGH);
  float distance = duration / 29.0 / 2.0;

  check_all(distance);
  
  lcd.clear();
  lcd.print("count: ");
  lcd.setCursor(6, 0);
  lcd.print(count);
  lcd.setCursor(0, 1);
  lcd.print("accuracy: ");
  lcd.setCursor(9, 1);
  int a = accuracy*100;
  lcd.print(a);
  delay(200);
}

void check_all(float distance){
  if (not check and distance <= check_length){
    count += 1;
    check = true;
  } else if (distance > check_length){
    check = false;
    m = 99999.9;
    accuracy = 0;
  }
  if (distance < m){
    m = distance;
    accuracy = p/m;
    if (accuracy > 1){
      accuracy = 1;
    }
  }
}
