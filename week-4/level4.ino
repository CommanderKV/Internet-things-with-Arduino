//   ________________________________________________________________________  
//  /  Name: Kyler Visser            level 4               Date: 2023-09-28  \
//  |                                                                        |
//  |                              Description                               |
//  |                                                                        |
//  |   This program will take the light level and display it in binary on   |
//  |                               four LEDs.                               |
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
    Serial.print("Number: ");
    Serial.print(data);
    Serial.print(" Binary: ");
    Serial.println(String(data, BIN));

    displayNum(data);
}

//  -------------------------------
//     Turn on specified LEDs by 
//    looking at the binary data.
//  -------------------------------
void displayNum(int num) {
    if (num & 0b00001000) {digitalWrite(red, HIGH);} 
        else {digitalWrite(red, LOW);}

    if (num & 0b00000100) {digitalWrite(blue, HIGH);} 
        else {digitalWrite(blue, LOW);}

    if (num & 0b00000010) {digitalWrite(green, HIGH);} 
        else {digitalWrite(green, LOW);}

    if (num & 0b00000001) {digitalWrite(yellow, HIGH);} 
        else {digitalWrite(yellow, LOW);}
}