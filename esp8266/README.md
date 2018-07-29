# The ESP8266 projects

The [ESP8266](https://www.espressif.com/en/products/hardware/esp8266ex/overview) is a small, but capable, microcontroller from Espressif.  It can be programmed with Arduino C and many other languages that can interoperate with C.  The examples in this section uses the ESP8266 for diverse IoT usage.

## Setup  

The following is a list of setup instructions to get you started:

* Setup the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [The ESP8266](https://en.wikipedia.org/wiki/ESP8266) microcontroller
* [Configure the ESP8266](./esp8266-setup.md) board for local development
* Setup the [ESP8266 with Arduino](https://github.com/esp8266/Arduino)


## ESP8266 examples

* [Testing the ESP8266 WIFI](./simple-tcp) - this example lets you get started with WIFI connectivity with the ESP8266
* [Getting started with protobuf](./simple-proto) - this is a simple project that lets you test your ESP8266 with sending protocol buffer encoded data to a backend.
* [ESP8266-DHT11 Temperature logger](./esp8266-dht11-temp) - This projects uses the ESP8266 and DHT11 temperature, plus several technologies, including Protocol Buffers, Go, InfluxDB, and Grafana, to collect temperature and provide a visualization dashboard.