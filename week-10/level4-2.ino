//   ________________________________________________________________________  
//  /  Name: Kyler Visser          Level4-Reciver          Date: 2023-00-00  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |    This program allows the arduino to recive an integer from another   |
//  |  arduino. This number determines if we move the servo left or right.   |
//  |     The color of the RGB LED is also determined by what number is      |
//  |                               recieved.                                |
//  \________________________________________________________________________/
#include <Servo.h>
#include <Wire.h>

// -----------------------------------------
//               Description
//           Initalize vairables
// -----------------------------------------
#define RGB_RED 9
#define RGB_GREEN 11
#define RGB_BLUE 10

Servo myservo;

const int MAX = 4;
const int MIN = 0;

int currentPos = 1;
int increment = 1;
int position = 0;

int colors[5][3] = {
    {255, 255, 255}, // 0
    {0, 255, 0},     // 25
    {0, 0, 255},   // 50
    {255, 255, 0},   // 75
    {255, 0, 0}      // 100
};

// -----------------------------------------
//               Description
//     Setup pins and wire communication
// -----------------------------------------
void setup()
{
    Wire.begin(8);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event

    myservo.attach(4);
    myservo.write(0);

    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);
}

// -----------------------------------------
//               Description
//             Main code loop
// -----------------------------------------
void loop()
{
    // If we are one position away from the desired position
    if ((currentPos - position) == 1 || (currentPos - position) == -1) {
        myservo.write(position * (180/4));
        analogWrite(RGB_RED, colors[position][0]);
        analogWrite(RGB_GREEN, colors[position][1]);
        analogWrite(RGB_BLUE, colors[position][2]);

        currentPos = position;

    // If we are more than one position away from the desired position
    } else if ((currentPos - position) > 1 || (currentPos - position) < -1) {
        int change = 0;
        if (currentPos < position) {
            change = 1;
        } else {
            change = -1;
        }

        for (int i = currentPos; i != position; i += change) {
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
//           Recieve event handler
// -----------------------------------------
void receiveEvent(int howMany)
{
    while(1 < Wire.available()) {}
    int newPosition = Wire.read();    // receive byte as an integer
    if (newPosition != 0) {
        // Move left
        if (newPosition == 1) {
            if ((currentPos + 1) <= MAX) {
                position = currentPos + 1;
            } else {
                position = MIN;
            }

        // Move right
        } else {
            if ((currentPos - 1) >= MIN) {
                position = currentPos - 1;
            } else {
                position = MAX;
            }
        }
    }
}