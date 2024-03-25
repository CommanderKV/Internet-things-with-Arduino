//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 3            Date:  2023-09-21  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |    This program utalizes a potentiometer and a RGB LED. The program    |
//  |      use these to create a color selector. Depending on what the       |
//  |     potentiometer is set to the RGB LED will be a diffrent color.      |
//  \________________________________________________________________________/

//  ------------------------
//    Initalize vairables.
//  ------------------------
int rotationPin = A0;
int redPin = 9;
int bluePin = 11;
int greenPin = 10;
int maxValueOfSensor = 1023;
int sectionLength;

//  ----------------------------
//    Initalize RGB structure.
//  ----------------------------
struct rgbColor {
  	int R;
  	int G;
  	int B;
};

//  -------------------------
//    Initalize RGB values.
//  -------------------------
rgbColor colors[] = {
    {255, 0, 0},    // Red
    {255, 165, 0},  // Orange
    {255, 255, 0},  // Yellow
    {0, 255, 0},    // Green
    {0, 0, 255},    // Blue
    {128, 0, 128}   // Purple
};

//  -------------------------------
//    Setup pins and serial port.
//  -------------------------------
void setup() {
    Serial.begin(9600);
    pinMode(rotationPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    
    sectionLength = sizeof(colors)/sizeof(rgbColor);
}

//  ----------------------
//    Main program loop.
//  ----------------------
void loop() {
    int posOfPotentiometer = analogRead(rotationPin);
    float space = maxValueOfSensor/sectionLength;
    for (int i=0; i<sectionLength; i++) {
        // lower bound for color X <= position of the potentiometer < upper bound for color X
        if (space*i <= posOfPotentiometer && posOfPotentiometer < space*(i+1)) {
            RGB(colors[i].R, colors[i].G, colors[i].B);
        }
    }
}

//  ----------------------
//    Display RGB value.
//  ----------------------
void RGB(int R, int G, int B) {
    analogWrite(redPin, R);
    analogWrite(greenPin, G);
    analogWrite(bluePin, B);
}