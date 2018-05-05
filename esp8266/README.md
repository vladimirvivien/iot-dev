# The ESP8266 microcontroller projects

The [ESP8266](https://www.espressif.com/en/products/hardware/esp8266ex/overview) is a small, but capable, microcontroller from Espressif.  It can be programmed with Arduino C and many other languages that can interoperate with C.  The examples in this section uses the ESP8266 for diverse IoT usage.

## Setup

The following setup links are for creating IoT applications with protocol buffers and microcontrollers dev boards such as the ESP8266.  

The following is a list of setup instructions to get you started:

* Setup the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [The ESP8266](https://en.wikipedia.org/wiki/ESP8266) microcontroller
* [Configure the ESP8266](./esp8266-setup.md) board for local development
* Setup the [ESP8266 with Arduino](https://github.com/esp8266/Arduino)
* Learn about [protocol buffers](https://developers.google.com/protocol-buffers/docs/tutorials), local setup, etc
* [Set up the nanopb](./nanopb.md) protoc plugin to generate C code for your device


## ESP8266 examples

* [Testing the ESP8266 WIFI](./simple-tcp) - this example lets you get started with WIFI connectivity with the ESP8266
* [Getting started with protobuf](./simple-proto) - this is a simple project that lets you test your ESP8266 with sending protocol buffer encoded data to a backend.
* [A temperature logger](./dht11-temp) - Use Arduino C, the ESP8266 board, and the DHT11 temp/humidity sensor to collect temperature data sent to a Go backend server for visualization using Grafana.