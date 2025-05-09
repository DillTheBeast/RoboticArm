#define DIR 2
#define PUL 3
#define DIR1 4
#define PUL1 5
#define DIR2 6
#define PUL2 7

int directionState = 0; // 0 = LOW, 1 = HIGH, 2 = HIGH, 3 = LOW, then repeat
unsigned long stepDuration = 3000; // 5 seconds

void setup() {
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PUL1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PUL2, OUTPUT);
}

void loop() {
  // Determine direction based on the state
  bool dirValue = (directionState == 0 || directionState == 3) ? LOW : HIGH;

  digitalWrite(DIR, dirValue);
  digitalWrite(DIR1, dirValue);
  digitalWrite(DIR2, !dirValue); // Inverted if needed for DIR2

  // Run motors for 5 seconds
  unsigned long startTime = millis();
  while (millis() - startTime < stepDuration) {
    // Pulse PUL and PUL1 once
    digitalWrite(PUL, HIGH);
    digitalWrite(PUL1, HIGH);
    digitalWrite(PUL2, HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL, LOW);
    digitalWrite(PUL1, LOW);
    digitalWrite(PUL2, LOW);
    delayMicroseconds(100);
  }

  // Cycle to next direction state
  directionState = (directionState + 1) % 4;

  delay(1000); // Optional pause between changes
}