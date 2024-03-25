//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 3             Date: 2023-00-00  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |  This program will allow for an arduino to use 2 buttons to change the |
//  |   position of an arm on the servo motor. For each position the servo   |
//  |   motor is in it'll have a diffrent color repersentation with a RGB    |
//  |                                  LED.                                  |
//  \________________________________________________________________________/

#include <Servo.h>


// -----------------------------------------
//               Description
//           Initalize vairables
// -----------------------------------------
#define BUTTON1 2
#define BUTTON2 3

#define RGB_RED 9
#define RGB_GREEN 11
#define RGB_BLUE 10

Servo myservo;

const int MAX = 4;
const int MIN = 0;

int currentPos = 0;
int increment = 1;
int position = 0;

int colors[5][3] = {
    {255, 255, 255},    // 0
    {0, 255, 0},        // 25
    {127, 127, 0},      // 50
    {255, 255, 0},      // 75
    {255, 0, 0}         // 100
};

// -----------------------------------------
//               Description
//     Setup pins and attach interrupts
// -----------------------------------------
void setup() {
    myservo.attach(4);
    myservo.write(0);
    Serial.begin(9600);

    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);

    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);

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
        analogWrite(RGB_RED, colors[position][0]);
        analogWrite(RGB_GREEN, colors[position][1]);
        analogWrite(RGB_BLUE, colors[position][2]);

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
            analogWrite(RGB_RED, colors[i][0]);
            analogWrite(RGB_GREEN, colors[i][1]);
            analogWrite(RGB_BLUE, colors[i][2]);
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

