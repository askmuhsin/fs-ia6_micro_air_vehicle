#include <Servo.h>

Servo left_servo;
Servo right_servo;
Servo rudder_servo;
// params
int flap_angle = 80;
// vars
int pos = 0;
int delay_read;
int rudder_angle;
double channel_3; //  channel 3 of rx maps to throttle logic
double channel_1; //  channel 1 of rx maps to rudder logic
int throttle_level;

void setup() {
  pinMode(3, INPUT);  //  throttle logic, channel_3 >> pin_3 uc
  pinMode(4, INPUT);  //  rudder logic, channel_1 >> pin_4 uc
  left_servo.attach(9);  //servo signal line >> pin_9 
  right_servo.attach(10);  //servo signal line >> pin_10
  rudder_servo.attach(11);  //sevo signal line >> pin_11
  left_servo.write(0);  
  right_servo.write(180);   
  rudder_servo.write(15);
  Serial.begin(9600);
}

void loop() {
  // Throttle logic
  channel_3 = pulseIn(3, HIGH);
  delay_read = throttleLevel(channel_3);
  if(channel_3<1100)
  {
    left_servo.write(0);
    right_servo.write(180);
  } else {
    flap(delay_read);
  }

  // Rudder logic
  channel_1 = pulseIn(4, HIGH);
  if(channel_1>1450 && channel_1<1540)
  {
    rudder_servo.write(15);
  } else {
    rudder_angle = rudderMove(channel_1);
    rudder_servo.write(rudder_angle);
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

int rudderMove(double channel) {
  int r_angle;
  r_angle = map(channel_1, 990, 1990, 0, 30);
  return r_angle;
}

