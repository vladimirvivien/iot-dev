# IoT Speech to Text on Raspberry Pi

IoT Speech to Text on Raspberry Pi using Google Clound Speech

The following instructions use Python to create a simple
program that interacts with Google's Speech APIs for
speech-to-text.

## Pre-requisites

* Python (2.7 or 3.x)
* Python-Pip
* PortAudio
* PyAudio
* Source code in Python
* Access to Google Cloud services

## Setup PortAudio

[PortAudio](http://portaudio.com/docs/v19-doxydocs/tutorial_start.html) will be built/setup when PyAudio is installed.

## Setup PyAudio

For latest instructions (and other platforms) see [here] (https://people.csail.mit.edu/hubert/pyaudio/) to setup PyAudio:

```shell
$> sudo apt-get install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev python-all-dev
$> sudo apt-get install python-pyaudio python3-pyaudio
$> pip install pyaudio #for latest
```

If PyAudio not building PortAudio, uninstall and install in order above.

## Setup Google Cloud Speech (for Python)

Follow steps on [Google Cloud](https://cloud.google.com/speech-to-text/docs/quickstart-client-libraries#client-libraries-install-python) for complete instructions.  Here is a summary:

* Setup Google Cloud Platform project (via GCP console)
* Enable Speech-to-Text API
* Download private key JSON file containing credentials for service account.

Next on the machine that will run the Python code, install the Google Speech Python libraries and other dependencies:

```shell
$> pip install --upgrade google-cloud-speech
```

## Examples

Example directory `hello`

* recorder.py - records voice and creates sound file.
* recognizer.py - submits sound file to Google Speech service for transcription and prints result.

Example director `transcribe`

* File transcribe.py combines the recording and tanscribing funtions into one program.

## Running Python code

When running Python scripts, ensure to setup environment variable GOOGLE_APPLICATION_CREDENTIALS to specify the location of the JSON service account credential files (see earlier step).