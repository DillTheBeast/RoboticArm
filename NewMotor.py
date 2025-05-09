import can
import struct
import time

# === USER SETTINGS ===
CAN_PORT = 'COM3'       # Change this to your actual COM port
MOTOR_ID = 0x01          # Default motor ID
ARBITRATION_ID = 0x140 + MOTOR_ID
BAUDRATE = 1000000       # RH-25 uses 1 Mbps
DEGREES = 90             # Rotate to 90°

# === CONVERSION ===
# 360° = 65535 (0xFFFF), so 90° = 16384
position_units = int((DEGREES / 360.0) * 65535)
position_bytes = list(struct.pack('<I', position_units))  # 4 bytes, little-endian

# === SETUP CAN BUS ===
bus = can.interface.Bus(bustype='serial', channel=CAN_PORT, bitrate=BAUDRATE)

def send_msg(data):
    msg = can.Message(arbitration_id=ARBITRATION_ID, data=data, is_extended_id=False)
    try:
        bus.send(msg)
        print(f"Sent: {data}")
    except can.CanError as e:
        print("CAN send failed:", e)

# === STEP 1: ENABLE MOTOR ===
send_msg([0x88, 0, 0, 0, 0, 0, 0, 0])
time.sleep(0.1)

# === STEP 2: SEND POSITION CONTROL COMMAND ===
# Command: 0xA4, next 4 bytes = position, last 3 = unused
send_msg([0xA4] + position_bytes + [0, 0, 0])
print(f"Rotating to {DEGREES} degrees...")
time.sleep(2)  # Wait for motion to complete

# === STEP 3: OPTIONAL - STOP MOTOR ===
send_msg([0x81, 0, 0, 0, 0, 0, 0, 0])
print("Motion complete. Motor stopped.")