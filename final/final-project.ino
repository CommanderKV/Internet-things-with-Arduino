//   ________________________________________________________________________  
//  /  Name: Kyler Visser           Final project          Date: 2023-11-30  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |  This program is a game that uses 3 LED rings and 2 buttons. The goal  |
//  |  of the game is to get all 3 LED rings to have the same color in the   |
//  |  same spot. To do this, the user must press the button when the color  |
//  |   is in the spot they want. If the user wins, the LEDs will flash 5    |
//  |     times. If the user loses, the LEDs will flash 5 times in red.      |
//  \________________________________________________________________________/


// -----------------------------------------
//               Description
//    Include the required libraries and   
//    define the pins that will be used.
// -----------------------------------------
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h> // Address: 0x20

#define CIRCLE_1 4
#define CIRCLE_2 5
#define CIRCLE_3 6
#define BUTTON_1 2
#define BUTTON_2 3

#define LED_COUNT 24


// -----------------------------------------
//               Description
//     Setup vairables that will be used   
//        throughout the program. This      
//     includes the 3 LED rings, the LCD
//     screen, the option selected by the
//     user, the time between each pixel    
//      move, if the pixels are cycling,    
//      the selected pixel, the selected    
//     color, and the colors that will be   
//                   used.                 
// -----------------------------------------
Adafruit_NeoPixel circles[3] = {
    Adafruit_NeoPixel(LED_COUNT, CIRCLE_3, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(LED_COUNT, CIRCLE_2, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(LED_COUNT, CIRCLE_1, NEO_GRB + NEO_KHZ800)
};

LiquidCrystal_I2C lcd(0x20, 16, 2);
int optionSelected = -1;

int timeBetweenMove = 100;
bool circlePixels = false;
int selectedPixel = 0;
int selected[3] = {
    -1, 
    -1, 
    -1
};

int colors[24][4] = {
    {0, 255, 0, 100},
    {0, 245, 8, 105},
    {0, 236, 17, 111},
    {0, 227, 26, 116},
    {0, 218, 35, 121},
    {0, 209, 44, 127},
    {0, 200, 53, 132},
    {0, 191, 62, 137},
    {0, 182, 71, 143},
    {0, 173, 80, 148},
    {0, 164, 89, 153},
    {0, 155, 98, 159},
    {0, 146, 107, 164},
    {0, 137, 116, 169},
    {0, 128, 125, 175},
    {0, 119, 134, 180},
    {0, 110, 143, 185},
    {0, 101, 152, 191},
    {0, 92, 161, 196},
    {0, 83, 170, 201},
    {0, 74, 179, 207},
    {0, 65, 188, 212},
    {0, 56, 197, 217},
    {0, 47, 206, 223}
};

int count = 0;


// -----------------------------------------
//               Description
//   Setup pins, LCDs, interrupts, and the
//   random seed. Then display the welcome
//        message on the LCD screen.        
// -----------------------------------------
void setup() {
    for (int i=0; i<3; i++) {
        circles[i].begin();
        circles[i].show();
        circles[i].setBrightness(50);
    }
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);

    Serial.begin(9600);

    lcd.init();
    lcd.clear();
    lcd.backlight();

    attachInterrupt(digitalPinToInterrupt(BUTTON_1), buttonPressed_1, RISING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_2), buttonPressed_2, RISING);
    randomSeed(analogRead(0));

    intalizeCircles();

    lcd.setCursor(0, 0);
    lcd.print("Welcome to slots!");
    delay(1000);
}



// -----------------------------------------
//               Description
//   The main loop of the program. This is
//   where the user will select what they 
//                want to do.             
// -----------------------------------------
void loop() {

    // 0123456789012345
    //     Options
    lcd.clear();
    lcd.home();
    lcd.setCursor(4, 0);
    lcd.print("Options");

    while (optionSelected == -1) {
        // 0123456789012345
        //     1: Play
        lcd.setCursor(4, 1);
        lcd.print("1: Play");

        delay(2000);

        if (optionSelected != -1) {
            break;
        }

        // 0123456789012345
        //   2: Tutorial
        lcd.setCursor(2, 1);
        lcd.print("2: Tutorial");

        delay(2000);
        lcd.setCursor(0, 1);
        lcd.print("                ");
    
    }

    // Go to the option selected by the user.
    switch (optionSelected) {
        case 1:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Starting game...");
            gameLoop();
            optionSelected = -1;
            break;
        
        case 2:
            tutorial();
            optionSelected = -1;
            break;
    }
}



