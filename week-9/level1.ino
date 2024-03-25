#include <IRremote.h>

#define IR_RECEIVE_PIN 11
int value;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.resume();
        value = IrReceiver.decodedIRData.command;
        Serial.println(value);
    }
}