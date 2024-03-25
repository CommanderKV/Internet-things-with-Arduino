//   ___________________________________________________________________
//  /  Name: Kyler Visser             Level 3               2023-09-07  \
//  |                                                                   |                           
//  |                              Description                          |
//  |                                                                   |
//  |      This program will utilize the digital pins 13 and 12 on      |
//  |     an arduino uno. The program will be utalizing these pins      |
//  |    connecting to LED's. Pin 13 should be connected to the blue    |
//  |        LED and pin 12 should be connected to the red LED.         |
//  |                                                                   |
//  |    The program will then flash the blue LED then the red LED      |
//  |    for 5 seconds then it will switch to flashing the red and      |
//  |    blue LED's at the same time for 4 seconds then repeating       |
//  |            this process untill power is disconected.              |
//  \___________________________________________________________________/

//  --------------------------------------
//    Initalize vairables for later use.
//  --------------------------------------
const int blueLED = 13;
const int redLED = 12;
int cycleLength = 1000;

//  --------------------
//    Setup pin modes.
//  --------------------
void setup()
{
	pinMode(blueLED, OUTPUT);
    pinMode(redLED, OUTPUT);
}

//  ----------------------
//    Main program loop.
//  ----------------------
void loop()
{
    cycle1();
    cycle2();
}

//  --------------------------------
//               Cycle 1
//
//    This function will allow for 
//    the red LED and blue LED to
//     blink one after the other
//          for 5 cycles.
//  --------------------------------
void cycle1() {
    for (int i=0; i<5; i++) {
        digitalWrite(blueLED, HIGH);
        delay(cycleLength/4);
        digitalWrite(blueLED, LOW);
        delay(cycleLength/4);
        digitalWrite(redLED, HIGH);
        delay(cycleLength/4);
        digitalWrite(redLED, LOW);
        delay(cycleLength/4);
    }
}

//  --------------------------------
//               Cycle 2
//
//    This function will allow for 
//    the red LED and blue LED to
//      blink simutaniously for
//              4 cycles.
//  --------------------------------
void cycle2() {
    for (int i=0; i<4; i++) {
        digitalWrite(blueLED, HIGH);
        digitalWrite(redLED, HIGH);
        delay(cycleLength/2);
        digitalWrite(blueLED, LOW);
        digitalWrite(redLED, LOW);
        delay(cycleLength/2);
    }
}