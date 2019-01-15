// -*- mode: c; -*-

// Gradually changes brightness of LEDs (fades and brighter) connected
// to analog out pins

// number of LEDs
const int GROUPS_COUNT = 3;
// pins that these LEDs are connected to
const int groups[GROUPS_COUNT][2] =
  {{3, 5},
   {6, 9},
   {10, 11}};

// groups by color
const int RED_G = 0;
const int GREEN_G = 1;
const int BLUE_G = 2;

// where the additional red led is connected
const int RED_PIN = 2;

// button for toggling modes
const int BTN_PIN = 7;

int bright_group = RED_G;
int dimmin_group = BLUE_G;

enum modes { SEQ, ALL };

modes mode = SEQ;

void setGroup(const int group, const int value)
{
    analogWrite(groups[group][0], value);
    analogWrite(groups[group][1], value);
    if (group == RED_G && value > 0)
    {
        digitalWrite(RED_PIN, HIGH);
    }
    else
    {
        digitalWrite(RED_PIN, LOW);
    }
}


void checkButton()
{
    int buttonState = digitalRead(BTN_PIN);
    if (buttonState == HIGH)
    {
        mode = (mode == SEQ) ? ALL : SEQ ;
        Serial.println("button HIGH, mode: " + (mode == ALL) ? "ALL" : "SEQ");
        delay(1000);
    }
}

void setup()
{
    Serial.begin(9600);

    pinMode(BTN_PIN, INPUT);

    pinMode(RED_PIN, OUTPUT);
    digitalWrite(RED_PIN, HIGH);

    // put your setup code here, to run once:
    for (int i = 0; i < GROUPS_COUNT; ++i)
    {
        pinMode(groups[i][0], OUTPUT);
        pinMode(groups[i][1], OUTPUT);
        setGroup(i, 205);
        delay(500);
        setGroup(i, 0);
    }

    // first group is made to shine
    int val = 0;
    while (val < 255)
    {
        setGroup(dimmin_group, val);
        val += 5;
        // wait for N milliseconds to see the dimming effect
        delay(100);
    }
    val = 255;
    setGroup(dimmin_group, val);
    delay(100);
} // end setup


void loop()
{
    switch (mode)
    {
    case SEQ:
        // put your main code here, to run repeatedly:
        for (int bright_group = 0; bright_group < GROUPS_COUNT; ++bright_group)
        {

            int val = 0;
            while (val < 255)
            {
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
        }
        break;
    case ALL:
        for (int group = 0; group < GROUPS_COUNT; ++group)
        {
            setGroup(group, 255);
        }
        delay(100);
        checkButton();
        break;
    }
}
// eof
