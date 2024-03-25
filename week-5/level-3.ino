/*
 _______________________________________________________________
/  Name: Kyler. V            level 3          Date: 2023-10-06  \
|                                                               |
|                          Description                          |
|                                                               |
|   This program will display a color on an RGB LED when the    |
|  start button is pressed. The color will change every 500ms.  | 
|    When the stop button is pressed, the LED will turn off.    |
\_______________________________________________________________/
*/

/*
-----------------------------------------
|         Initialize variables          |
-----------------------------------------
*/
// Initialize button and LED pins 
int startButtonPin = 2;
int stopButtonPin = 3;

int redLedPin = 13;
int greenLedPin = 11;
int blueLedPin = 12;

// Initialize state variables
bool display = false;
int colorIndex = 0;
long int colorSwap = 0;

// Create a struct to represent an RGB color
struct RGB {
    bool r;
    bool g;
    bool b;
};

// Create an array of RGB colors
RGB colors[] = {
    {true, false, false}, // Red
    {false, true, false}, // Green
    {false, false, true}  // Blue
};

// Initialize rgb display function
void rgbDisplay(RGB rgb);

/*
-----------------------------------------
|       Setup pins and interrupts       |
-----------------------------------------
*/
void setup() {
    pinMode(startButtonPin, INPUT);
    pinMode(stopButtonPin, INPUT);

    pinMode(redLedPin, OUTPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(blueLedPin, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(startButtonPin), changeStateON, RISING);
    attachInterrupt(digitalPinToInterrupt(stopButtonPin), changeStateOFF, RISING);
}

/*
-----------------------------------------
|               Main loop               |
-----------------------------------------
*/
void loop() {
    // If we are displaying, display the next color
    if (display) {
        rgbDisplay(colors[colorIndex]);
        delay(500);
        colorIndex = (colorIndex < 2) ? (colorIndex + 1) : 0;

    // Otherwise turn off the display
    } else {
        rgbDisplay(RGB{false, false, false});
        colorIndex = 0;
    }
}

// Change the state of the display to ON
void changeStateON() {
    display = true;
}

// Change the state of the display to OFF
void changeStateOFF() {
    display = false;
}

// Display an RGB color
void rgbDisplay(RGB rgb) {
    digitalWrite(redLedPin, rgb.r);
    digitalWrite(greenLedPin, rgb.g);
    digitalWrite(blueLedPin, rgb.b);
}
