//   ________________________________________________________________________  
//  /  Name: Kyler Visser             level 2              Date: 2023-00-00  \
//  |                                                                        |
//  |                               Description                              |
//  |                                                                        |
//  |   This program will take an input in from the potentiometer and the    |
//  |    change the brightness of the green LED based off of that input.     |
//  \________________________________________________________________________/

//  ------------------------------
//    Initalize variables
//  ------------------------------
int RGBRedPin = 9;    
int RGBGreenPin = 10; 
int RGBBluePin = 11;  
int fadeDelay = 5;    

int potentiometer = A0;

//  ------------------------------
//    Setup pins
//  ------------------------------
void setup() {
    pinMode(RGBRedPin, OUTPUT);
    pinMode(RGBGreenPin, OUTPUT);
    pinMode(RGBBluePin, OUTPUT);

    pinMode(potentiometer, INPUT);
}

//  ------------------------------
//    Display the color based
//    based off the potentiometer
//  ------------------------------
void loop() {

    int potentiometerValue = analogRead(potentiometer);
    int mappedPotentiometerValue = map(potentiometerValue, 0, 1023, 0, 255);
    analogWrite(RGBGreenPin, mappedPotentiometerValue);
}