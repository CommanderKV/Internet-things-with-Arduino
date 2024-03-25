//   ________________________________________________________________________  
//  /  Name: Kyler Visser             Level 2             Date: 20223-09-07  \
//  |                                                                        |
//  |                               Description                              |
//  |                                                                        |
//  |    This program will utalize pin 13 on an arduino uno to allow for     |
//  |  morse code to be displayed through the LED connected to pin 13. The   |
//  |   original code is set to display "Hi you" in morse code using the     |
//  |                               blue LED.                                |
//  \________________________________________________________________________/

//  ------------------------
//    Initalize vairables.
//  ------------------------
int blueLED = 13;
char morseCode[26][5] = {
    {'A', 'D', 'B', 'X', 'X'},
    {'B', 'B', 'D', 'D', 'D'},
    {'C', 'B', 'D', 'B', 'D'},
    {'D', 'B', 'D', 'D', 'X'},
    {'E', 'D', 'X', 'X', 'X'},
    {'F', 'D', 'D', 'B', 'D'},
    {'G', 'B', 'B', 'D', 'X'},
    {'H', 'D', 'D', 'D', 'D'},
    {'I', 'D', 'D', 'X', 'X'},
    {'J', 'D', 'B', 'B', 'B'},
    {'K', 'B', 'D', 'B', 'X'},
    {'L', 'D', 'B', 'D', 'D'},
    {'M', 'B', 'B', 'X', 'X'},
    {'N', 'B', 'D', 'X', 'X'},
    {'O', 'B', 'B', 'B', 'X'},
    {'P', 'D', 'B', 'B', 'D'},
    {'Q', 'B', 'B', 'D', 'B'},
    {'R', 'D', 'B', 'D', 'X'},
    {'S', 'D', 'D', 'D', 'X'},
    {'T', 'B', 'X', 'X', 'X'},
    {'U', 'D', 'D', 'B', 'X'},
    {'V', 'D', 'D', 'D', 'B'},
    {'W', 'D', 'B', 'B', 'X'},
    {'X', 'B', 'D', 'D', 'B'},
    {'Y', 'B', 'D', 'B', 'B'},
    {'Z', 'B', 'B', 'D', 'D'}
};


//  -----------------------------
//    Setting up the pins used.
//  -----------------------------
void setup()
{
	pinMode(blueLED, OUTPUT);
}

//  ----------------------
//    Main program loop.
//  ----------------------
void loop()
{
    writeText("Hi you");
}

//  ---------------------------------------
//    Used to display text in morse code.
//  ---------------------------------------
void writeText(String text) {
    // Go through the incoming text
    for (int i=0; i<text.length(); i++) {
        char currentChar = toupper(text[i]);

        // If we are not communicating a space proceed
        if (currentChar != ' ') {

            // Go thorough the morseCode array to find
            // what letter matches the current letter
            for (int j=0; j<26; j++) {
                if (currentChar == morseCode[j][0]) {

                    // Once letter is found display it
                    for (int k=0; k<4; k++) {
                        if (morseCode[j][1+k] == 'B') {
                            displayUnit(3);
                        } else if (morseCode[j][1+k] == 'D') {
                            displayUnit(1);
                        } else {
                            // Found placeholder skip the rest
                            break;
                        }
                        // Delay between pats of a letter
                        delay(200);
                    }
                }
            }
            // Delay between letters
            delay(600);
        } else {
            // Delay between words
            delay(1400);
        }
    }
}

//  --------------------------------------------------
//    Display a unit according to the passed length.
//  --------------------------------------------------
void displayUnit(int unitLength) {
    digitalWrite(blueLED, HIGH);
    delay(200*unitLength);
    digitalWrite(blueLED, LOW);
}
