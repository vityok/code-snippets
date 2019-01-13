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

// groups by color
const int RED_G = 0;
const int GREEN_G = 1;
const int BLUE_G = 2;

const int RED_PIN = 2;

const int BTN_PIN = 7;

int bright_group = RED_G;
int dimmin_group = BLUE_G;

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

  pinMode(BTN_PIN, INPUT);

  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, HIGH);
  // first group is made to shine
  int val = 0;
  while (val < 255) {
    setGroup(bright_group, val);
    val += 5;
    // wait for N milliseconds to see the dimming effect
    delay(100);
  }
  val = 255;
  setGroup(bright_group, val);
  delay(100);
}

enum modes { SEQ, ALL };

modes mode = ALL;

void checkButton()
{
  int buttonState = digitalRead(BTN_PIN);
  if (buttonState == HIGH) {
    mode = (mode == SEQ) ? ALL : SEQ ;
  }
}

void loop() {
  switch (mode) {
  case SEQ:
    // put your main code here, to run repeatedly:
    for (int group = 0; group < GROUPS_COUNT; ++group) {
      int val = 0;
      while (val < 255) {
	setGroup(bright_group, val);
	setGroup(dimmin_group, 255-val);
	val += 5;
	// wait for N milliseconds to see the dimming effect
	delay(100);
	checkButton();
      }
      val = 255;
      setGroup(bright_group, val);
      setGroup(dimmin_group, 0);
      delay(100);
      dimmin_group = bright_group;
      bright_group = group;
    }
    break;
  case ALL:
      for (int group = 0; group < GROUPS_COUNT; ++group) {
	setGroup(group, 255);
      }
      checkButton();
    break;
  }
}
