//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 4             Date: 2023-10-15  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program will take in an input from the user and then display    |
//  |   one color at a time from the sequence. The user can then use the     |
//  |    poteniomiter to adjust the brightness. If the user inputs a non     |
//  |  exsitant color then the program will give a warnin about that color.  |
//  |     If they input a color that is already in the sequence then the     |
//  |                        program will also error.                        |
//  \________________________________________________________________________/


//  ------------------------------
//    Initalize vairables.
//  ------------------------------
const int RGBRedPin = 9;    
const int RGBGreenPin = 10; 
const int RGBBluePin = 11;  

int potentiometer = A0;
int lockoutButton = 2;

int currentColor = 0;

int colorList[] = {-1, -1, -1};
int colorValues[3] = {0, 0, 0};
String display[3][2] = {
    {String(RGBRedPin), "Red"},
    {String(RGBGreenPin), "Green"},
    {String(RGBBluePin), "Blue"}
};

bool asked = false;

//  ------------------------------
//    Setup the pins and 
//    inturupts.
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


//  ------------------------------
//    Main loop of the program.
//  ------------------------------
void loop() {
    if (!asked) {
        getInput();
    }
    changeBrightness();
    SerialMonitorPrint();
}

//  ------------------------------
//    Change the brightness of
//    the RGB led.
//  ------------------------------
void changeBrightness() {
    if (asked) {
        colorValues[currentColor] = map(analogRead(potentiometer), 0, 1023, 0, 255);
        analogWrite(colorList[currentColor], colorValues[currentColor]);
    } else {
        for (int i=0; i<sizeof(colorList); i++) {
            analogWrite(colorList[i], colorValues[i]);
        }
    }
}

//  ------------------------------
//    Set the value of the
//    current light
//  ------------------------------
void setValue() {
    if (asked) {
        currentColor = (currentColor < 2) ? currentColor + 1 : 0;
        if (currentColor == 0) {
            asked = false;
        }
    } else {
        currentColor = 0;
    }
}

//  ------------------------------
//    Display details to users.
//  ------------------------------
void SerialMonitorPrint() {
    int values[3] = {};
    for (int i=0; i<sizeof(colorList); i++) {
        switch (colorList[i]) {
            case RGBRedPin:
                values[0] = colorValues[i];
                break;
            
            case RGBGreenPin:
                values[1] = colorValues[i];
                break;
            
            case RGBBluePin:
                values[2] = colorValues[i];     
                break;
        }
    }

    Serial.print("Red: ");
    Serial.print(values[0]);
    Serial.print(" Green: ");
    Serial.print(values[1]);
    Serial.print(" Blue: ");
    Serial.println(values[2]);
}


//  ------------------------------
//    Get the input from the 
//    user.
//  ------------------------------
void getInput() {
    Serial.println("Please input the sequence of colors you would like to change in the format RGB, \nR = Red, \nG = Green, \nB = Blue. \nFor example, RGB, GRB, BGR, etc.");
    Serial.print("Sequence: ");

    while (Serial.available() == 0) {}

    String input = Serial.readString();
    input.trim();
    input.toUpperCase();

    while (!validateInput(input)) {
        Serial.print("Sequence: ");
        
        while (Serial.available() == 0) {}

        input = Serial.readString();
        input.trim();
        input.toUpperCase();
    }

    asked = true;
}

//  ------------------------------
//    Validate the input.
//  ------------------------------
bool validateInput(String input) {
    Serial.println(input);
    colorList[0] = -1;
    colorList[1] = -1,
    colorList[2] = -1;

    // Check to see if the input is the correct length
    if (input.length() != 3) {
        Serial.println("Invalid length");
        return false;
    }

    for (int i=0; i<3; i++) {
        int number = 0;
        // Check to see if the character is a valid color
        switch (input[i]) {
            case 'R':
                number = RGBRedPin;
                break;
            
            case 'G':
                number = RGBGreenPin;
                break;
            
            case 'B':
                number = RGBBluePin;
                break;
            
            default:
                Serial.println("Invalid color");
                return false;
        }
        
        // Make sure there is no duplicate colors
        for (int j=0; j<sizeof(colorList); j++) {
            if (colorList[j] == number) {
                Serial.println("Duplicate color");
                return false;
            }
        }
        colorList[i] = number;
    }

    // Input has passed all tests
    return true;
}