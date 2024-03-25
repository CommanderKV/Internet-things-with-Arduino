//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 2            Date: 20223-09-14  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program utalizes pins 9, 10, and 11. It will connect to a RGB   |
//  |     LED and allow it to display multiple diffrent colors that are      |
//  |   hardcoded. The amount of time the LED displays a certain color is    |
//  |     decided dynamically by how much time we want the sequence to       |
//  |                                   take.                                |
//  \________________________________________________________________________/

//  ------------------------
//    Initalize vairables.
//  ------------------------
int RGBRedPin = 9;
int RGBGreenPin = 10;
int RGBBluePin = 11;
int maxShowTime = 15000;

//  ----------------------------------
//    Setup pins and Serial monitor.
//  ----------------------------------
void setup() {
    pinMode(RGBRedPin, OUTPUT);
    pinMode(RGBGreenPin, OUTPUT);
    pinMode(RGBBluePin, OUTPUT);
	Serial.begin(9600);
    Serial.println("------------------------------");
}

void loop() {
    unsigned long startTime = millis();

    //  ---------------------------------
    //    Display this cycle and output
    //        details to the user.
    //  ---------------------------------
    cycle("GBRW", 3); // Cycle 1
    Serial.print("| Cycle 1 time: ");
    Serial.print((millis() - startTime) / 1000);
    Serial.print(" Total: ");
    Serial.println((millis() - startTime) / 1000);

    //  ---------------------------------
    //    Display this cycle and output
    //        details to the user.
    //  ---------------------------------
    unsigned long start2 = millis();
    cycle("CYM", 4); // Cycle 2
    Serial.print("| Cycle 2 time: ");
    Serial.print((millis() - start2) / 1000);
    Serial.print(" Total: ");
    Serial.println((millis() - startTime) / 1000);

    //  ---------------------------------
    //    Display this cycle and output
    //        details to the user.
    //  ---------------------------------
    unsigned long start3 = millis();
    cycle("BMGRCW", 8); // Cycle 3
    Serial.print("| Cycle 3 time: ");
    Serial.print((millis() - start3) / 1000);
    Serial.print(" Total: ");
    Serial.println((millis() - startTime) / 1000);

    //  --------------------------
    //    Display End of Cycles.
    //  --------------------------
    Serial.println("| End of cycles\n------------------------------");
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
