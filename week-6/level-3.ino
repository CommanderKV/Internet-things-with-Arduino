//   ________________________________________________________________________  
//  /  Name: Kyler Visser             level 3              Date: 2023-00-00  \
//  |                                                                        |
//  |                              Desctipition                              |
//  |                                                                        |
//  |  This program will change the brightness of the LED based off of the   |
//  |   current color and the potentiometer. The user can change the color   |
//  |                        by pressing the button.                         |
//  \________________________________________________________________________/

//  ------------------------------
//    Initalize variables.
//  ------------------------------
int RGBRedPin = 9;    
int RGBGreenPin = 10; 
int RGBBluePin = 11;  
int fadeDelay = 5;    

int potentiometer = A0;
int lockoutButton = 2;

int currentColor = 0;
int colorValues[3] = {0, 0, 0};

//  ------------------------------
//    Setup pins and inturupts.
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
//    Main loop
//  ------------------------------
void loop() {
    changeBrightness();
}

//  ------------------------------
//    Change the value of the 
//    brightness based off of 
//       the poteniometer.
//  ------------------------------
void changeBrightness() {
    int value = map(analogRead(potentiometer), 0, 1023, 0, 255);
    switch (currentColor) {
    case 0:
        colorValues[0] = value;
        analogWrite(RGBRedPin, colorValues[0]);
        break;
    
    case 1:
        colorValues[1] = value;
        analogWrite(RGBGreenPin, colorValues[1]);
        break;

    case 2:
        colorValues[2] = value;
        analogWrite(RGBBluePin, colorValues[2]);
        break;
    }  
    
}

//  ------------------------------
//    Change the current color
//  ------------------------------
void setValue() {
    currentColor = (currentColor <= 2) ? currentColor + 1 : 0;
    SerialMonitorPrint();
}

//  ------------------------------
//    Output the details of the 
//      current color to the 
//            serial.
//  ------------------------------
void SerialMonitorPrint() {
    Serial.print("Red: ");
    Serial.print(colorValues[0]);
    Serial.print("Green: ");
    Serial.print(colorValues[1]);
    Serial.print("Blue: ");
    Serial.println(colorValues[2]);
}