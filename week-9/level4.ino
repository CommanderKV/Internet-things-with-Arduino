//  _______________________________________________________________
// /  Name: Kyler. V            level 4          Date: 2023-11-12  \
// |                                                               |
// |                          Description                          |
// |                                                               |
// |  This program will allow the user to control the LEDs on the  |
// |               arduino board using an IR remote.               |
// |                                                               |
// |  Menu 1:                                                      |
// |    1. Toggle blue LED                                  (NEW)  |
// |    2. Toggle red LED                                   (NEW)  |
// |                                                               |
// |  Menu 2:                                                      |
// |    1. Turn on next orange LED                          (NEW)  |
// |    2. Turn off current orange LED                      (NEW)  |
// |                                                               |
// |  Menu 3:                                                      |
// |    1. Random RGB color                                        |
// |    2. Toggle all LEDs                                  (NEW)  |
// |                                                               |
// |   The user can navigate through the menus using the remotes   |
// |      "SKIP-FORWARD" and "SKIP-BACK" buttons. The user can     |
// |   select an option using the respective number displayed on   |
// |                           the menu.                           |
// \_______________________________________________________________/
#include <IRremote.h>


// -----------------------------------------
//      Define variables and datatypes
// -----------------------------------------
#define IR_RECEIVE_PIN 11
#define BLUE_LED 12
#define RED_LED 13

#define RGB_RED 3
#define RGB_GREEN 5
#define RGB_BLUE 6

#define WIDTH 50


int remoteKeyPressed;
const int ORANGE_LIGHTS[4] = {10, 9, 8, 7};
int currentMenu = 1;
int maxMenu = 3;

struct Menu {
    const char* title;
    int functionLength;
    const char* options[10];
    void (*functions[10])();
};
typedef struct Menu Menu;

Menu menus[] = {
    {
        "Menu 1",                               // Title   
        2,    
        {
            "Toggle blue LED", 
            "Toggle red LED"
        },
        {
            [] {return;},
            [] {
                digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
            },
            [] {
                digitalWrite(RED_LED, !digitalRead(RED_LED));
            }
        }
    },
    {
        "Menu 2",                               // Title    
        2,    
        {
            "Turn on next orange LED", 
            "Turn off current orange LED"
        },
        {
            [] {return;},
            [] {
                if (digitalRead(ORANGE_LIGHTS[0]) == LOW) {
                    digitalWrite(ORANGE_LIGHTS[0], HIGH);
                } else {
                    for (int i=1; i<4; i++) {
                        if (digitalRead(ORANGE_LIGHTS[i]) == LOW) {
                            if (digitalRead(ORANGE_LIGHTS[i-1]) == HIGH) {
                                digitalWrite(ORANGE_LIGHTS[i], HIGH);
                                break;
                            }
                        }
                    }
                }
            },
            [] {
                for (int i=3; i>=0; i--) {
                    if (digitalRead(ORANGE_LIGHTS[i]) == HIGH) {
                        digitalWrite(ORANGE_LIGHTS[i], LOW);
                        break;
                    }
                }
            }
        }
    },
    {
        "Menu 3",                               // Title
        2,
        {
            "Random RGB color", 
            "Toggle all LEDs"
        },
        {
            [] {return;},
            [] {
                analogWrite(RGB_RED, random(0, 255));
                analogWrite(RGB_GREEN, random(0, 255));
                analogWrite(RGB_BLUE, random(0, 255));
            },
            [] {
                digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
                digitalWrite(RED_LED, !digitalRead(RED_LED));

                for (int i=0; i<4; i++) {
                    digitalWrite(ORANGE_LIGHTS[i], !digitalRead(ORANGE_LIGHTS[i]));
                }
            }
        }
    }
};

bool on = false;
bool asked = false;

// -----------------------------------------
//              Setup function.
// -----------------------------------------
void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN);

    pinMode(BLUE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    pinMode(RGB_RED, OUTPUT);
    pinMode(RGB_GREEN, OUTPUT);
    pinMode(RGB_BLUE, OUTPUT);

    for (int i=0; i<4; i++) {
        pinMode(ORANGE_LIGHTS[i], OUTPUT);
    }

    randomSeed(analogRead(0));
}

// -----------------------------------------
//               Main loop.
// -----------------------------------------
void loop() {
    // Get user to initiate program
    if (!on) {
        if (!asked) {
            Serial.println("Press the power button");
            while(!checks()) {}
            asked = true;
            currentMenu = 1;
        }
    } else {
        // Powered on, Display menu
        displayMenu(menus[currentMenu-1]);
    }
}


