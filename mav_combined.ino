#include <Servo.h>

Servo left_servo;
int pos = 0;

int delay_val;
const int max_angle=60;  //throttle flap max angle, default 60

double channel_3; //throttle channel -- connect to reciever channel 4

void setup() {
  pinMode(3, INPUT);  //throttle logic, channel_3 >> pin_3
  left_servo.attach(9);  //servo signal line >> pin_9
  left_servo.write(60);
  Serial.begin(9600);
}

void loop() {
  channel_3 = pulseIn(3, HIGH);
  delay_val = throttleLevel(channel_3);
  if (delay_val>1250)
    flap(delay_val);
  else
    ;
}

void flap(int delay_) {
  for(pos=0; pos<=max_angle; pos+=1)
  {
    left_servo.write(pos);
    delay(delay_);
  }
  for(pos=max_angle; pos>=0; pos-=1)
  {
    left_servo.write(pos);
    delay(delay_);
  }
}

int throttleLevel(double channel) {
  int throttle_l = 0;
  throttle_l = map(channel, 1000, 2000, -5, -2);
  throttle_l*=-1;
  return throttle_l;
}
