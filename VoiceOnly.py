import speech_recognition as sr
from gtts import gTTS
import os
from playsound import playsound

def speak(text):
    tts = gTTS(text=text, lang='en')
    filename = "/tmp/temp_audio.mp3"
    tts.save(filename)
    playsound(filename)
    os.remove(filename)

def listen():
    recognizer = sr.Recognizer()
    microphone = sr.Microphone()

    print("Start speaking...")
    with microphone as source:
        recognizer.adjust_for_ambient_noise(source)
        while True:
            print("Listening...")
            audio = recognizer.listen(source)
            try:
                transcription = recognizer.recognize_google(audio)
                print(f"You said: {transcription}")
                return transcription
            except sr.UnknownValueError:
                print("Could not understand the audio")
            except sr.RequestError as e:
                print(f"Could not request results; {e}")

def main():
    while True:
        identify = listen()
        if 'robot' in identify:
            if "move right" in identify:
                speak("moving right")
            elif "move left" in identify:
                speak("moving left")
            elif "move forward" in identify:
                speak("moving forward")
            elif "move backward" in identify:
                speak("moving backwards")
            else:
                speak("unidentified")
        else:
            speak("unidentified")

# Test continuous recognition
speak("Hello, I am your robot assistant. How can I help you?")
main()