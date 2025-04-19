#include <Arduino.h>

#define DIR1 2
#define DIR2 8
#define DIRB 12

#define PUL1 3
#define PUL2 9
#define PULB 11

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(DIRB, OUTPUT);
  pinMode(PULB, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PUL1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PUL2, OUTPUT);
  
  Serial.println("Stepper motor ready!");
}

void moveStepper(int dirPin, int pulPin, int direction, int steps, int delayTime) {
  digitalWrite(dirPin, direction);  // Set motor direction
  for (int i = 0; i < steps; i++) {
    digitalWrite(pulPin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(pulPin, LOW);
    delayMicroseconds(delayTime);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any trailing whitespace or newlines

    Serial.print("Received command: ");
    Serial.println(command);

    if (command == "B_R") { 
      moveStepper(DIRB, PULB, HIGH, 16000, 100); 
    } 
    else if (command == "B_L") { 
      moveStepper(DIRB, PULB, LOW, 16000, 100); 
    } 
    else if (command == "S_R") { 
      moveStepper(DIR1, PUL1, HIGH, 16000, 100); 
    } 
    else if (command == "S_L") { 
      moveStepper(DIR1, PUL1, LOW, 16000, 100); 
    } 
    else if (command == "E_R") { 
      moveStepper(DIR2, PUL2, HIGH, 16000, 100); 
    } 
    else if (command == "E_L") { 
      moveStepper(DIR2, PUL2, LOW, 16000, 100); 
    } 
    else {
      Serial.println("Unknown command received");
    }
  }
}