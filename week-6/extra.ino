//   ________________________________________________________________________  
//  /  Name: Kyler Visser               Extra              Date: 2023-10-15  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program will take in an input from the user and then display    |
//  |    the sequence that the user has inputted. If the user clicks the     |
//  |  button again then the program will ask for input again. If the user   |
//  |   inputs a non exsitant color then the program will skip that color.   |
//  |    if they input a color that is already in the sequence then the      |
//  |                 program will still display that color.                 |
//  \________________________________________________________________________/

//  --------------------------------------
//    Initalize variables and structors.
//  --------------------------------------
const int RGBRedPin = 9;    
const int RGBGreenPin = 10; 
const int RGBBluePin = 11;  

int potentiometer = A0;
int lockoutButton = 2;

int currentColor = 0;

bool asked = false;

int colorChangeDelay = 1000;
struct color {
    int pins[3] = {-1, -1, -1};
    int values[3] = {0, 0, 0};
    int brightness;
    String name;

    bool operator!=(const color& other) {
        for (int i=0; i<sizeof(pins); i++) {
            if (pins[i] != other.pins[i]) {
                return true;
            }
        }
        return false;
    }
};
color colors[7] = {};
color emptyColor = color {
    {-1, -1, -1},
    {0, 0, 0},
    0,
    ""
};

int colorPins[3] = {RGBRedPin, RGBGreenPin, RGBBluePin};

bool lightShow = false;


//  ------------------------------
//    Setup pins, inturupts, and 
//        the serial output.
//  ------------------------------
void setup() {
    pinMode(RGBRedPin, OUTPUT);
    pinMode(RGBGreenPin, OUTPUT);
    pinMode(RGBBluePin, OUTPUT);

    pinMode(potentiometer, INPUT);
    pinMode(lockoutButton, INPUT);

    attachInterrupt(digitalPinToInterrupt(lockoutButton), setValue, RISING);

    Serial.begin(9600);
}


//  -----------------------------
//    Main loop of the program.
//  -----------------------------
void loop() {
    // If we are in need of asking
    // the user what the sequence is
    // is or if we are not in a 
    // light show then ask the user
    // for the sequence.
    if (!asked && !lightShow) {
        Serial.println("Please sequenceInput the sequence of colors you'd like to change in the format RGBCMYW, where \nR = Red, \nG = Green, \nB = Blue, \nC = Cyan, \nM = Magenta, \nY = Yellow, \nW = White. \nFor example, RGB, GRBCW, etc.");
        String sequenceInputIn;
        
        // Wait for the user to input a sequence
        // then process it.
        do {
            Serial.print("Sequence: ");
            do {
                sequenceInputIn = Serial.readString();
            } while (sequenceInputIn.length() == 0);
            Serial.println(sequenceInputIn);
            sequenceInputIn.trim();
            sequenceInputIn.toUpperCase();
        } while (!validateInput(sequenceInputIn));

        asked = true;
    
    // If we are displaying a light show then
    // loop through the colors and have a 
    // custom reset of the current color
    } else if (lightShow) {
        currentColor = (currentColor < 6) ? currentColor + 1 : 0;
        changeBrightness();

    // If we have gotten a sequence but haven't 
    // set the brightness of the colors then
    // go through and do that now.
    } else {
        changeBrightness();
        SerialMonitorPrint();
    }
}


//  ------------------------------
//    Change the brightness of
//       the current color.
//  ------------------------------
void changeBrightness() {
    // If the user has sequenceInputted a sequence of colors
    if (asked) {
        // Set the brightness of the current color to the potentiometer value mapped to 0-255
        colors[currentColor].brightness = map(analogRead(potentiometer), 0, 1023, 0, 255);

        // Display the color
        for (int i=0; i<3; i++) {
            if (colors[currentColor].pins[i] == -1) {
                analogWrite(colorPins[i], 0);
                continue;
            }
            analogWrite(
                colors[currentColor].pins[i], 
                map(
                    colors[currentColor].values[i], 
                    0, 255, 
                    0, colors[currentColor].brightness)
            );
        }

    // Display the light show
    } else {
        // Go through all pins
        for (int i=0; i<3; i++) {
            if (colors[currentColor].pins[i] == -1) {
                analogWrite(colorPins[i], 0);
                continue;
            }
            // Display the color
            analogWrite(colors[currentColor].pins[i], map(colors[currentColor].values[i], 0, 255, 0, colors[currentColor].brightness));

            // Wait to initiate the color changing effect
            delay(colorChangeDelay);
        }
    }
}


