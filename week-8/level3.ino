//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 3             Date: 2023-11-03  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |  This program will use the LCD to display a menu of food options. The  |
//  |    first menu contains the appetizers, the second contains the main    |
//  |  course, and the third contains the dessert. The user will be able to  |
//  |  select an option from each menu by pressing the left or right button. |
//  |                                                                        |
//  |  At the start of the program, the user will be greeted with a welcome  |
//  |  screen. To contiune to the menu, the user will press either the left  |
//  |  or the right button. At the end of the program there will be another  |
//  |         screen to tell the users the food they have selected.          |
//  \________________________________________________________________________/
#include <LiquidCrystal.h>

// Initialise the Serial LCD.
LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // These pin numbers are hard coded in on the serial backpack board.

//  -----------------------
//    Initlize vairables.
//  -----------------------
int leftButton = 3;
int rightButton = 2;

String optionsAvailable[3][5] = {
    {"Bread",       "Cheese sticks",    "Pretzels",     "Nachos",       "Chicken wings"}, // Apatizers
    {"Steak",       "Pasta",            "Chicken",      "Fish",         "Vegetarian"}, // Main course
    {"Ice cream",   "Cake",             "Pie",          "Pudding",      "Fruit salad"}  // Dessert
};

String selected[3];
bool stop = false;
int displayDelay = 2000;

//  -----------------------------
//    Setup inturupts, buttons,
//          and the LCD.
//  -----------------------------
void setup() {
    lcd.begin(16, 2); // Initialize the LCD.
    pinMode(leftButton, INPUT);
    pinMode(rightButton, INPUT);

    attachInterrupt(digitalPinToInterrupt(leftButton), buttonPressed, RISING);
    attachInterrupt(digitalPinToInterrupt(rightButton), buttonPressed, RISING);
}

//  -------------------
//    Main code loop.
//  -------------------
void loop() {
    welcome();
    for (int choice=0; choice<3; choice++) {
        stop = false;
        optionCycle(optionsAvailable[choice], choice);
    }
    displayResults();
}

//  -------------------
//    Welcome screen.
//  -------------------
void welcome() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to");
    lcd.setCursor(4, 1);
    lcd.print("Kyler's TV");
    while (true) {
        if (digitalRead(leftButton) == HIGH || digitalRead(rightButton) == HIGH) {
            break;
        }
    }
}

//  ------------------------------
//    Inturupt for button press.
//  ------------------------------
void buttonPressed() {
    stop = true;
}

//  -------------------------------
//    Cycle  through the options.
//  -------------------------------
void optionCycle(String options[5], int choice) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Select a food:");
    bool run = true;
    while (run) {
        for (int i=0; i<5; i++) {
            lcd.setCursor(0, 1);
            lcd.print(">              ");

            lcd.setCursor(2, 1);
            lcd.print(options[i]);
            delay(displayDelay);

            if (stop) {
                run = false;
                selected[choice] = options[i];
                break;
            }
        }
    }
}

//  ------------------------------
//    Display the selected food.
//  ------------------------------
void displayResults() {
    lcd.clear();
    lcd.print("Selected food:");
    stop = false;
    while (!stop) {
        for (int i=0; i<3; i++) {
            lcd.setCursor(0, 1);
            lcd.print(">              ");
            lcd.setCursor(2, 1);
            lcd.print(selected[i]);
            delay(displayDelay);
        }
    }
}
