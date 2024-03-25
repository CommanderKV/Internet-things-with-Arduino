//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 2             Date: 2023-11-03  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program will use the LCD to display my name on the screen. It   |
//  |            rotate in a circle clockwise around the display.            |
//  \________________________________________________________________________/

#include <LiquidCrystal.h>

// Initialise the Serial LCD.
LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // These pin numbers are hard coded in on the serial backpack board.

//  --------------------
//    Setup vairables.
//  --------------------
String name = "Kyler";
int distance = 16 - name.length();
int pauseTime = 100;

//  --------------
//    Setup lcd.
//  --------------
void setup() {
    lcd.begin(16, 2); // Initialize the LCD.
}

//  -----------------------------
//    Main code execution loop.
//  -----------------------------
void loop() {
    goRight();
    goLeft();
}

//  ---------------------------
//    Send text to the right.
//  ---------------------------
void goRight() {
    for (int i=0; i<distance; i++) {
        lcd.clear();
        lcd.setCursor(i, 0);
        lcd.print(name);
        delay(pauseTime);
    }
}

//  --------------------------
//    Send text to the left.
//  --------------------------
void goLeft() {
    for (int i=0; i<distance; i++) {
        lcd.clear();
        lcd.setCursor(distance - i, 1);
        lcd.print(name);
        delay(pauseTime);
    }
}