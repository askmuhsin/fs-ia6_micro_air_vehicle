#include <Servo.h>

Servo myservo;
int pos = 0;
int posRead = 0;

void setup() {
  myservo.attach(9);
  myservo.write(60);   

}

void loop() {
  for(pos=0; pos<=60; pos+=1)
  {
    myservo.write(pos);
    delay(2);
  }
  for(pos=60; pos>=0; pos-=1)
  {
    myservo.write(pos);
    delay(2);
  }
}
