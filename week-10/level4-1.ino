//   ________________________________________________________________________  
//  /  Name: Kyler Visser           Level4-Sender          Date: 2023-00-00  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program allows for the arduino to send an integer to another    |
//  |  arduino. This number is then used to change the position of a servo   |
//  |  and the color of a RGB LED. What number to be sent is determined by   |
//  |                        which button is pressed.                        |
//  \________________________________________________________________________/

#include <Wire.h>

// -----------------------------------------
//               Description
//           Initalize vairables
// -----------------------------------------
#define BUTTON1 2
#define BUTTON2 3

byte move = 0;
bool buttonHit = false;

// -----------------------------------------
//               Description
//     Setup pins and wire communication
// -----------------------------------------
void setup() {
    Wire.begin();
    Serial.begin(9600);

    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
}

// -----------------------------------------
//               Description
//             Main code loop
// -----------------------------------------
void loop() {
    // Move left
    if (!buttonHit) {
        if (digitalRead(BUTTON1) == HIGH) {
            Wire.beginTransmission(8);
            Wire.write(1);
            Wire.endTransmission();
            buttonHit = true;
            
        // Move right
        } else if (digitalRead(BUTTON2) == HIGH) {
            Wire.beginTransmission(8);
            Wire.write(2);
            Wire.endTransmission();
            buttonHit = true;
        }
    } else {
        if (digitalRead(BUTTON1) == LOW && digitalRead(BUTTON2) == LOW) {
            buttonHit = false;
        }
    }
}

