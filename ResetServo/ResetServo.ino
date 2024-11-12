#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create an instance of the PCA9685 driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Set the I2C address to 0x40

// Define the minimum and maximum pulse lengths for the servo
#define SERVOMIN  120  // Minimum pulse length count (for 0 degrees)
#define SERVOMAX  650  // Maximum pulse length count (for 180 degrees)

// Function prototype for moveServo
void moveServo(uint8_t channel, int angle);

void setup() {
  // Initialize the PCA9685 driver
  pwm.begin();
  pwm.setPWMFreq(60);  // Set frequency to 60 Hz
  delay(10);  // Short delay for the servo driver to stabilize
  moveServo(0, 90);
  delay(1000);
  moveServo(0, 180);
  delay(3000);
  moveServo(0, 0);
  delay(3000);
  moveServo(0, 90);
  moveServo(1, 90);
  moveServo(2, 90);
  moveServo(3, 90);
  delay(1000);
  moveServo(1, 180);
  moveServo(2, 180);
  delay(1000);
  moveServo(1, 0);
  moveServo(2, 0);
  delay(1000);
  moveServo(1, 90);
  moveServo(2, 90);
  // moveServo(2, 90);
  // delay(1000);
  // moveServo(3, 180);
  // delay(1000);
  // moveServo(3, 0);
  // delay(1000);
  // moveServo(3, 90);
  // delay(1000);
  // moveServo(0,0);
  // moveServo(1,180);
  // delay(1000);
  // moveServo(0, 180);
  // moveServo(1,0);
  // delay(1000);
  // moveServo(0, 90);
  // moveServo(1,90);

  // for(int i = 90; i < 180; i+=5) {
  //   moveServo(0, i);
  //   moveServo(1, 180-i);
  //   delay(1);
  // }
  // delay(1000);
  // for(int i = 0; i < 90; i+= 5) {
  //   moveServo(0, 180-i);
  //   moveServo(1, i);
  //   delay(1);
  // }
  // delay(1000);
  //moveServo(2, 90);
  // delay(1000);
  // moveServo(2, 0);
  // delay(1000);

  // moveServo(0, 90);
  // delay(1000);
  // moveServo(1, 90);
  // delay(1000);
  // moveServo(2, 90);
  // delay(1000);

  // moveServo(0, 0);
  // delay(1000);
  // moveServo(1, 0);
  // delay(1000);
  // moveServo(2, 180);
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
