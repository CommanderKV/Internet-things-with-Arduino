//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 2             Date: 2023-00-00  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program will allow for an arduino to use 2 buttons to change    |
//  |     the position of a servo by 25% each time in either direction.      |
//  \________________________________________________________________________/

#include <Servo.h>

// -----------------------------------------
//               Description
//           Initalize vairables
// -----------------------------------------
#define BUTTON1 2
#define BUTTON2 3

Servo myservo;

const int MAX = 4;
const int MIN = 0;

int currentPos = 0;
int increment = 1;
int position = 0;


// -----------------------------------------
//               Description
//    Setup pins and attach interrupts
// -----------------------------------------
void setup() {
    myservo.attach(4);
    myservo.write(0);
    Serial.begin(9600);

    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);

    attachInterrupt(digitalPinToInterrupt(BUTTON1), button1, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON2), button2, RISING);
}


// -----------------------------------------
//               Description
//             Main code loop
// -----------------------------------------
void loop() {
   if ((currentPos - position) == 1 || (currentPos - position) == -1){
        myservo.write(position * (180/4));
        currentPos = position;

    } else if ((currentPos - position) > 1 || (currentPos - position) < -1) {
        int change = 0;
        if (currentPos < position) {
            change = 1;
        } else {
            change = -1;
        }

        for (int i=currentPos; i!=position; i+=change) {
            myservo.write(i * (180/4));
            delay(500);
            currentPos = i;
        }
    }
}

// -----------------------------------------
//               Description
//           Button 1 interrupt
// -----------------------------------------
void button1() {
    if (currentPos + increment <= MAX) {
        position = currentPos + increment;
    } else {
        position = MIN;
    }
}

// -----------------------------------------
//               Description
//           Button 2 interrupt
// -----------------------------------------
void button2() {
    if (currentPos - increment >= MIN) {
        position = currentPos - increment;
    } else {
        position = MAX;
    }
}

