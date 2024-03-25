//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 2             Date: 2023-00-00  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |    This program will allow the user to control the two LEDS using a    |
//  |   IR reciver and a remote control. The user will be able to turn the   |
//  |                 LEDS on and off, and also blink them.                  |
//  \________________________________________________________________________/
#include <IRremote.h>

// -----------------------------------------
//               Description
//          Intialize vairables.
// -----------------------------------------
#define IR_RECEIVE_PIN 11
#define BLUE_LED 12
#define RED_LED 13
int value;


// -----------------------------------------
//               Description
//     Setup pins, IR reciver and setup
//           serial communication.
// -----------------------------------------
void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
}

// -----------------------------------------
//               Description
//             Main code loop
// -----------------------------------------
void loop() {
    if (IrReceiver.decode()) {
        IrReceiver.resume();
        value = IrReceiver.decodedIRData.command;
        Serial.println(value);
        switch (value) {
            case 16:
                button1();
                break;

            case 17:
                button2();
                break;
            
            case 18:
                button3();
                break;
            
            case 20:
                button4();
                break;
            
            case 21:
                button5();
                break;
        }
    }
}

// -----------------------------------------
//               Description
//            Button functions
// -----------------------------------------

void button1() {
    digitalWrite(BLUE_LED, HIGH);
}

void button2() {
    digitalWrite(RED_LED, HIGH);
}

void button3() {
    digitalWrite(BLUE_LED, LOW);
}

void button4() {
    digitalWrite(RED_LED, LOW);
}

void button5() {
    for (int i=0; i < 3; i++) {
        digitalWrite(BLUE_LED, HIGH);
        digitalWrite(RED_LED, HIGH);
        delay(500);
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(RED_LED, LOW);
        delay(500);
    }
}