// -----------------------------------------
//               Description
//      Display the tutorial on the LCD     
//                  screen.                 
// -----------------------------------------
void tutorial() {
    Serial.println("[NOTICE]\tNot implemented.");
    Serial.println("[REASON]\tTinkercad limitations.");
    /*
    // -----------------------------------------
    //               Description
    //   Display the tutorial on the LCD screen.
    // -----------------------------------------
    Serial.println("Tutorial starting.");
    scrollText("Welcome to slots!");
    intalizeCircles();

    circles[0].setPixelColor(0, 255, 0, 0, 100);
    circles[0].show();
    circles[1].setPixelColor(0, 255, 0, 0, 100);
    circles[1].show();
    circles[2].setPixelColor(0, 255, 0, 0, 100);
    circles[2].show();
    // Breaks at "all "
    Serial.println("First text scroll starting.");
    scrollText("The goal of the game is to get all 3 circles to have the RED pixel in the same spot as displayed above.");
    
    Serial.println("Second text scroll starting.");
    scrollText("To do this, you must press the button 1 when the RED pixel is in the spot you want.");
    scrollText("Upon winning the game, the LEDs will flash 5 times as follows.");
    flash();

    Serial.println("Third text scroll starting.");
    scrollText("Upon losing the game, the LEDs will flash 5 times as follows.");
    reset();

    scrollText("After each game, the LEDs will reset to the starting position.");
    scrollText("To play again you will need to navigate the menu again.");
    scrollText("Have fun!");
    delay(1000);
    */
}



// -----------------------------------------
//               Description
//            Button functions.
// -----------------------------------------
void buttonPressed_1() {
    // -----------------------------------------
    //               Description
    //   When the button is pressed, stop the
    //   current circle from cycling and save
    //   the current pixel that it is selected.
    // -----------------------------------------
    if (circlePixels) {
        for (int circle=0; circle<3; circle++) {
            if (selected[circle] == -1) {
                selected[circle] = selectedPixel;
                break;
            }
        }

    } else if (optionSelected == -1) {
        optionSelected = 1;
    }
}

void buttonPressed_2() {
    // -----------------------------------------
    //               Description
    //   When the button is pressed, stop the
    //   current circle from cycling and save
    //   the current pixel that it is selected.
    // -----------------------------------------
    if (optionSelected == -1) {
        optionSelected = 2;

    } else if (circlePixels) {
        for (int circle=0; circle<3; circle++) {
            if (selected[circle] == -1) {
                selected[circle] = selectedPixel;
                break;
            }
        }
    }
}



// -----------------------------------------
//               Description
//             Game functions.
// -----------------------------------------
void gameLoop() {
    // -----------------------------------------
    //               Description
    //         Run a single game loop.
    // -----------------------------------------

    // Get the user to select a color using a button.
    select();

    // Check if the user won.
    if (checkWin()) {
        // If the user won, flash the LEDs.
        for (int circle=0; circle<3; circle++) {
            for (int pixel=0; pixel<circles[circle].numPixels(); pixel++) {
                circles[circle].setPixelColor(
                    pixel, 
                    0,
                    255,
                    0,
                    0
                );
            }
        }
        flash();
        for (int i=0; i<3; i++) {
            selected[i] = -1;
        }
    } else {
        // If the user did not win, reset the game.
        reset();
    }
}

void select () {
    // -----------------------------------------
    //               Description
    //   Cycle through which color is selected
    //     untill the button is pressed then
    //      dont cycle that circle anymore.
    // -----------------------------------------
    circlePixels = true;
    selectedPixel = random(0, 24);
    long lastMove = millis();
    while (circlePixels) {
        // Add a delay between each pixel change
        if (millis() - lastMove >= timeBetweenMove) {
            // Increment the selected pixel
            selectedPixel++;
            if (selectedPixel > 23) {
                selectedPixel = 0;
            }

            // Go over each circle
            for (int circle=0; circle<3; circle++) {
                if (selected[circle] == -1) {
                    // Set the current pixel
                    circles[circle].setPixelColor(
                        selectedPixel, 
                        255,
                        0,
                        0,
                        100
                    );

                    // Reset the previous pixel
                    if (selectedPixel == 0) {
                        circles[circle].setPixelColor(
                            23, 
                            colors[23][0],
                            colors[23][1],
                            colors[23][2],
                            colors[23][3]
                        );

                    } else {
                        circles[circle].setPixelColor(
                            selectedPixel-1,
                            colors[selectedPixel-1][0],
                            colors[selectedPixel-1][1],
                            colors[selectedPixel-1][2],
                            colors[selectedPixel-1][3]
                        );
                    }

                    // Display the circle
                    circles[circle].show();
                } 
            }

            // Record the lastMove of the pixel
            lastMove = millis();
        }

        // If the last circle has been selected, stop cycling
        if (selected[2] != -1) {
            circlePixels = false;
            delay(1000);
        }
    }
}

