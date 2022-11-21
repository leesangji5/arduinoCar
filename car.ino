#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3);

int frontLeft = 7;
int frontRight = 6;

int trig = 8;
int echo = 9;

int pare = 10;

int dir;

Servo servofl;
Servo servofr;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pare, INPUT_PULLUP);
  
  servofl.attach(frontLeft);
  servofr.attach(frontRight);
  bluetooth.write(1);
}

void loop() {
  if (bluetooth.available()) {
    dir = bluetooth.read();
    Serial.println(dir);
    bluetooth.write(1);
    direct(dir);
    delay(10);
  }
  if (Serial.available()){
    if (Serial.read() == '1'){
      bluetooth.write(1);
    }
  }
//  if (digitalRead(pare) == LOW){
//    bluetooth.write(1);
//  }
}

/////////////////////////////////
bool collision(){
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
 
  unsigned long duration = pulseIn(echo, HIGH);
  float distance = duration / 29.0 / 2.0;

  if (distance < 10){
    return true;
  }
  else {
    return false;
  }
}

////////////////////////////////////////////
void direct(int dir){
  bool rect = collision();
  if (dir == 1 and not rect){
    right();
  }
  else if (dir == 2 and not rect){
    left();
  }
  else if (dir == 3 and not rect){
    go();
  }
  else if (dir == 4){
    back();
  }
  else {
    breacking();
  }
}

/////////////////////////////////////////
void breacking(){
  servofl.write(90);
  servofr.write(90);
}

void go(){
  servofl.write(180);
  servofr.write(0);
}

void back(){
  servofl.write(0);
  servofr.write(180);
}

void right(){
  servofl.write(180);
  servofr.write(180);
}

void left(){
  servofl.write(0);
  servofr.write(0);
}
