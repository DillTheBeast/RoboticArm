#define dirPin 2       // DIR+ connected to pin 2
#define stepPin 3      // PUL+ connected to pin 3
#define rightButtonPin 7 // Right button connected to pin 7
#define leftButtonPin 8  // Left button connected to pin 8

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(rightButtonPin, INPUT_PULLUP); // Use internal pull-up resistors
  pinMode(leftButtonPin, INPUT_PULLUP);  // Use internal pull-up resistors
}

void loop() {
  // If the right button is held, rotate clockwise
  if (digitalRead(rightButtonPin) == LOW) {
    digitalWrite(dirPin, HIGH); // Set direction to clockwise
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100); // Adjust speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100);
  }
  // If the left button is held, rotate counterclockwise
  else if (digitalRead(leftButtonPin) == LOW) {
    digitalWrite(dirPin, LOW); // Set direction to counterclockwise
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100); // Adjust speed
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100);
  }
  // If no button is pressed, do nothing (motor stays idle)
}