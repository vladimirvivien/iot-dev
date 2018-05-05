import pyaudio
import wave
import signal
import sys
import io
import os

# Imports the Google Cloud client library
from google.cloud import speech
from google.cloud.speech import enums
from google.cloud.speech import types


CHUNK = 1024 *  8
FORMAT = pyaudio.paInt16
CHANNELS = 1
RECORD_SECONDS = 5
WAVE_OUTPUT_FILENAME = "output.wav"

frames = []

p = pyaudio.PyAudio()

RATE = (int)(p.get_device_info_by_index(0)['defaultSampleRate'])

stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)


def close_stream(pa, pa_stream):
    print("closing..")
    pa_stream.stop_stream()
    pa_stream.close()
    pa.terminate()

def close_file(data):
    print "saving file " + WAVE_OUTPUT_FILENAME 
    wf = wave.open(WAVE_OUTPUT_FILENAME, 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(p.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(data))
    wf.close()

def signal_handler(signal, frame):
    print('Stopping...')
    close_stream(p, stream)
    close_file(frames)
    transcribe()
    sys.exit(0)

def transcribe():
    client = speech.SpeechClient()
    
    file_name = os.path.join(
    os.path.dirname(__file__),
    './',
    WAVE_OUTPUT_FILENAME)

    with io.open(file_name, 'rb') as audio_file:
        content = audio_file.read()
        audio = types.RecognitionAudio(content=content)

    config = types.RecognitionConfig(
        encoding=enums.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=RATE,
        language_code='en-US')

    response = client.recognize(config, audio)

    print ("transcribe...")
    for result in response.results:
        print('{}'.format(result.alternatives[0].transcript))


def main():
    signal.signal(signal.SIGINT, signal_handler)
    print "* recording " 
    print RATE

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)

    print("* done recording")

    close_stream(p, stream)
    close_file(frames)
    transcribe()

if __name__== "__main__":
  main()

