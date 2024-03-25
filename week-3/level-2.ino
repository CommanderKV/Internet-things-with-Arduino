//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 2             Date: 2023-09-21  \
//  |                                                                        |
//  |                               Description                              |
//  |                                                                        |
//  |  This program will utalize a potentiometer and a RGB LED. The program  |
//  |    will then use the potentiometer will control how long each color    |
//  |     stays on for. The colors that will be utalized are Red, Green,     |
//  |                                 Blue.                                  |
//  \________________________________________________________________________/

//  --------------------
//    Setup vairables.
//  --------------------
int rotationPin = A0;
int data = 0;
int redPin = 9;
int bluePin = 11;
int greenPin = 10;
int MAXTIME = 5000;
int modifier = 5;

//  -------------------------------
//    Setup pins and serial port.
//  -------------------------------
void setup() {
    Serial.begin(9600);
    pinMode(rotationPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(greenPin, OUTPUT);
}

//  ----------------------
//    Main program loop.
//  ----------------------
void loop() {
    customDelay();
    red();
    customDelay();
    green();
    customDelay();
    blue();
}

//  -------------------------------------
//    Delay for a set time depending on 
//    what the potentiometer is set to.
//  -------------------------------------
void customDelay() {
    int counter = 0;
    while (getTime() - counter > 0) {
        delay(1);
        counter++;
    }
    Serial.println(counter);
}

//  ----------------------------
//    Get the time needed that
//        is non-negative.
//  ----------------------------
int getTime() {
    int time = (MAXTIME - (analogRead(rotationPin) * modifier));
    if (time > 0) {
        return time;
    } else {
        return 0;
    }
}

//  ----------------
//    Display red.
//  ----------------
void red() {
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
}

//  -----------------
//    Display blue.
//  -----------------
void blue() {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);
}

//  ------------------
//    Display green.
//  ------------------
void green() {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, HIGH);
}