bool checkWin() {
    // -----------------------------------------
    //               Description
    //     Check if the user won the game by
    //    checking if all the selected colors
    //              are the same.
    // -----------------------------------------
    int winCondition = selected[0];
    for (int circle=0; circle<3; circle++) {
        if (selected[circle] != winCondition) {
            return false;
        }
    }
    return true;
}

void flash() {
    // -----------------------------------------
    //               Description
    //    Flash the LEDs to indicate that the
    //   user won the game. Flash 5 times with
    //     a 250ms delay between each flash.
    // -----------------------------------------
    int spacing = 250;
    for (int i=0; i<5; i++) {
        for (int circle=0; circle<3; circle++) {
            circles[circle].setBrightness(255);
            circles[circle].show();
        }

        delay(spacing);

        for (int circle=0; circle<3; circle++) {
            circles[circle].setBrightness(1);
            circles[circle].show();
        }

        delay(spacing);
    }

    intalizeCircles();
}

void reset() {
    // -----------------------------------------
    //               Description
    //   Reset the game by setting all the LEDs
    //   to red and reseting the selected array
    //   to -1. Then flash the LEDs to indicate
    //       that the game has been reset.
    // -----------------------------------------
    for (int pixel=0; pixel<24; pixel++) {
        for (int circle=0; circle<3; circle++) {
            circles[circle].setPixelColor(
                pixel,
                255,
                0,
                0,
                0
            );
        }
    }

    for (int circle=0; circle<3; circle++) {
        selected[circle] = -1;
        circles[circle].show();
    }

    flash();
}



// -----------------------------------------
//               Description
//            Helper functions.
// -----------------------------------------

char** makeSegement(char* text) {
    // -----------------------------------------
    //               Description
    //   Segment the text into parts of up to
    //    16 characters without splitting any   
    //     words. The returned array must be    
    //             freed after use.            
    // -----------------------------------------
    int segmentCount = 0;

    // Allocate memory for segments
    char** segements = (char**) malloc(sizeof(char*));
    char* word = strtok(text, " ");
    String segment = "";
    
    // Loop through all words in the text
    while (word != NULL) {
        // If adding the next word to the current segment would make it longer than 16 characters
        if (segment.length() + strlen(word) > 16) {

            // Add the current segment to the segments array
            segements[segmentCount] = strdup(segment.c_str());
            segmentCount++;

            // Reallocate memory for the segments array to accommodate the new segment
            segements = (char**)realloc(segements, (segmentCount + 1) * sizeof(char*));

            segment = "";
        }

        // If the segment is not empty, add a space before the next word
        if (!(segment.length() == 0)) {
            segment += " ";
        }

        // Add the next word to the segment and get the next word
        segment += word;
        word = strtok(NULL, " ");
    }

    // If the last segment is not empty
    if (!(segment.length() == 0)) {
        // Add the last segment to the segments array
        segements[segmentCount] = strdup(segment.c_str());
        segmentCount++;
    }

    count = segmentCount;

    return segements;
}

void scrollText(char* text) {
    // -----------------------------------------
    //               Description
    //   Scroll the text across the LCD screen
    //   by segmenting the text into parts of
    //   up to 16 characters without splitting
    //   any words. The text will scroll across
    //   the screen with a 500ms delay between
    //              each segment.              
    // -----------------------------------------
    count = 0;
    char** displays = makeSegement(text);

    for (int i=0; i < count; i++) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(displays[i]);
        delay(500);
    }

    for (int i=0; i < count; i++) {
        free(displays[i]);
    }
    free(displays);

    delete[] displays;
}

char* subStr(char* source, int start, int end) {
    // -----------------------------------------
    //               Description
    //   Get a substring of a string. The start
    //   and end are inclusive. The returned
    //   string must be freed after use.
    // -----------------------------------------
    char* dest = (char*) malloc(sizeof(char) * (end-start+1));
    for (int i=start; i<=end; i++) {
        dest[i-start] = source[i];
    }
    dest[end-start+1] = '\0';
    return dest;
}

void intalizeCircles() {
    // -----------------------------------------
    //               Description
    //   Set the color of each pixel in each
    //   circle to the color that is stored in
    //             the colors array.
    // -----------------------------------------
    for (int circle=0; circle<3; circle++) {
        for (int pixel=0; pixel<circles[circle].numPixels(); pixel++) {
            circles[circle].setPixelColor(
                pixel, 
                colors[pixel][0], 
                colors[pixel][1], 
                colors[pixel][2], 
                colors[pixel][3]
            );
        }
        circles[circle].show();
        circles[circle].setBrightness(50);
        delay(100);
    }
}

