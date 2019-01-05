// Gradually changes brightness of LEDs (fades and brighter) connected
// to analog out pins

// number of LEDs
const int PINS_COUNT = 6;
// pins that these LEDs are connected to
const int pins[] = {3, 5, 6, 9, 10, 11};
// value output to the pin
int values[PINS_COUNT];
// change between cycles
int deltas[PINS_COUNT];

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < PINS_COUNT; ++i) {
    pinMode(pins[i], OUTPUT);
    values[i] = random(5);
    deltas[i] = 5 + random(5);
    analogWrite(pins[i], 200);
    delay(500);
    analogWrite(pins[i], 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < PINS_COUNT; ++i) {
    // set the brightness of pin i:
    analogWrite(pins[i], values[i]);

    // change the brightness for next time through the loop:
    values[i] = values[i] + deltas[i];

    // reset fading for the pin with value going outside the range:
    if (values[i] <= 0 || values[i] >= 255) {
      int delta = 2 + random(5);
      if (values[i] < 0) {
	values[i] = 0;
	deltas[i] = delta;
      }
      if (values[i] > 255) {
	values[i] = 255;
	deltas[i] = -delta;
      }
    }
  }
  // wait for N milliseconds to see the dimming effect
  delay(100);
}
