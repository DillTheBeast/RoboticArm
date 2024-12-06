#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create an instance of the PCA9685 driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Set the I2C address to 0x40

// Define the minimum and maximum pulse lengths for the servo
#define SERVOMIN  120  // Minimum pulse length count (for 0 degrees)
#define SERVOMAX  650  // Maximum pulse length count (for 180 degrees)
#define STOP  380      // Neutral pulse to stop the servo (adjust if needed)
#define RIGHT 650      // Pulse length for rotation in one direction
#define LEFT  120      // Pulse length for rotation in the opposite direction

// Function prototype for moveServo
void moveServo(uint8_t channel, int angle);

void setup() {
  // Initialize the PCA9685 driver
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz
  delay(10);  // Short delay for the servo driver to stabilize
  // pwm.setPWM(0, 0, RIGHT);  // Rotate servo in the right direction
  // delay(2000);

  // // Stop the servo briefly between directions
  // pwm.setPWM(0, 0, STOP);
  // delay(100);

  // // Rotate left for 1 second
  // pwm.setPWM(0, 0, LEFT);  // Rotate servo in the left direction
  // delay(2000);

  // // Stop the servo briefly between cycles
  // pwm.setPWM(0, 0, STOP);
  // delay(1000);

  // moveServo(1, 90);
  // moveServo(2, 90);
  // delay(1000);
  // moveServo(1, 0);
  // moveServo(2, 0);
  // delay(1000);
  // moveServo(1, 90);
  // moveServo(2, 90);
  // delay(1000);
  // moveServo(1, 180);
  // moveServo(2, 180);
  // delay(1000);
  // moveServo(1, 90);
  // moveServo(2, 90);
  moveServo(0, 90);
  moveServo(1, 90);
  // delay(1000);
  // moveServo(0, 150);
  // moveServo(1, 150);
  // delay(1000);
  // moveServo(0, 90);
  // moveServo(1, 90);
}

void loop() {

  // Loop continues indefinitely
}

// Function to move a servo to a specific angle on a specific channel
void moveServo(uint8_t channel, int angle) {
  if (angle >= 0 && angle <= 180) {  // Ensure angle is within 0-180 degrees
    int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);  // Convert angle to pulse width
    pwm.setPWM(channel, 0, pulse);  // Set the PWM signal for the servo
  }
}
