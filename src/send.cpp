#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>

const uint8_t irSendPin = 4;
IRsend irsend(irSendPin);

void setup() {
  irsend.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.println("Enviando sinal: ");
  serialPrintUint64(0x0, HEX);
  irsend.sendNEC(0x0, 32); 
  //delay(4800);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}
