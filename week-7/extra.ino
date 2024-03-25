//   ________________________________________________________________________  
//  /  Name: Kyler Visser               Extra              Date: 2023-10-24  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |  This program will play a song and the user must guess the song. If    |
//  |  they guess the correct answer then the user should press the button   |
//  |   once the button is pressed then the program will stop playing the    |
//  |   current song and switch to the next song in the list. If the user    |
//  |  doesnt press the button then the program will stop playing the song   |
//  |  after 10 seconds. After all songs have been played the program will   |
//  |  then display the users score and tell them how well they did. After   |
//  |             10 seconds the songs will start playing again.             |
//  \________________________________________________________________________/


/*************************************************
 * Public Constants
 *************************************************/
#define REST        0   // Custom note for rest
#define NOTE_B0     31
#define NOTE_C1     33
#define NOTE_CS1    35
#define NOTE_D1     37
#define NOTE_DS1    39
#define NOTE_E1     41
#define NOTE_F1     44
#define NOTE_FS1    46
#define NOTE_G1     49
#define NOTE_GS1    52
#define NOTE_A1     55
#define NOTE_AS1    58
#define NOTE_B1     62
#define NOTE_C2     65
#define NOTE_CS2    69
#define NOTE_D2     73
#define NOTE_DS2    78
#define NOTE_E2     82
#define NOTE_F2     87
#define NOTE_FS2    93
#define NOTE_G2     98
#define NOTE_GS2    104
#define NOTE_A2     110
#define NOTE_AS2    117
#define NOTE_B2     123
#define NOTE_C3     131
#define NOTE_CS3    139
#define NOTE_D3     147
#define NOTE_DS3    156
#define NOTE_E3     165
#define NOTE_F3     175
#define NOTE_FS3    185
#define NOTE_G3     196
#define NOTE_GS3    208
#define NOTE_A3     220
#define NOTE_AS3    233
#define NOTE_B3     247
#define NOTE_C4     262
#define NOTE_CS4    277
#define NOTE_D4     294
#define NOTE_DS4    311
#define NOTE_E4     330
#define NOTE_F4     349
#define NOTE_FS4    370
#define NOTE_G4     392
#define NOTE_GS4    415
#define NOTE_A4     440
#define NOTE_AS4    466
#define NOTE_B4     494
#define NOTE_C5     523
#define NOTE_CS5    554
#define NOTE_D5     587
#define NOTE_DS5    622
#define NOTE_E5     659
#define NOTE_F5     698
#define NOTE_FS5    740
#define NOTE_G5     784
#define NOTE_GS5    831
#define NOTE_A5     880
#define NOTE_AS5    932
#define NOTE_B5     988
#define NOTE_C6     1047
#define NOTE_CS6    1109
#define NOTE_D6     1175
#define NOTE_DS6    1245
#define NOTE_E6     1319
#define NOTE_F6     1397
#define NOTE_FS6    1480
#define NOTE_G6     1568
#define NOTE_GS6    1661
#define NOTE_A6     1760
#define NOTE_AS6    1865
#define NOTE_B6     1976
#define NOTE_C7     2093
#define NOTE_CS7    2217
#define NOTE_D7     2349
#define NOTE_DS7    2489
#define NOTE_E7     2637
#define NOTE_F7     2794
#define NOTE_FS7    2960
#define NOTE_G7     3136
#define NOTE_GS7    3322
#define NOTE_A7     3520
#define NOTE_AS7    3729
#define NOTE_B7     3951
#define NOTE_C8     4186
#define NOTE_CS8    4435
#define NOTE_D8     4699
#define NOTE_DS8    4978


//  ------------------------------
//    Define vairables and pins.
//  ------------------------------
int buzzerPin = 5;
int button1Pin = 2;

int rgbRedPin = 9;
int rgbGreenPin = 11;
int rgbBluePin = 10;

int tempo = 144;
int wholeNote = (60000 * 4) / tempo;
bool continuePlaying = true;

int counter = 0;
int maxTime = 10000;
float totalTime = 0;
long int roundStart = 0;
bool infoDisplayed = false;

//  ------------------------------
//     Setup pins, serial, and 
//            inturupts.
//  ------------------------------
void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(button1Pin, INPUT);
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(button1Pin), togglePlay, RISING);
}

