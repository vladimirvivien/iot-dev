#include <pb_common.h>
#include <dice_roll.pb.h>
#include <pb.h>
#include <pb_encode.h>
#include <pb_decode.h>

#include <ESP8266WiFi.h>

const char* ssid     = "<SSID-Name>";
const char* password = "<SSID-Password>";
const char* addr     = "192.168.1.136";
const uint16_t port  = 10101;
WiFiClient client;
  
const char* messages[] = {
  "the path to happiness is toward the bathroom",
  "may you become carbon neutral someday",
  "you are not illeterate",
  "be kind to pigeons, a status will be made of you someday",
  "your head is the wrong size for your body",
  "every exist is a new entrance",
  "you will be hungry again in one hour exactly",
  "they already know your secrets",
  "Hard work pays off in the future, laziness now",
  "a cynic is a frustrated optimist",
  "aliens will come to you after you read this",
  "the road to riches is paved with homework"
};

int randNum;

void setup() {
  Serial.begin(115200);
  delay(10);  
  
  Serial.println();
  Serial.print("Setting up WIFI for SSID ");
  Serial.println(ssid);

  // setup WIFI as client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI connection failed, reconnecting");
    delay(500);
    Serial.print("...");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
  
  randomSeed(analogRead(0));
  
}

void loop() {
  Serial.print("connecting to ");
  Serial.println(addr);

  if (!client.connect(addr, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec to reconnect...");
    delay(5000);
    return;
  }

  
  randNum = random(0,12);
  sendMsg(randNum, messages[randNum]);
  
  delay(5000);
}

// encode message as protobuf and send via serial
void sendMsg(int idx, const char* msg) {

  pb_DiceRoll roll = pb_DiceRoll_init_zero;
  uint8_t buffer[128];
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  
  roll.roll = idx;
 
  if (!pb_encode(&stream, pb_DiceRoll_fields, &roll)){
    Serial.println("failed to encode proto");
    Serial.println(PB_GET_ERROR(&stream));
    return;
  }
  
  Serial.print("sending dice roll of ");
  Serial.println(roll.roll);
  client.write(buffer, stream.bytes_written);
}