// -----------------------------------------
//               Description
//   Check which button was pressed and
//   execute the associated function.
// -----------------------------------------
bool checks() {
    // Check which button was pressed and execute the associated function
    switch (getIRCode()) {
        case 0:
            // Handle "POWER" button
            if (!on) {
                on = !on;
                return true;
            } else {
                Serial.println("Invalid button");
                return false;
            }

        case 1:
            // Handle "VOL+"
            Serial.println("Invalid button");
            return false;

        case 2:
            // Handle "FUNC/STOP"
            Serial.println("Invalid button");
            return false;

        case 4:
            // Handle "SKIP-BACK"
            if (on) {
                menuBack();
                return true;
            } else {
                Serial.println("Invalid button");
                return false;
            }

        case 5:
            // Handle "PAUSE"
            Serial.println("Invalid button");
            return false;

        case 6:
            // Handle "SKIP-FORWARD"
            if (on) {
                menuForward();
                return true;
            } else {
                Serial.println("Invalid button");
                return false;
            }

        case 8:
            // Handle "DOWN"
            Serial.println("Invalid button");
            return false;

        case 9:
            // Handle "VOL-"
            Serial.println("Invalid button");
            return false;

        case 10:
            // Handle "UP"
            Serial.println("Invalid button");
            return false;

        case 12:
            // Handle "0"
            return buttonPress(0);

        case 13:
            // Handle "EQ"
            Serial.println("Invalid button");
            return false;

        case 14:
            // Handle "ST/REPT"
            Serial.println("Invalid button");
            return false;

        case 16:
            // Handle "1"
            return buttonPress(1);

        case 17:
            // Handle "2"
            return buttonPress(2);

        case 18:
            // Handle "3"
            return buttonPress(3);

        case 20:
            // Handle "4"
            return buttonPress(4);

        case 21:
            // Handle "5"
            return buttonPress(5);

        case 22:
            // Handle "6"
            return buttonPress(6);

        case 24:
            // Handle "7"
            return buttonPress(7);

        case 25:
            // Handle "8"
            return buttonPress(8);

        case 26:
            // Handle "9"
            return buttonPress(9);

        default:
            // Handle unknown button
            return false;
    }
}

bool buttonPress(int functionIndex) {
    // -----------------------------------------
    //               Description
    //   When a button is pressed then execute
    //         the associated function.
    // -----------------------------------------
    if (on) {
        if (functionIndex > menus[currentMenu-1].functionLength) {
            Serial.println("Invalid button");
            return false;
        }
        if ((sizeof(menus[currentMenu-1].functions) / sizeof(menus[currentMenu-1].functions[0]))-1 >= functionIndex) {
            menus[currentMenu-1].functions[functionIndex]();
        }
        return false;
    } else {
        Serial.println("Invalid button");
        return false;
    }
}

int getIRCode() {
    // Get the IR code from the remote
    if (IrReceiver.decode()) {
        IrReceiver.resume();
        // Return the pressed key
        return IrReceiver.decodedIRData.command;
    } else {
        // No key pressed
        return -1;
    }
}


// -----------------------------------------
//             Menu functions
// -----------------------------------------

void menuBack() {
    // Go back to the previous menu
    if (currentMenu > 1) {
        currentMenu--;
    } else {
        currentMenu = maxMenu;
    }
}

void menuForward() {
    // Go forward to the next menu
    if (currentMenu < maxMenu) {
        currentMenu++;
    } else {
        currentMenu = 1;
    }
}

void displayMenu(auto menu) {
    // -----------------------------------------
    //               Description
    //            Display the menu.
    // -----------------------------------------
    displayTitle(menu.title);
    displayOptions(menu);
    displayMenuNavigator();
    displayDash(WIDTH, true);
     
    while (!checks()) {}
}

void displayTitle(const char* title) {
    // -----------------------------------------
    //               Description
    //       Display the title of the menu
    // -----------------------------------------
    int lenDashes = (WIDTH - (strlen(title)+2)) / 2;
    displayDash(lenDashes, false);
    Serial.print(" ");

    Serial.print(title);
    
    Serial.print(" ");
    displayDash(lenDashes, true);
}

void displayDash(int amount, bool endLine) {
    // -----------------------------------------
    //               Description
    //   Display a dash for the given amount.
    // -----------------------------------------
    for (int i=0; i<amount; i++) {
        Serial.print("-");
    }
    if (endLine) {
        Serial.println();
    }
}

void displayOptions(auto menu) {
    // -----------------------------------------
    //               Description
    //    Display all of the options for this
    //                   menu.
    // -----------------------------------------
    for (int i = 0; i < (sizeof(menu.options) / sizeof(menu.options[0]) - 1); i++) {
        if (menu.options[i] == NULL) {
            break;
        }
        Serial.print("\t");
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(menu.options[i]);
    }
}

void displayMenuNavigator() {
    // -----------------------------------------
    //               Description
    //   Display the following message in the
    //   format:
    //  |<< Menu: 1        2/3       Menu: 3>>|
    // -----------------------------------------
    
    int space = (WIDTH - (strlen("|<< Menu: ") + 6 + strlen("Menu: ") + strlen(" >>|"))) / 2;

    Serial.print("|<< Menu: ");
    Serial.print((currentMenu - 1) < 1 ? maxMenu : (currentMenu - 1));
    Serial.print(" ");
    
    for (int i=0; i<space; i++) {
        Serial.print(" ");
    }

    Serial.print(currentMenu);
    Serial.print("/");
    Serial.print(maxMenu);

    for (int i=0; i<space; i++) {
        Serial.print(" ");
    }

    Serial.print("Menu: ");
    Serial.print((currentMenu + 1) > maxMenu ? 1 : (currentMenu + 1));
    Serial.println(" >>|");
}
