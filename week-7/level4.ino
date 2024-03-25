//   ________________________________________________________________________  
//  /  Name: Kyler Visser              Level 4             Date: 2023-10-29  \
//  |                                                                        |
//  |                                Description                             |
//  |                                                                        |
//  |   This program will play a song from a list of songs. The user will    |
//  |    need to select the song they want to play from a list of songs.     |
//  \________________________________________________________________________/

/*************************************************
 * Public Constants
 *************************************************/
#define REST 0 // Custom note for rest
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978


//  -----------------------
//    Initalize vairables
//  -----------------------
int buzzerPin = 5;
int button1Pin = 2;

int rgbRedPin = 9;
int rgbGreenPin = 11;
int rgbBluePin = 10;

bool play = true;


int tempo = 144;
int wholenote = (60000 * 4) / tempo;

//  -------------------------
//    Setup pins and serial
//  -------------------------
void setup() {
    pinMode(buzzerPin, OUTPUT);
    pinMode(button1Pin, INPUT);
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(button1Pin), stop, RISING);
}

//  -------------
//    Main loop
//  -------------
void loop() {
    runMenu();
}


//  -------------------
//    Button inturupt
//  -------------------
void stop() {
    play = false;
}

//  -----------------------
//    Main menu for songs
//  -----------------------
void runMenu() {
    /*
    ---------- Main Menu ----------
      Songs:
        1. Mary had a little lamb
        2. Harry Potter
        3. Star Wars
    -------------------------------
    */  
    Serial.println("---------- Main Menu ----------");
    Serial.println("  Songs:");
    Serial.println("    1. Mary had a little lamb");
    Serial.println("    2. Harry Potter");
    Serial.println("    3. Star Wars");
    Serial.println("-------------------------------");
    Serial.println();
    Serial.print("Enter song selection: ");

    //  ---------------------------
    //    Get user input for song 
    //           selection
    //  ---------------------------
    while (Serial.available() == 0) {}
    int songSelection = Serial.parseInt();
    Serial.println(songSelection);

    //  -------------------
    //    Select the song
    //  -------------------
    switch (songSelection) {
        case 1:
            play = true;
            song1();
            break;
        case 2:
            play = true;
            song2();
            break;
        case 3:
            play = true;
            song3();
            break;
        default:
            Serial.println("Invalid selection");
            break;
    }
    Serial.println();
}

void song1() {
    //  ------------------------------
    //    Marry had a little lamb
    //  ------------------------------
    int notes[][2] = {
        {NOTE_E4, 200},
        {NOTE_D4, 200},
        {NOTE_C4, 200},
        {NOTE_D4, 200},
        {NOTE_E4, 900},
        {NOTE_D4, 800},
        {NOTE_E4, 200},
        {NOTE_G4, 600},
        {NOTE_E4, 200},
        {NOTE_D4, 200},
        {NOTE_C4, 200},
        {NOTE_D4, 200},
        {NOTE_E4, 800},
        {NOTE_D4, 400},
        {NOTE_E4, 200},
        {NOTE_D4, 200},
        {NOTE_C4, 200}
    };
    playSong(notes, 17, false);
}

void song2() {
    //  ----------------
    //    Harry potter
    //  ----------------
    int tempo = 144;
    int wholenote = (60000 * 4) / tempo;

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

        {NOTE_D5,    2},       {NOTE_AS4,   4},
        {NOTE_D5,    2},       {NOTE_AS4,   4},
        {NOTE_F5,    2},       {NOTE_E5,    4},
        {NOTE_DS5,   2},       {NOTE_B4,    4},
        {NOTE_DS5,   -4},      {NOTE_D5,    8},     {NOTE_CS5, 4},
        {NOTE_CS4,   2},       {NOTE_AS4,   4},
        {NOTE_G4,    -1}
    };

    playSong(harryPotter, 62, true);
}

void song3() {
    //  -------------
    //    Star wars
    //  -------------
    int tempo = 144;
    int wholenote = (60000 * 4) / tempo;

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
        
        {NOTE_C6, -8},  {NOTE_G5, 16},  {NOTE_G5, 2},   {REST, 8},      {NOTE_C5, 8},
        {NOTE_D5, -4},  {NOTE_D5, 8},   {NOTE_AS5, 8},  {NOTE_A5, 8},   {NOTE_G5, 8},   {NOTE_F5, 8},
        {NOTE_F5, 8},   {NOTE_G5, 8},   {NOTE_A5, 8},   {NOTE_G5, 4},   {NOTE_D5, 8},   {NOTE_E5, 4},   {NOTE_C6, -8},  {NOTE_C6, 16},
        {NOTE_F6, 4},   {NOTE_DS6, 8},  {NOTE_CS6, 4},  {NOTE_C6, 8},   {NOTE_AS5, 4},  {NOTE_GS5, 8},  {NOTE_G5, 4},   {NOTE_F5, 8},
        {NOTE_C6, 1}
    };

    playSong(starWars, 88, true);
}

void song4() {
    //  ----------------
    //    Pink panther
    //  ----------------
    int tempo = 120;
    int wholenote = (60000 * 4) / tempo;

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
        
        {NOTE_AS4,  2},     {NOTE_A4,    -16},  {NOTE_G4,   -16},   {NOTE_E4,    -16},  {NOTE_D4,   -16}, 
        {NOTE_E4,   -4},    {REST,       4},
        {REST,      4},     {NOTE_E5,    -8},   {NOTE_D5,   8},     {NOTE_B4,    -8},   {NOTE_A4,   8},     {NOTE_G4,   -8},    {NOTE_E4,   -8},
        {NOTE_AS4,  16},    {NOTE_A4,    -8},   {NOTE_AS4,  16},    {NOTE_A4,    -8},   {NOTE_AS4,  16},    {NOTE_A4,   -8},    {NOTE_AS4,  16},    {NOTE_A4,   -8},   
        {NOTE_G4,   -16},   {NOTE_E4,    -16},  {NOTE_D4,   -16},   {NOTE_E4,    16},   {NOTE_E4,   16},    {NOTE_E4,   2},
    
    };

    playSong(pinkPanther, 88, true);
}



//  --------------------------
//    Play the song from the
//            array
//  --------------------------
void playSong(int song[][2], int length, bool special) {
    if (!special) {
        for (int i = 0; i < length; i++) {
            if (play) {
                tone(buzzerPin, song[i][0], song[i][1]);
                delay(song[i][1]);
                noTone(buzzerPin);
            } else {
                return;
            }
        }
        noTone(buzzerPin);

    } else {
        //  ------------------------------
        //    Setup duration and produce
        //             the notes
        //  ------------------------------
        int count = 0;
        for (int i=0; i< (length!=0 ? length: 1000); i++) { // Unable to find bettwe way to get length of array
            if (song[i][1] < 0) {
                song[i][1] = wholenote / abs(song[i][1]);
                song[i][1] *= 1.5;
            } else {
                song[i][1] = wholenote / song[i][1];
            }

            if (song[i][1] == 0) {
                Serial.println(i);
                break;
            }
            count++;
        }

        for (int i=0; i < count; i++) {
            if (play) {
                tone(buzzerPin, song[i][0], song[i][1]*0.9);
                delay(song[i][1]);
                noTone(buzzerPin);
            } else {
                return;
            }
        }
    }
}