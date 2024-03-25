//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 4             Date: 2023-11-03  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |  This program will use the LCD to ask the user a series of questions.  |
//  |   If the user selects yes or no it will increment a counter. At the    |
//  |                    end it will display the results.                    |
//  \________________________________________________________________________/

#include <LiquidCrystal.h>

// Initialise the Serial LCD.
LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // These pin numbers are hard coded in on the serial backpack board.

//  ------------------------------
//    Initalize vairables
//  ------------------------------
int leftButton = 3;
int rightButton = 2;

String questions[5] = {
    "You like bread",
    "You like death",
    "You like code",
    "You like food",
    "You like games"
};

int selected[2] = {0, 0};
int stop = 0;


//  ------------------------------
//    Initalize, LCD, buttons,
//         and inturupts.
//  ------------------------------
void setup() {
    lcd.begin(16, 2); // Initialize the LCD.
    pinMode(leftButton, INPUT);
    pinMode(rightButton, INPUT);

    attachInterrupt(digitalPinToInterrupt(leftButton), yes, RISING);
    attachInterrupt(digitalPinToInterrupt(rightButton), no, RISING);
}

//  ------------------------------
//    Main code loop.
//  ------------------------------
void loop() {
    welcome();
    for (int choice=0; choice<5; choice++) {
        switch (askQuestion(questions[choice])) {
            case true:
                selected[0] += 1;
                break;
            case false:
                selected[1] += 1;
                break;
        }
    }
    displayResults();
}

//  ------------------------------
//    Yes interrupt.
//  ------------------------------
void yes() {
    stop = 1;
}

//  ------------------------------
//    No interrupt.
//  ------------------------------
void no() {
    stop = -1;
}

//  ------------------------------
//    Welcome screen.
//  ------------------------------
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
//    Ask the user a question.
//  ------------------------------
bool askQuestion(String question) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Yes         No");

    lcd.setCursor(0, 1);
    lcd.print(question);

    stop = 0;
    while (stop == 0) {}
    return (stop == 1);
}

//  ------------------------------
//    Display the results.
//  ------------------------------
void displayResults() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Yes count: ");
    lcd.print(selected[0]);

    lcd.setCursor(0, 1);
    lcd.print("No count: ");
    lcd.print(selected[1]);

    stop = 0;
    while (stop == 0) {}
}
