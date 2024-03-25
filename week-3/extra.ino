//   ________________________________________________________________________  
//  /  Name: Kyler Visser               Extra             Date:  2023-09-21  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program utalizes an RGB LED and the serial line. The program    |
//  |  will ask for a color to display to the user then it will display the  |
//  |   selected color however if the color entered is wrong or invaild we   |
//  |                      will not accept the input.                        |
//  \________________________________________________________________________/

//  ------------------------
//    Initalize vairables.
//  ------------------------
int redPin = 9;
int bluePin = 11;
int greenPin = 10;
bool sent = false;
int displayTime = 500;

//  ------------------------------
//    Create a RGB color value
//  ------------------------------
struct rgbColor {
    int R;
    int G;
    int B;
};

//  ------------------------------------
//    Initalize RGB values for colors.
//  ------------------------------------
rgbColor colors[] = {
    {255, 0, 0},        // Red
    {255, 255, 0},      // Yellow
    {0, 255, 0},        // Green
    {0, 0, 255},        // Blue
    {0, 100, 100},      // Cyan
    {255, 0, 255},      // Magenta
    {255, 255, 255},    // White
};

//  ----------------------------------
//    Initalize allowed color chars.
//  ----------------------------------
char colorLetters[] = {
    'R',
    'G',
    'B',
    'C',
    'Y',
    'W',
    'M'
};


//  -----------------------------
//    Setup pins and the Serial 
//             monitor.
//  -----------------------------
void setup() {
    Serial.begin(9600);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

//  ----------------------
//    Main program loop.
//  ----------------------
void loop() {
    ask();
    while (Serial.available() > 0) {
        int incomingBytes = Serial.read();
        if (vaildInput(incomingBytes)) {
            display(incomingBytes);
            delay(displayTime);
        } else {
            break;
        }
        sent = false;
    }
}


//  ------------------------------
//    Validate the input that is 
//    given to us by checking if 
//     its in the colorLetters 
//              array.
//  ------------------------------
bool vaildInput(int input) {
    for (int i=0; i<sizeof(colorLetters); i++) {
        if (colorLetters[i] == input) {
            Serial.print("Correct value: ");
            Serial.println(colorLetters[i]);
            return true;
        }
    }
    Serial.print("Incorect value: ");
    Serial.println(input);
    return false;
}

//  -------------------------------
//    Used to display the correct 
//     color based on the input 
//              given.
//  -------------------------------
void display(int input) {
    switch (input) {
        case 'R':
            RGB(colors[0].R, colors[0].G, colors[0].B);
            break;

        case 'Y':
            RGB(colors[1].R, colors[1].G, colors[1].B);
            break;

        case 'G':
            RGB(colors[2].R, colors[2].G, colors[2].B);
            break;

        case 'B':
            RGB(colors[3].R, colors[3].G, colors[3].B);
            break;

        case 'C':
            RGB(colors[4].R, colors[4].G, colors[4].B);
            break;
        
        case 'M':
            RGB(colors[5].R, colors[5].G, colors[5].B);
            break;

        case 'W':
            RGB(colors[5].R, colors[5].G, colors[5].B);
            break;

        default:
            break;
    }
}

//  -----------------------------
//    Ask user what color combo 
//           they want.
//  -----------------------------
void ask() {
    if (!sent) {
        Serial.println("\nEnter a combination of the following colors to be displayed:");
        for (int i=0; i<sizeof(colorLetters); i++) {
            Serial.print("    -");
            Serial.println(colorLetters[i]);
        }
        Serial.println("Color combination: ");
        sent = true;
    }
}

//  --------------------------------
//    Display RGB code on the LED.
//  --------------------------------
void RGB(int R, int G, int B) {
    analogWrite(redPin, R);
    analogWrite(greenPin, G);
    analogWrite(bluePin, B);
}