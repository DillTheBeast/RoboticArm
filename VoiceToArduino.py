import speech_recognition as sr
from gtts import gTTS
import os
import serial
import time
from pydub import AudioSegment
from pydub.playback import play

# Adjust this to your Arduino's serial port
ARDUINO_PORT = "/dev/tty.usbmodem1101"  
BAUD_RATE = 9600  

# Connect to Arduino
try:
    arduino = serial.Serial(ARDUINO_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Allow Arduino to initialize
    print("Connected to Arduino on", ARDUINO_PORT)
except Exception as e:
    print("Error connecting to Arduino:", e)
    exit()

# Text-to-speech function
def speak(text):
    tts = gTTS(text=text, lang='en')
    filename = "/tmp/temp_audio.mp3"
    tts.save(filename)
    sound = AudioSegment.from_mp3(filename)
    play(sound)
    os.remove(filename)

# Speech recognition function
def listen():
    recognizer = sr.Recognizer()
    microphone = sr.Microphone()

    with microphone as source:
        recognizer.adjust_for_ambient_noise(source)
        print("Listening...")
        audio = recognizer.listen(source, timeout=5)
        try:
            transcription = recognizer.recognize_google(audio).lower()
            print(f"You said: {transcription}")
            return transcription
        except sr.UnknownValueError:
            print("Could not understand the audio")
        except sr.RequestError as e:
            print(f"Could not request results; {e}")
    return None

# Main function for listening and controlling the robotic arm
def main():
    while True:
        command = listen()
        if command:
            if "br" in command:
                speak("Moving base right")
                arduino.write(b'B_R')
            elif "bl" in command:
                speak("Moving base left")
                arduino.write(b'B_L')
            elif "sr" in command:
                speak("Moving shoulder right")
                arduino.write(b'S_R')
            elif "xl" in command:
                speak("Moving shoulder left")
                arduino.write(b'S_L')
            elif "er" in command:
                speak("Moving elbow right")
                arduino.write(b'E_R')
            elif "el" in command:
                speak("Moving elbow left")
                arduino.write(b'E_L')
            else:
                speak("Command not recognized")

# Start voice assistant
speak("Hello, I am your robot assistant. How can I help you?")
main()