//  ------------------------------
//    Set the values of crucal 
//           vairables.
//  ------------------------------
void setValue() {
    // If user wants to reset the colors used
    // reset vars to defaults
    if (lightShow) {
        currentColor = 0;
        lightShow = false;
        asked = false;
        return;
    }

    // If the user wants to set the brightness of the next color
    // increment the current color
    if (currentColor < 6 && colors[currentColor + 1] != emptyColor) {
        currentColor++;
    } else {
        currentColor = -1;
        lightShow = true;
    }

    // If the user reached the end of the colors
    // start to display colors in a loop
    if (lightShow) {
        asked = false;
        Serial.println("Starting light show...");
    }
}

//  ------------------------------
//    Output color stats.
//  ------------------------------
void SerialMonitorPrint() {
    Serial.print("Current color: ");
    Serial.print(colors[currentColor].name);
    Serial.print(", Red: ");
    Serial.print(map(colors[currentColor].values[0], 0, 255, 0, colors[currentColor].brightness));
    Serial.print(", Green: ");
    Serial.print(map(colors[currentColor].values[1], 0, 255, 0, colors[currentColor].brightness));
    Serial.print(", Blue: ");
    Serial.println(map(colors[currentColor].values[2], 0, 255, 0, colors[currentColor].brightness));
}

//  ------------------------------
//    Validate the user input.
//  ------------------------------
bool validateInput(String sequenceInput) {
    // Reset the colors array
    for (int i=0; i<7; i++) {
        colors[i] = emptyColor;
    }

    // Check to see if the sequenceInput is the correct length
    if (sequenceInput.length() > 7 || sequenceInput.length() == 0) {
        Serial.println("Invalid length");
        return false;
    }

    int indexModifier = 0;
    for (int i=0; i<sequenceInput.length(); i++) {
        // Check to see if the character is a valid color
        switch (sequenceInput[i]) {
            case 'R':
                colors[i + indexModifier] = color {
                    {RGBRedPin, -1, -1},
                    {255, 0, 0},
                    0,
                    "Red"
                };
                break;
            
            case 'G':
                colors[i + indexModifier] = color {
                    {-1, RGBGreenPin, -1},
                    {0, 255, 0},
                    0,
                    "Green"
                };
                break;
            
            case 'B':
                colors[i + indexModifier] = color {
                    {-1, -1, RGBBluePin},
                    {0, 0, 255},
                    0,
                    "Blue"
                };
                break;

            case 'C':
                colors[i + indexModifier] = color {
                    {-1, RGBGreenPin, RGBBluePin},
                    {0, 255, 255},
                    0,
                    "Cyan"
                };
                break;

            case 'M':
                colors[i + indexModifier] = color {
                    {RGBRedPin, -1, RGBBluePin},
                    {255, 0, 255},
                    0,
                    "Magenta"
                };
                break;
            
            case 'Y':
                colors[i + indexModifier] = color {
                    {RGBRedPin, RGBGreenPin, -1},
                    {255, 255, 0},
                    0,
                    "Yellow"
                };
                break;

            case 'W':
                colors[i + indexModifier] = color {
                    {RGBRedPin, RGBGreenPin, RGBBluePin},
                    {255, 255, 255},
                    0,
                    "White"
                };
                break;
            
            default:
                Serial.print("Color '");
                Serial.print(sequenceInput[i]);
                Serial.println("' is not valid skipping...");
                indexModifier--;
                break;
        }
    }

    // Input has passed all tests
    Serial.println("Input valid continuing...");
    return true;
}
