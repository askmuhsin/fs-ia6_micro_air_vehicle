#include <Servo.h>

Servo left_servo;
int pos = 0;

int delay_read;

double channel_3; //throttle channel -- connect to reciever channel 4
int throttle_level;

void setup() {
  pinMode(3, INPUT);  //throttle logic, channel_3 >> pin_3
  left_servo.attach(9);  //servo signal line >> pin_9
  left_servo.write(60);
  Serial.begin(9600);
}

void loop() {
  channel_3 = pulseIn(3, HIGH);
  delay_read = throttleLevel(channel_3);

  if(channel_3<1100)
  {
    ;
  } else {
    flap(delay_read);
  }
}

void flap(int delay_) {
  for(pos=0; pos<=60; pos+=1)
  {
    left_servo.write(pos);
    delay(delay_);
  }
  for(pos=60; pos>=0; pos-=1)
  {
    left_servo.write(pos);
    delay(delay_);
  }
}

int throttleLevel(double channel) {
  int throttle_l = 0;
  throttle_l = map(channel, 1100, 2000, -5, -1); //change map out from -5 to 0
  return abs(throttle_l);
}
