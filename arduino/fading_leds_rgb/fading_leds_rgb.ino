// -*- mode: c; -*-

// Gradually changes brightness of LEDs (fades and brighter) connected
// to analog out pins

// number of LEDs
const int GROUPS_COUNT = 3;
// pins that these LEDs are connected to
const int groups[3][2] = 
  {{3, 5},
   {6, 9},
   {10, 11}};

// value output to the pin
int values[GROUPS_COUNT];
// change between cycles
int deltas[GROUPS_COUNT];

void setGroup(int group, int value) {
  values[group] = value;
  analogWrite(groups[group][0], value);
  analogWrite(groups[group][1], value);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < GROUPS_COUNT; ++i) {
    pinMode(groups[i][0], OUTPUT);
    pinMode(groups[i][1], OUTPUT);
    setGroup(i, 205);
    deltas[i] = 5 + random(5);
    delay(500);
    setGroup(i, 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int group = 0; group < GROUPS_COUNT; ++group) {
    int val = 0;
    while (val < 255) {
      setGroup(group, val);
      val += 5;
      // wait for N milliseconds to see the dimming effect
      delay(100);
    }
    val = 255;
    setGroup(group, val);
    delay(100);

    while (val > 0) {
      setGroup(group, val);
      val -= 5;
      // wait for N milliseconds to see the dimming effect
      delay(100);
    }
    setGroup(group, 0);
    // wait for N milliseconds to see the dimming effect
    delay(100);
  }
}