//  ------------------------------
//    Main loop
//  ------------------------------
void loop() {
    runGame();
}

//  ------------------------------
//    Toggle the song playing 
//       with an inturupt.
//  ------------------------------
void togglePlay() {
    if (continuePlaying) {
        continuePlaying = !continuePlaying;
        totalTime += 10 - ((millis() - roundStart) / 1000);
    }
}

//  ------------------------------
//    Main game loop.
//  ------------------------------
void runGame() {
    // If we need to display info then do so.
    if (!infoDisplayed) {
        // If we are just starting the game then display
        // the starting info.
        if (counter == 0) {
            Serial.println("-----------------------------------");
            Serial.println("---------- Starting Game ----------");
            Serial.println("-----------------------------------");
            Serial.println();
            Serial.println("You must guess 5 songs!");
            Serial.println("Your score WILL be told to you at ");
            Serial.println("the end of guessing.");
            Serial.println();

            for (int i=3; i!=0; i--) {
                Serial.print("[COUNTDOWN] ");
                Serial.println(i);
                delay(1000);
            }
            counter = 1;
            infoDisplayed = true;

        // Display ending info.
        } else {
            Serial.println("------------------------------------");
            Serial.println("         Congratulations!!!");
            Serial.print("  Your point total came to ");
            Serial.print(totalTime);
            Serial.println("/50 pts.");
            if (totalTime < 20) {
                Serial.println("  You are a musical genius!");
            } else if (totalTime < 30) {
                Serial.println("");
            } else {
                Serial.println("  You need to listen to more music!");
            }
            Serial.println("------------------------------------");
            Serial.println("[NOTICE] Restarting game in 10 seconds...");
            delay(10000);
            totalTime = 0;
            counter = 0;
            infoDisplayed = true;
        }
    
    // If the game is running.
    } else {
        // Game loop var adjustments
        continuePlaying = true;
        counter++;

        // If we are on the last song then stop the game.
        if (counter == 5) {
            infoDisplayed = false;
        }
    }

    // Play the song
    if (counter != 0 && counter <= 5){
        roundStart = millis();
        switch (counter) {
            case 1:
                song1();
                break;
            case 2:
                song2();
                break;
            case 3:
                song3();
                break;
            case 4:
                song4();
                break;
            case 5:
                song5();
                break;
        }
        
        // If they were not able to guess the song in time
        // then display the message and add points.
        if (!continuePlaying) {
            Serial.print("[NOTICE] Congrats!! You got it in ");
            Serial.print((millis() - roundStart) / 1000);
            Serial.println(" seconds, well done.");
            Serial.print("[POINTS] Adding ");
            Serial.print(10 - ((millis() - roundStart) / 1000));
            Serial.println(" points...");
        }
    }
}

//  ------------------------------
//    Song 1: 
//        Mary had a little lamb
//  ------------------------------
void song1() {
    tempo = 120;
    wholeNote = (60000 * 4) / tempo;

    int notes[][2] = {
        {NOTE_E4, 200},     {NOTE_D4, 200},     {NOTE_C4, 200},     {NOTE_D4, 200},     {NOTE_E4, 900},   
        {NOTE_D4, 800},     {NOTE_E4, 200},     {NOTE_G4, 600},     {NOTE_E4, 200},     {NOTE_D4, 200}, 
        {NOTE_C4, 200},     {NOTE_D4, 200},     {NOTE_E4, 800},     {NOTE_D4, 400},     {NOTE_E4, 200},
        {NOTE_D4, 200},     {NOTE_C4, 200},
        {REST,    300},
        {NOTE_E4, 200},     {NOTE_D4, 200},     {NOTE_C4, 200},     {NOTE_D4, 200},     {NOTE_E4, 900},   
        {NOTE_D4, 800},     {NOTE_E4, 200},     {NOTE_G4, 600},     {NOTE_E4, 200},
    };

    playSong(notes, 26, false);
}

