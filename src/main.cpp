#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

const uint8_t irRecvPin = 15;
int32_t lastTimeRecv = 0;
IRrecv irRecv(irRecvPin);

bool isLostReported = true;
decode_results results;

const uint8_t irSendPin = 4;
IRsend irSend(irSendPin);

void setup(){
    Serial.begin(115200);
    irSend.begin();
    irRecv.enableIRIn();
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Pronto para receber sinais");
}

void loop(){
    irSend.sendNEC(0x0, 32); 

    if (irRecv.decode(&results)){
    irRecv.resume();

    if(results.value == 0){
      serialPrintUint64(results.value, HEX);
      Serial.println("");

      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);

      lastTimeRecv = millis();
      isLostReported = false;
    }
  }

  if((millis() - lastTimeRecv > 200) && !isLostReported){
    Serial.println("Sinal perdido");
    isLostReported = true;
  }
}