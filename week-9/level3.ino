//  _______________________________________________________________
// /  Name: Kyler. V            level 3          Date: 2023-11-12  \
// |                                                               |
// |                          Description                          |
// |                                                               |
// |  This program will allow the user to control the LEDs on the  |
// |               arduino board using an IR remote.               |
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

int currentMenu = 1;
int maxMenu = 3;

// Function prototype
struct Menu {
    const char* title;
    const char* options[3];
    void (*functions[3])();
};
typedef struct Menu Menu;

Menu menus[] = {
    {
        "Menu 1",                               // Title       
        {
            "Blue LED -> ON", 
            "Blue LED -> OFF"
        },
        {
            [] {
                digitalWrite(BLUE_LED, HIGH);
            },
            [] {
                digitalWrite(BLUE_LED, LOW);
            }
        }
    },
    {
        "Menu 2",                               // Title        
        {
            "Red LED -> ON", 
            "Red LED -> OFF"
        },
        {
            [] {
                digitalWrite(RED_LED, HIGH);
            },
            [] {
                digitalWrite(RED_LED, LOW);
            }
        }
    },
    {
        "Menu 3",                               // Title
        {
            "Random RGB color", 
            "Toggle LEDs"
        },
        {
            [] {
                analogWrite(RGB_RED, random(0, 255));
                analogWrite(RGB_GREEN, random(0, 255));
                analogWrite(RGB_BLUE, random(0, 255));
            },
            [] {
                digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
                digitalWrite(RED_LED, !digitalRead(RED_LED));
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


// Menu functions
bool checks() {
    // Check which button was pressed and execute the associated function
    switch (getIRCode()) {
        case 0:
            // Handle "POWER" button
            if (!on) {
                on = !on;
                return true;
            } else {
                return false;
            }

        case 1:
            // Handle "VOL+"
            return false;

        case 2:
            // Handle "FUNC/STOP"
            return false;

        case 4:
            // Handle "SKIP-BACK"
            if (on) {
                menuBack();
                return true;
            } else {
                return false;
            }

        case 5:
            // Handle "PAUSE"
            return false;

        case 6:
            // Handle "SKIP-FORWARD"
            if (on) {
                menuForward();
                return true;
            } else {
                return false;
            }

        case 8:
            // Handle "DOWN"
            return false;

        case 9:
            // Handle "VOL-"
            return false;

        case 10:
            // Handle "UP"
            return false;

        case 12:
            // Handle "0"
            return false;

        case 13:
            // Handle "EQ"
            return false;

        case 14:
            // Handle "ST/REPT"
            return false;

        case 16:
            // Handle "1"
            if (on) {
                menus[currentMenu-1].functions[0]();
                return false;
            } else {
                return false;
            }

        case 17:
            // Handle "2"
            if (on) {
                menus[currentMenu-1].functions[1]();
                return false;
            } else {
                return false;
            }

        case 18:
            // Handle "3"
            if (on) {
                menus[currentMenu-1].functions[2]();
                return false;
            } else {
                return false;
            }

        case 20:
            // Handle "4"
            if (on) {
                menus[currentMenu-1].functions[3]();
                return false;
            } else {
                return false;
            }

        case 21:
            // Handle "5"
            if (on) {
                menus[currentMenu-1].functions[4]();
                return false;
            } else {
                return false;
            }

        case 22:
            // Handle "6"
            if (on) {
                menus[currentMenu-1].functions[5]();
                return false;
            } else {
                return false;
            }

        case 24:
            // Handle "7"
            if (on) {
                menus[currentMenu-1].functions[6]();
                return false;
            } else {
                return false;
            }

        case 25:
            // Handle "8"
            if (on) {
                menus[currentMenu-1].functions[7]();
                return false;
            } else {
                return false;
            }

        case 26:
            // Handle "9"
            if (on) {
                menus[currentMenu-1].functions[8]();
                return false;
            } else {
                return false;
            }

        default:
            // Handle unknown button
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










