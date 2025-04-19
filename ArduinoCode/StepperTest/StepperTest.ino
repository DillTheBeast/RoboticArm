#define DIR 2
#define PUL 3
#define DIR1 7
#define PUL1 6
#define DIR2 11
#define PUL2 10

int count = 0;         // To count elapsed seconds
bool clockwise = true; // Track the direction of movement
bool completedCycle = false; // Track if both directions have been completed

void setup() {
  // Set the control pins as outputs
  pinMode(DIR, OUTPUT);
  pinMode(PUL, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PUL1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PUL2, OUTPUT);
}

void loop() {
  if (!completedCycle) {
    // Set motor direction
    digitalWrite(DIR, clockwise ? LOW : HIGH); // Change direction based on `clockwise`
    digitalWrite(DIR1, clockwise ? LOW : HIGH);
    digitalWrite(DIR2, clockwise ? HIGH : LOW);

    // Move motor for 3 seconds
    unsigned long startTime = millis();
    while (millis() - startTime < 3000) {
      digitalWrite(PUL, HIGH);
      digitalWrite(PUL1, HIGH);
      digitalWrite(PUL2, HIGH);
      delayMicroseconds(50); // Adjust speed
      digitalWrite(PUL, LOW);
      digitalWrite(PUL1, LOW);
      digitalWrite(PUL2, LOW);
      delayMicroseconds(50);

      digitalWrite(PUL2, HIGH);
      delayMicroseconds(50);
      digitalWrite(PUL2, LOW);
      delayMicroseconds(50);
    }

    // Switch direction after 3 seconds
    clockwise = !clockwise;
    count++;

    // Check if each direction has been executed once
    if (count == 2) {
      completedCycle = true; // Mark cycle as complete
      count = 0;             // Reset count for next loop
    }

    delay(1000); // Add a small pause between direction changes
  } else {
    // Delay 5 seconds before restarting the loop
    delay(5000);
    completedCycle = false; // Reset the cycle status
  }
}

// #define DIR 2
// #define PUL 3
// #define DIR1 4
// #define PUL1 5


// void setup() {
//   // Set the control pins as outputs
//   pinMode(DIR, OUTPUT);
//   pinMode(PUL, OUTPUT);
//   pinMode(DIR1, OUTPUT);
//   pinMode(PUL1, OUTPUT);
// }

// void loop() {
//   // Set motor direction
//   digitalWrite(DIR, HIGH);
//   digitalWrite(DIR1, HIGH);

//   digitalWrite(PUL, HIGH);
//   digitalWrite(PUL1, HIGH);
//   delayMicroseconds(30);
//   digitalWrite(PUL, LOW);
//   digitalWrite(PUL1, LOW);
//   delayMicroseconds(30);

//   delayMicroseconds(3000);

//   digitalWrite(DIR, LOW);
//   digitalWrite(DIR1, LOW);

//   digitalWrite(PUL, HIGH);
//   digitalWrite(PUL1, HIGH);
//   delayMicroseconds(30);
//   digitalWrite(PUL, LOW);
//   digitalWrite(PUL1, LOW);
//   delayMicroseconds(30);
// }


// #define DIR 2
// #define PUL 3

// void setup() {
//   pinMode(DIR, OUTPUT);
//   pinMode(PUL, OUTPUT);
//   Serial.begin(9600); // Start serial communication
// }

// void loop() {
//   if (Serial.available() > 0) {
//     char command = Serial.read();
//     if (command == 'R') {
//       digitalWrite(DIR, HIGH); // Move right
//       moveStepper();
//     } else if (command == 'L') {
//       digitalWrite(DIR, LOW); // Move left
//       moveStepper();
//     }
//   }
// }

// void moveStepper() {
//   for (int i = 0; i < 200; i++) { // Adjust 200 for step size
//     digitalWrite(PUL, HIGH);
//     delayMicroseconds(30);
//     digitalWrite(PUL, LOW);
//     delayMicroseconds(30);
//   }
// }