#include <Servo.h>

Servo left_servo;
Servo right_servo;
int flap_angle = 80;
int pos = 0;
int delay_read;
double channel_3; //throttle channel -- connect to reciever channel 4
int throttle_level;

void setup() {
  pinMode(3, INPUT);  //throttle logic, channel_3 >> pin_3
  left_servo.attach(9);  //servo signal line >> pin_9
  left_servo.write(0);
  right_servo.attach(10);  //servo signal line >> pin_9
  right_servo.write(180);
  Serial.begin(9600);
}

void loop() {
  channel_3 = pulseIn(3, HIGH);
  delay_read = throttleLevel(channel_3);
  if(channel_3<1100)
  {
    left_servo.write(0);
    right_servo.write(180);
  } else {
    flap(delay_read);
  }
}

void flap(int delay_) {
  //left wing
  int it_1, it_2;
  it_1 = 0;
  it_2 = 180;
  for(pos=0; pos<=flap_angle; pos++)
  {
    left_servo.write(it_1);
    right_servo.write(it_2);
    delay(delay_);
    it_1++;
    it_2--;
  }
  it_1 = 60;
  it_2 = 120;
  for(pos=0; pos<=flap_angle; pos++)
  {
    left_servo.write(it_1);
    right_servo.write(it_2);
    delay(delay_);
    it_1--;
    it_2++;
  }
}

int throttleLevel(double channel) {
  int throttle_l = 0;
  throttle_l = map(channel, 1100, 2000, -5, -1);
  return abs(throttle_l);
}
