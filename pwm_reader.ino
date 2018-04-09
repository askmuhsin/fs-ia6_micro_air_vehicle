double channel_4; //throttle channel -- connect to reciever channel 4
double channel_2; //rudder channel -- connect to reciever channel 2

char* throttle_states[] = {"high", "mid-hi", "mid-lo", "low"};
char* throttle_state;
int rudder_state;
int throttle_level;

void setup() {
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {
  channel_4 = pulseIn(4, HIGH);
  channel_2 = pulseIn(2, HIGH);

  throttle_state = throttleScan(channel_4);
  throttle_level = throttleLevel(channel_4);
  rudder_state = rudderScan(channel_2);

  Serial.print("Throttle level --\t");
  Serial.print(throttle_state);
  Serial.print("\t,\t");
  Serial.print(throttle_level);
  Serial.print("\t||\tRudder level -- \t");
  Serial.println(rudder_state);
//  Serial.println(channel_1);
}

char* throttleScan(double channel) {
  if (channel>=1750 && channel<2000)
    return throttle_states[0];
  else if (channel>=1500 && channel<1750)
    return throttle_states[1];
  else if (channel>=1250 && channel<1500)
    return throttle_states[2];
  else if (channel<1250)
    return throttle_states[3];
}

int rudderScan(double channel) {
  return map(channel, 975, 1965, -2, 2);
}

int throttleLevel(double channel) {
  int level;
  level = map(channel, 990, 1987, -3, 0);
  level+=3;
  return level;
}
