/*
 _______________________________________________________________
/  Name: Kyler. V             Extra           Date: 2023-10-06  \
|                                                               |
|                          Description                          |
|                                                               |
|   This program will start with the lockout enabled and the    |
|  cycle disabled. It will then ask the user for a color combo  | 
|  to cycle through. Once the user enters a valid color combo   |
|  the color combo will be put into the cycle. Once the cycle   |
|  button is pushed the cycle will start. When the cycle button |
|  is then again toggled and the lockout is disabled, and the   |
|  cycle will stop. When the lockout becomes enabled the cycle  |
|  will stop and the RGB light turn off, then once again the it |
|             will ask the user for a color combo.              |
\_______________________________________________________________/
*/

/*
-----------------------------------------
|          Initialize variables         |
-----------------------------------------
*/
// Set button pins
int toggleButtonPin = 2;
int rgbButtonPin = 3;

// Set the RGB pins
int rgbRed = 13;
int rgbGreen = 11;
int rgbBlue = 12;

// Set the LED pins
int redLed = 10;
int greenLed = 9;

// Set state variables
bool displayedLed = false;
bool cycle = false;
bool display = false;
int colorIndex = 0;

// User input variables
int lengthOfDisplay = 0;
bool ask = true;
bool asked = false;
bool valid = false;
char validCommands[] = {
    'R',
    'G',
    'B',
    'C',
    'M',
    'Y',
    'W'
};

// RGB structure
struct RGB {
    bool r;
    bool g;
    bool b;

    bool operator!=(const RGB& other) const {
        return (r != other.r) || (g != other.g) || (b != other.b);
    }
};

// Colors available for use
RGB colors[] = {
    {true, false, false},
    {false, true, false},
    {false, false, true},
    {false, true, true},
    {true, false, true},
    {true, true, false},
    {true, true, true}
};

// Set the colors to cycle through
RGB cycleColors[50];

// Initialize function
void rgbDisplay(RGB rgb);

/*
-----------------------------------------
|    Setup pins, LEDs, and interrupts   |
-----------------------------------------
*/
void setup() {
    // Start serial monitor
    Serial.begin(9600);

    // Initialize all pins
    pinMode(toggleButtonPin, INPUT);
    pinMode(rgbButtonPin, INPUT);

    pinMode(rgbRed, OUTPUT);
    pinMode(rgbGreen, OUTPUT);
    pinMode(rgbBlue, OUTPUT);

    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);

    // Initialize basic state
    digitalWrite(redLed, HIGH);
    attachInterrupt(digitalPinToInterrupt(toggleButtonPin), changeLed, RISING);
    attachInterrupt(digitalPinToInterrupt(rgbButtonPin), attemptCycleToggle, RISING);
}

/*
-----------------------------------------
|               Main loop               |
-----------------------------------------
*/
void loop() {
    // Ask the user for input
    if (!displayedLed && ask) {
        // If we have already displayed a message to 
        // the user then dont redisplay that message
        if (!asked) {
            Serial.println("Enter a command using the following (RGBCMYW)");
            Serial.print("Command: ");
            asked = true;
        }

      // Get the input from the user
      getInput();
    }

    attemptCycle();
}


// Get the input from the user
void getInput() {
    if (Serial.available() == 0) {
        // Get our input from the serial monitor
        String myInput = Serial.readString();
        myInput.trim();
        myInput.toUpperCase();

        // Save previous values
        int prevLength = lengthOfDisplay;
        RGB previousColors[50];
        memcpy(previousColors, cycleColors, sizeof(cycleColors));

        
        bool valid = false;

        // Check if the input is there
        if (myInput.length() > 0) {
            // Set default variables
            lengthOfDisplay = 0;
            Serial.println(myInput);
            valid = false;
            
            // Go through each character in the input
            for (int i=0; i<myInput.length(); i++) {
                // Go through each valid command and check 
                // to see if we have a valid color command
                for (int j=0; j<sizeof(validCommands); j++) {
                    if (myInput.charAt(i) == validCommands[j]) {
                        valid = true;
                        cycleColors[i] = colors[j];
                        lengthOfDisplay++;
                    }
                }

                // If we dont have a valid color then break
                // and reset changed values. in addition,
                // display an error message and re-ask for
                // the color combo they want.
                if (!valid) {
                    Serial.println("[Value not accepted] Invalid color character");
                    Serial.print("Command: ");
                    lengthOfDisplay = prevLength;
                    memcpy(cycleColors, previousColors, sizeof(previousColors));
                    break;
                }
            }
        }
        
        // If we dont have a valid string then reset the 
        // length of the color to the previous length
        if (valid) {
            Serial.println(myInput);
            Serial.println("[Value accepted] Color set");
        }
    }
}

// Attempt to cycle through the colors
void attemptCycle() {
    // If we are supposed to cycle then 
    // cycle the selected colors
    if (cycle) {
        rgbDisplay(cycleColors[colorIndex]);
        colorIndex = (colorIndex < lengthOfDisplay-1) ? (colorIndex + 1) : 0;
        delay(500);
        
    // Otherwise turn off the RGB led
    } else {
        rgbDisplay(RGB{false, false, false});
        colorIndex = 0;
    }
}

// Change the lockout LED to the opposite
// state and turn on the appropriate LED
void changeLed() {
    // change the lockout LED
    displayedLed = !displayedLed;
    if (displayedLed) {
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, LOW);
    } else {
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, LOW);
    }

    // Reset variables
    if (!displayedLed) {
        cycle = false;
        ask = true;
        asked = false;
    } else {
        cycle = true;
    }
}


// Attempt to toggle the cycle state
void attemptCycleToggle() {
    // If lockout is disengaged start cycling colors
    if (displayedLed) {
        cycle = !cycle;
    }
}

// Display a selected RGB value
void rgbDisplay(RGB rgb) {
    digitalWrite(rgbRed, rgb.r);
    digitalWrite(rgbGreen, rgb.g);
    digitalWrite(rgbBlue, rgb.b);
}






