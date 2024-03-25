//   ________________________________________________________________________  
//  /  Name: Kyler Visser              level 2             Date: 2023-09-28  \
//  |                                                                        |
//  |                               Description:                             |
//  |                                                                        |
//  |   This program will turn two LEDS on and off depending on the light    |
//  |                                 level.                                 |
//  \________________________________________________________________________/

//  ---------------------------------
//    Initalize vairables and pins.
//  ---------------------------------
int lightPin = A1;
int data = 0;
int red = 12;
int blue = 13;

//  ---------------
//    Setup pins.
//  ---------------
void setup() {
    pinMode(lightPin, INPUT);
    pinMode(red, OUTPUT);
    pinMode(blue, OUTPUT);
    Serial.begin(9600);
}

//  --------------
//    Main loop.
//  --------------
void loop() {
    data = analogRead(lightPin);
    Serial.println(data);
    data = map(data, 6, 679, 0, 100);
    Serial.print("Light level: ");
    Serial.println(data);

    //  -----------------------------------
    //    If the light level is below 25%
    //  -----------------------------------
    if (data < 25) { 
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
    } else {
        digitalWrite(red, LOW);
        digitalWrite(blue, LOW);
    }

}
