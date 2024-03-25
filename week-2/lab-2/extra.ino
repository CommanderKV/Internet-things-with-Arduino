//   ________________________________________________________________________  
//  /  Name: Kyler Visser               Extra             Date: 20223-09-14  \
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
//  |  The colors will be displayed randomly and the duration they will be   |
//  |                displayed in is also randomly decided.                  |
//  \________________________________________________________________________/

//  ------------------------
//    Initalize vairables.
//  ------------------------
int RGBRedPin = 9;
int RGBGreenPin = 10;
int RGBBluePin = 11;
int maxShowTime = 15000;
char colors[] = {'R', 'G', 'B', 'M', 'Y', 'C', 'W'};

//  ---------------------------------------
//    Setup all pins, random, and Serial.
//  ---------------------------------------
void setup() {
    pinMode(RGBRedPin, OUTPUT);
    pinMode(RGBGreenPin, OUTPUT);
    pinMode(RGBBluePin, OUTPUT);
    Serial.begin(9600);
    Serial.println("------------------------------");
    randomSeed(analogRead(0));
}

void loop() {
    //  ---------------------
    //    Define vairables.
    //  ---------------------
    unsigned long startTime = millis();
    unsigned long resetTime = 15;
    long totalTime = 0;
    int counter = 1;

    //  -----------------------------------
    //    Loop over until a combined time 
    //      of 15 seconds is achieved.
    //  -----------------------------------
    while (totalTime <= resetTime) {

        //  -----------------------------
        //    Get random values and add
        //            to total.
        //  -----------------------------
        long length = random(3, 21);
        long time = random(1, 15);
        totalTime += time;
        String combo = "";

        for (int i=0; i<length; i++) {
            combo += colors[random(0, 7)];
        }

        //  --------------------
        //    Execute cycle X.
        //  --------------------
        unsigned long timeX = millis();
        cycle(combo, time);

        //  --------------------------------
        //    Output information for user.
        //  --------------------------------
        Serial.print("| Cycle ");
        Serial.print(counter);
        Serial.print(" time: ");
        Serial.print((millis() - timeX) / 1000);
        Serial.print(" Total: ");
        Serial.println((millis() - startTime) / 1000);
    }

    //  ------------------------
    //    Display end of loop.
    //  ------------------------
    Serial.println("| End of Loop\n------------------------------");
    delay(5000);

}

//  ------------------------
//    Run through a cycle.
//  ------------------------
void cycle(String strData, int totalTime) {
    totalTime = totalTime * 1000;
    for (int i=0; i<strData.length(); i++) {
        char data = strData[i];
        float timePerEach = totalTime/strData.length();
        if (data == 'R') {
            red(timePerEach);
        } else if (data == 'G') {
            green(timePerEach);
        } else if (data == 'B') {
            blue(timePerEach);
        } else if (data == 'M') {
            magenta(timePerEach);
        } else if (data == 'Y') {
            yellow(timePerEach);
        } else if (data == 'C') {
            cyan(timePerEach);
        } else if (data == 'W') {
            white(timePerEach);
        }
        
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
