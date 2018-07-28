#include <temp.pb.h>

#include <pb_common.h>
#include <pb.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include <DHT.h>
#include <DHT_U.h>

#include <ESP8266WiFi.h>

#define DHTPIN 5     
#define DHTTYPE DHT11

#define DEVICEID 100

DHT dht(DHTPIN, DHTTYPE);


const char* ssid     = "vivien-lab";
const char* password = "vivien-lab";
const char* addr     = "192.168.43.217";
const uint16_t port  = 10101;

WiFiClient client;

// setup WIFI and sensor
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Setting up WIFI for SSID ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI connection failed, reconnecting...");
    delay(500);
  }

  Serial.println("");
  Serial.print("WiFi connected, ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting DHT11 sensor...");
  dht.begin();
}


void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("connecting to ");
  Serial.println(addr);

  if (!client.connect(addr, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec to reconnect...");
    delay(5000);
    return;
  }

  Serial.println("reading humidity/temp...");
  
  float hum = dht.readHumidity();
  float tmp = dht.readTemperature();
  
  if (isnan(hum) || isnan(tmp)) {
    Serial.println("failed to read sensor data");
    return;
  }

  float hiCel = dht.computeHeatIndex(tmp, hum, false);
    
  pb_TempEvent temp = pb_TempEvent_init_zero;
  temp.deviceId = 12;
  temp.eventId = 100;
  temp.humidity = hum;
  temp.tempCel = tmp;
  temp.heatIdxCel = hiCel;
  
  sendTemp(temp);
  digitalWrite(LED_BUILTIN, HIGH);
  
  delay(5000);
}

void sendTemp(pb_TempEvent e) {
  uint8_t buffer[128];
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  
  if (!pb_encode(&stream, pb_TempEvent_fields, &e)){
    Serial.println("failed to encode temp proto");
    Serial.println(PB_GET_ERROR(&stream));
    return;
  }
  
  Serial.print("sending temp...");
  Serial.println(e.tempCel);
  client.write(buffer, stream.bytes_written);
}