//  ------------------------------
//    Song 2:
//        Harry Potter
//  ------------------------------
void song2() {
    tempo = 144;
    wholeNote = (60000 * 4) / tempo;

    int harryPotter[][2] = {
        {REST,       2},       {NOTE_D4,    4},
        {NOTE_G4,    -4},      {NOTE_AS4,   8},     {NOTE_A4,    4},
        {NOTE_G4,    2},       {NOTE_D5,    4},
        {NOTE_C5,    -2}, 
        {NOTE_A4,    -2},
        {NOTE_G4,    -4},      {NOTE_AS4,   8},     {NOTE_A4,    4},
        {NOTE_F4,    2},       {NOTE_GS4,   4},
        {NOTE_D4,    -1}, 
        {NOTE_D4,    4},

        {NOTE_G4,    -4},      {NOTE_AS4,   8},     {NOTE_A4,    4},
        {NOTE_G4,    2},       {NOTE_D5,    4},
        {NOTE_F5,    2},       {NOTE_E5,    4},
        {NOTE_DS5,   2},       {NOTE_B4,    4},
        {NOTE_DS5,   -4},      {NOTE_D5,    8},     {NOTE_CS5,   4},
        {NOTE_CS4,   2},       {NOTE_B4,    4},
        {NOTE_G4,    -1},
        {NOTE_AS4,   4},

        {NOTE_D5,    2},       {NOTE_AS4,   4},
        {NOTE_D5,    2},       {NOTE_AS4,   4},
        {NOTE_DS5,   2},       {NOTE_D5,    4},
        {NOTE_CS5,   2},       {NOTE_A4,    4},
        {NOTE_AS4,   -4},      {NOTE_D5,    8},     {NOTE_CS5,   4},
        {NOTE_CS4,   2},       {NOTE_D4,    4},
        {NOTE_D5,    -1}, 
        {REST,       4},       {NOTE_AS4,   4},  
    };

    playSong(harryPotter, 48, true);
}

//  ------------------------------
//    Song 3:
//        Star Wars
//  ------------------------------
void song3() {
    tempo = 108;
    wholeNote = (60000 * 4) / tempo;

    int starWars[][2] = {
        {NOTE_AS4, 8},  {NOTE_AS4, 8},  {NOTE_AS4, 8},
        {NOTE_F5, 2},   {NOTE_C6, 2},
        {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F6, 2},   {NOTE_C6, 4},
        {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F6, 2},   {NOTE_C6, 4},
        {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_AS5, 8},  {NOTE_G5, 2},   {NOTE_C5, 8},   {NOTE_C5, 8},   {NOTE_C5, 8},
        {NOTE_F5, 2},   {NOTE_C6, 2},
        {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F6, 2},   {NOTE_C6, 4},
        
        {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F6, 2},   {NOTE_C6, 4},
        {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_AS5, 8},  {NOTE_G5, 2},   {NOTE_C5, -8},  {NOTE_C5, 16},
        {NOTE_D5, -4},  {NOTE_D5, 8},   {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F5, 8},
        {NOTE_F5, 8},   {NOTE_G5, 8},   {NOTE_A5, 8},   {NOTE_G5, 4},   {NOTE_D5, 8},   {NOTE_E5, 4},   {NOTE_C5, -8},  {NOTE_C5, 16},
        {NOTE_D5, -4},  {NOTE_D5, 8},   {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F5, 8},
        

    };

    playSong(starWars, 60, true);
}

