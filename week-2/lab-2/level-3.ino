//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 3            Date: 20223-09-14  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |  This program utalizes pins 9, 10, 11 to connect to an RGB LED. Using  | 
//  |         this LED it will display all of the following colors:          |
//  |                                                                        |
//  |                   - Red                     - Green                    |
//  |                   - Blue                    - Magenta                  |
//  |                   - Yellow                  - Cyan                     |
//  |                                - White                                 |
//  |                                                                        |
//  |  It will display all of the colors in 1 second the first time around.  |
//  |  After the first loop it will increment the time they all need to be   |
//  |             displayed in by 1 second or 1000 miliseconds.              |
//  \________________________________________________________________________/

//  ------------------------
//    Initalize vairables.
//  ------------------------
int RGBRedPin = 9; 
int RGBGreenPin = 10; 
int RGBBluePin = 11; 
int maxShowTime = 15000;
int spacing;

//  ---------------
//    Setup pins.
//  ---------------
void setup() {
    pinMode(RGBRedPin, OUTPUT); 
    pinMode(RGBGreenPin, OUTPUT); 
    pinMode(RGBBluePin, OUTPUT); 
}

void loop() { //The loop function runs forever.

    //  ------------------------------------
    //    Loop over all colors and display 
    //    them within the limit of total 
    //            time 10 times.
    //  ------------------------------------
    int totalTime = 1000;
    for (int i=0; i<10; i++) {
        spacing = totalTime / 7;
        red(spacing);
        green(spacing);
        blue(spacing);
        magenta(spacing);
        yellow(spacing);
        cyan(spacing);
        white(spacing);
        totalTime += 1000;
    }
}

//  ----------------
//    Display red.
//  ----------------
void red(float time) {
    digitalWrite(RGBRedPin, HIGH);
    delay(time);
    digitalWrite(RGBRedPin, LOW);
}


//  ------------------
//    Display Green.
//  ------------------
void green(float time) {
    digitalWrite(RGBGreenPin, HIGH); 
    delay(time); 
    digitalWrite(RGBGreenPin, LOW); 
}

//  -----------------
//    Display Blue.
//  -----------------
void blue(float time) {
    digitalWrite(RGBBluePin, HIGH); 
    delay(time); 
    digitalWrite(RGBBluePin, LOW);
}


//  --------------------
//    Display Magenta.
//  --------------------
void magenta(float time) {
    digitalWrite(RGBRedPin, HIGH); 
    digitalWrite(RGBBluePin, HIGH); 
    delay(time); 
    digitalWrite(RGBRedPin, LOW);
    digitalWrite(RGBBluePin, LOW); 
}

//  -------------------
//    Display Yellow.
//  -------------------
void yellow(float time) {
    digitalWrite(RGBRedPin, HIGH);
    digitalWrite(RGBGreenPin, HIGH); 
    delay(time);
    digitalWrite(RGBRedPin, LOW);
    digitalWrite(RGBGreenPin, LOW);
}

//  -----------------
//    Display Cyan.
//  -----------------
void cyan(float time) {
    digitalWrite(RGBBluePin, HIGH);
    digitalWrite(RGBGreenPin, HIGH);
    delay(time);
    digitalWrite(RGBBluePin, LOW);
    digitalWrite(RGBGreenPin, LOW);
}

//  ------------------
//    Display White.
//  ------------------
void white(float time) {
    digitalWrite(RGBRedPin, HIGH);
    digitalWrite(RGBBluePin, HIGH);
    digitalWrite(RGBGreenPin, HIGH);
    delay(time); 
    digitalWrite(RGBRedPin, LOW);
    digitalWrite(RGBBluePin, LOW);
    digitalWrite(RGBGreenPin, LOW);
}
