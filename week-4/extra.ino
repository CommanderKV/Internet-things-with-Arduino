//   ________________________________________________________________________  
//  /  Name: Kyler Visser             Extra                Date: 2023-09-28  \
//  |                                                                        |
//  |                              Description                               |
//  |                                                                        |
//  |   This program will take the light level and display it in binary on   |
//  |   four LEDs. The number will be displayed and blink according to how   |
//  |                           big the number is.                           |
//  \________________________________________________________________________/

//  ---------------------------------
//    Initalize vairables and pins.
//  ---------------------------------
int lightPin = A1;
int data = 0;
int red = 12;
int blue = 13;
int green = 11;
int yellow = 10;
int lastFire = 0;
int numToDisplay[4];

//  --------------------------
//    Setup pins and serial.
//  --------------------------
void setup() {
    pinMode(lightPin, INPUT);
    pinMode(red, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);

    Serial.begin(9600);
}

//  --------------
//    Main loop.
//  --------------
void loop() {
    data = analogRead(lightPin);
    data = map(data, 6, 679, 0, 15);

    for (int i=0; i<4; i++) {
        numToDisplay[i] = bitRead(data, 3-i);
    }
    
    lightsON(numToDisplay);
}

//  ------------------------
//    Turn all lights off.
//  ------------------------
void lightsOFF() {
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
}

//  -------------------------------
//     Determine which lights to
//    turn on based on the binary
//               array.
//  -------------------------------
void lightsON(int binNum[]) {
    Serial.print("Binary: ");
    int number = 0;
    for (int i=0; i<4; i++) {
        Serial.print(binNum[i]);
        if (binNum[i] == 1) {
            number += pow(2, 3-i)+.5;
        }
    }
    Serial.print(" Decimal: ");
    Serial.println(number);

    int timeToDelay = map(number, 0, 15, 2000, 300);
    
    displayNum(number);
    delay(timeToDelay);
    lightsOFF();
    delay(timeToDelay);
}

//  --------------------------------
//    Display the number in binary
//         on the four LEDs.
//  --------------------------------
void displayNum(int num) {
    if (num & 0b00001000) {digitalWrite(red, HIGH);} else {digitalWrite(red, LOW);}

    if (num & 0b00000100) {digitalWrite(blue, HIGH);} else {digitalWrite(blue, LOW);}

    if (num & 0b00000010) {digitalWrite(green, HIGH);} else {digitalWrite(green, LOW);}

    if (num & 0b00000001) {digitalWrite(yellow, HIGH);} else {digitalWrite(yellow, LOW);}
}