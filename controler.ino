#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2, 3);

void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop(){
  if (bluetooth.available()) {
    if (bluetooth.read() == 1){
      int x = analogRead(A1);
      int y = analogRead(A0);
      bluetooth.write(direct(x, y));
      delay(100);
    }
  }
}

int direct(int x, int y){
  int dir;
  if (y<400){
    dir = 1;
  }
  else if (y>600){
    dir = 2;
  }
  else if (x<400){
    dir = 3;
  }
  else if (x>600){
    dir = 4;
  }
  else{
    dir = 5;
  }
  return dir;
}