//  ------------------------------
//    Song 4:
//        Pink Panther
//  ------------------------------
void song4() {
    tempo = 120;
    wholeNote = (60000 * 4) / tempo;

    int pinkPanther[][2] = {
        {REST,      2},     {REST,       4},    {REST,      8},     {NOTE_DS4,   8}, 
        {NOTE_E4,   -4},    {REST,       8},    {NOTE_FS4,  8},     {NOTE_G4,    -4},   {REST,      8},     {NOTE_DS4,  8},
        {NOTE_E4,   -8},    {NOTE_FS4,   8},    {NOTE_G4,   -8},    {NOTE_C5,    8},    {NOTE_B4,   -8},    {NOTE_E4,   8},     {NOTE_G4,   -8},    {NOTE_B4,   8},   
        {NOTE_AS4,  2},     {NOTE_A4,    -16},  {NOTE_G4,   -16},   {NOTE_E4,    -16},  {NOTE_D4,   -16}, 
        {NOTE_E4,   2},     {REST,       4},    {REST,      8},     {NOTE_DS4,   4},

        {NOTE_E4,   -4},    {REST,       8},    {NOTE_FS4,  8},     {NOTE_G4,    -4},   {REST,      8},     {NOTE_DS4,  8},
        {NOTE_E4,   -8},    {NOTE_FS4,   8},    {NOTE_G4,   -8},    {NOTE_C5,    8},    {NOTE_B4,   -8},    {NOTE_G4,   8},     {NOTE_B4,   -8},    {NOTE_E5,   8},
        {NOTE_DS5,  1},
        {NOTE_D5,   2},     {REST,       4},    {REST,      8},     {NOTE_DS4,   8}, 
        {NOTE_E4,   -4},    {REST,       8},    {NOTE_FS4,  8},     {NOTE_G4,    -4},   {REST,      8},     {NOTE_DS4,  8},
        {NOTE_E4,   -8},    {NOTE_FS4,   8},    {NOTE_G4,   -8},    {NOTE_C5,    8},    {NOTE_B4,   -8},    {NOTE_E4,   8},     {NOTE_G4,   -8},    {NOTE_B4,   8},   
        

    };

    playSong(pinkPanther, 60, true);
}

//  ------------------------------
//    Song 5:
//        Happy Birthday
//  ------------------------------
void song5() {
    tempo = 140;
    wholeNote = (60000 * 4) / tempo;
    
    int happyBirthday[][2] = {
        {NOTE_C4,   4},     {NOTE_C4,   8}, 
        {NOTE_D4,   -4},    {NOTE_C4,   -4},    {NOTE_F4,   -4},
        {NOTE_E4,   -2},    {NOTE_C4,   4},     {NOTE_C4,   8}, 
        {NOTE_D4,   -4},    {NOTE_C4,   -4},    {NOTE_G4,   -4},
        {NOTE_F4,   -2},    {NOTE_C4,   4},     {NOTE_C4,   8},

        {NOTE_C5,   -4},    {NOTE_A4,   -4},    {NOTE_F4,   -4}, 
        {NOTE_E4,   -4},    {NOTE_D4,   -4},    {NOTE_AS4,  4},     {NOTE_AS4,  8},
        {NOTE_A4,   -4},    {NOTE_F4,   -4},    {NOTE_G4,   -4},
        {NOTE_F4,   -2},
    };

    playSong(happyBirthday, 25, true);
}


//  ------------------------------
//    Play the song based on the
//           input array.
//  ------------------------------
void playSong(int song[][2], int length, bool special) {
    bool cleanExit = true;

    // If we ahave an array with
    // the length already in it.
    if (!special) {
        long int startTime = millis();
        // Go through each note and play it.
        for (int i = 0; i < length; i++) {
            // If we are over 10 seconds then stop playing.
            if (millis() - startTime >= maxTime) {break;}
            // If we have guessed the song correctly stop playing.
            if (continuePlaying) {
                tone(buzzerPin, song[i][0], song[i][1]);
                delay(song[i][1]);
                noTone(buzzerPin);
            } else {
                cleanExit = false;
                break;
            }
        }
    } else {
        // Apply modifications to the duration of the
        // song based on input in the array. Also get
        // the length of the array at the same time
        int count = 0;
        for (int i=0; i< (length!=0 ? length: 1000); i++) { // Unable to find better way to get length of array
            if (song[i][1] < 0) {
                song[i][1] = wholeNote / abs(song[i][1]);
                song[i][1] *= 1.5;
            } else {
                song[i][1] = wholeNote / song[i][1];
            }
            count++;
        }

        long int startTime = millis();
        for (int i=0; i < count; i++) {
            // Check if we need to stop playing because of time limit
            // or because of button press.
            if (millis() - startTime >= maxTime) {break;}
            if (continuePlaying) {
                tone(buzzerPin, song[i][0], song[i][1]*0.9);
                delay(song[i][1]);
                noTone(buzzerPin);
            } else {
                cleanExit = false;
                break;
            }
        }
    }


    // If we did not guess the song in time then display
    // to the user that no one got it in time.
    if (cleanExit) {
        Serial.println("[NOTICE] No one got it in time.");

    }
}