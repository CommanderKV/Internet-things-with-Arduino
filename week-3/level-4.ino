//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 4            Date:  2023-09-21  \
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

//  ----------------------------
//    Initalize RGB structure.
//  ----------------------------
struct rgbColor {
    int R;
    int G;
    int B;
};

//  -------------------------------
//    Initalize RGB color values.
//  -------------------------------
rgbColor colors[] = {
    {255, 0, 0},        // Red
    {0, 255, 0},        // Green
    {0, 0, 255},        // Blue
};

//  ------------------------------------
//    Initalize Acceptable RGB inputs.
//  ------------------------------------
char colorLetters[] = {
    'R',
    'G',
    'B',
};

//  ------------------------------
//    Set pins and initalize the 
//         Serial monitor.
//  ------------------------------
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
        int incomingByte = Serial.read();
        switch (incomingByte) {
            case 'R':
                RGB(colors[0].R, colors[0].G, colors[0].B);
                break;

            case 'G':
                RGB(colors[3].R, colors[3].G, colors[3].B);
                break;

            case 'B':
                RGB(colors[4].R, colors[4].G, colors[4].B);
                break;
            
            default:
                Serial.println("Unrecognized color.");
                break;
        }
        delay(displayTime);
        sent = false;
    }
    
}

//  -----------------------------
//    Ask user what color combo 
//           they want.
//  -----------------------------
void ask() {
    if (!sent) {
        Serial.println("Enter a combination of the following colors to be displayed:");
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