#include <pb_common.h>
#include <dice_roll.pb.h>
#include <pb.h>
#include <pb_encode.h>
#include <pb_decode.h>


const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  16;      // the number of the LED pin

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

int buttonState = 0;  
bool msgSent = false;
int randNum;

uint8_t buffer[128];
size_t message_length;
bool status;
pb_ostream_t stream;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); 
  randomSeed(analogRead(0));
  stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
}

void loop() {
  buttonState = digitalRead(buttonPin);
  randNum = random(0,12);
    
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    if (!msgSent){
        sendMsg(randNum, messages[randNum]);
        msgSent = true;
    }
  } else {
    digitalWrite(ledPin, LOW);
    msgSent = false;
  }
}

// encode message as protobuf and send via serial
void sendMsg(int idx, const char* msg) {
  DiceRoll roll = DiceRoll_init_zero;
  roll.number = idx;
  status = pb_encode(&stream, DiceRoll_fields, &roll);
  if (!status){
    return;
  }
  //Serial.write(buffer, stream.bytes_written);
  Serial.print(msg);
}

