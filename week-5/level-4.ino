/*
 _______________________________________________________________
/  Name: Kyler. V            Level 4          Date: 2023-10-06  \
|                                                               |
|                          Description                          |
|                                                               |
|  This program will start with the lockout enabled and RGB LED |
|  off. When the toggle button is pushed the lockout var will   |
|   toggle. When the lockout is disabled, the RGB LED will be   |
|  able to cycle through colors when the cycle is set. When the |
|   cycle button is pressed the cycle var will toggle. If the   |
|  lockout is enabled, the cycle var will not toggle be able to |
|                          be toggled.                          | 
\_______________________________________________________________/
*/

/*
-----------------------------------------
|          Initialize variables         |
-----------------------------------------
*/
// Setup button pins
int toggleButtonPin = 2;
int rgbButtonPin = 3;

// Setup RGB pins
int rgbRed = 13;
int rgbGreen = 11;
int rgbBlue = 12;

// Setup LED pins
int redLed = 10;
int greenLed = 9;
bool displayedLed = false;

// Setup state variables
bool cycle = false;
bool display = false;
int colorIndex = 0;

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
    // Setup pins
    pinMode(toggleButtonPin, INPUT);
    pinMode(rgbButtonPin, INPUT);

    pinMode(rgbRed, OUTPUT);
    pinMode(rgbGreen, OUTPUT);
    pinMode(rgbBlue, OUTPUT);

    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);

    // Set inital state of LEDs
    digitalWrite(redLed, HIGH);

    // Setup interrupts
    attachInterrupt(digitalPinToInterrupt(toggleButtonPin), changeLed, RISING);
    attachInterrupt(digitalPinToInterrupt(rgbButtonPin), attemptCycleToggle, RISING);
}

/*
-----------------------------------------
|               Main loop               |
-----------------------------------------
*/
void loop() {
    // If we are cycling colors, display the next color
    if (cycle) {
        rgbDisplay(colors[colorIndex]);
        colorIndex = (colorIndex < 2) ? (colorIndex + 1) : 0;
        delay(500);

    // Otherwise turn off the display
    } else {
        rgbDisplay(RGB{false, false, false});
        colorIndex = 0;
    }
}

// Change the lockout LED to the opposite state
void changeLed() {
    displayedLed = !displayedLed;
    if (displayedLed) {
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, LOW);
    } else {
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
    }
}

// Attempt to toggle the cycle state
void attemptCycleToggle() {
    if (displayedLed) {
        cycle = !cycle;
    }
}

// Display an RGB color
void rgbDisplay(RGB rgb) {
    digitalWrite(rgbRed, rgb.r);
    digitalWrite(rgbGreen, rgb.g);
    digitalWrite(rgbBlue, rgb.b);
}
