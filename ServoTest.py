import serial
import time

# Replace with your Arduino's serial port
ser = serial.Serial('/dev/tty.usbmodem101', 9600)

def move_servo(channel, angle):
    if 0 <= channel <= 15 and 0 <= angle <= 360:
        command = f"{channel} {angle}\n"
        ser.write(command.encode('utf-8'))
        time.sleep(0.1)  # Allow some time for the Arduino to process the command

# Example: Move servo on channel 0 to 0 degrees
move_servo(0, 0)
time.sleep(2)

# Example: Move servo on channel 0 to 45 degrees
move_servo(0, 45)
time.sleep(2)

# Example: Move servo on channel 0 to 180 degrees
move_servo(0, 180)
time.sleep(2)

# Example: Move servo on channel 0 to 360 degrees
move_servo(0, 360)
time.sleep(2)

# Close the serial connection
ser.close()