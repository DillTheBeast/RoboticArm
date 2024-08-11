#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Set the I2C address to 0x40

#define SERVOMIN  150  // Minimum pulse length count (for 0 degrees)
#define SERVOMAX  600  // Maximum pulse length count (for 180 degrees)

void setup() {
  Serial.begin(9600);  // Start serial communication
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz
}

void loop() {
  if (Serial.available()) {
    int channel = Serial.parseInt();  // Read the servo channel (0-15)
    int angle = Serial.parseInt();    // Read the servo angle (0-180)
    if (channel >= 0 && channel <= 15 && angle >= 0 && angle <= 180) {
      int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(channel, 0, pulse);  // Set the PWM signal for the servo
    }
  }
}
