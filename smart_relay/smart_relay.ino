#define DEBUG

#define SWITCH_DISTANCE 50
#define REPEAT_COUNT 10

#define TRIG_PIN 3
#define ECHO_PIN 2
#define RELAY_PIN 4

bool on = false;
int cnt = 0;

int distanceFromObject() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  int duration = pulseIn(2, HIGH);

  return duration * 0.034 / 2;
}

void setup() {
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void dump(int distance) {
#ifdef DEBUG
  Serial.print("> ON: ");
  Serial.print(on);
  Serial.print(" CNT: ");
  Serial.print(cnt);
  Serial.print(" DISTANCE: ");
  Serial.println(distance);
#endif
}

void loop() {
  int distance = distanceFromObject();

  if (distance <= SWITCH_DISTANCE) {
    if (on) {
      cnt = 0;
    } else {
      cnt++;
    }
  } else {
    if (!on) {
      cnt = 0;
    } else {
      cnt++;
    }
  }

  if (cnt >= REPEAT_COUNT) {
    if (on) {
      on = false;
      cnt = 0;
    } else {
      on = true;
      cnt = 0;
    }
  }
  if (on) {
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
  }

  dump(distance);

  delay(250);
}
