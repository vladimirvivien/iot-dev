import pyaudio
import wave
import signal
import sys

CHUNK = 1024 *  8
FORMAT = pyaudio.paInt16
CHANNELS = 1
RECORD_SECONDS = 5
WAVE_OUTPUT_FILENAME = "output.wav"

frames = []

p = pyaudio.PyAudio()

RATE = p.get_device_info_by_index(0)['defaultSampleRate']

stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=(int)(RATE),
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
    sys.exit(0)

def main():
    signal.signal(signal.SIGINT, signal_handler)
    print "* recording " 
    print p.get_device_info_by_index(0)['defaultSampleRate']

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data)

    print("* done recording")

    close_stream(p, stream)
    close_file(frames)

if __name__== "__main__":
  main()

