//   ________________________________________________________________________  
//  /  Name: Kyler Visser              level 3             Date: 2023-09-28  \
//  |                                                                        |
//  |                              Description                               |
//  |                                                                        |
//  |   This program will take the red light and turn it on when the light   |
//  |  is above 50%, the blue light will turn on when the light is between   |
//  |  30% and 60%, and the green light will turn on when the light is below |
//  |  33% or above 66%. The green light will blink slowly when the light is |
//  |           below 33% and quickly when the light is above 66%.           |
//  \________________________________________________________________________/

//  ---------------------------------
//    Initalize vairables and pins.
//  ---------------------------------
int lightPin = A1;
int data = 0;
int red = 12;
int blue = 13;
int green = 11;
int lastFire = 0;

//  --------------------------
//    Setup pins and serial.
//  --------------------------
void setup() {
    pinMode(lightPin, INPUT);
    pinMode(red, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(green, OUTPUT);

    Serial.begin(9600);
}

//  --------------
//    Main loop.
//  --------------
void loop() {
    data = analogRead(lightPin);
    data = map(data, 6, 679, 0, 100);
    Serial.print("Light level: ");
    Serial.println(data);

    //  -------------------------------
    //    If the light level is above
    //    50%, turn on the red light.
    //  -------------------------------
    if (data > 50) {
        digitalWrite(red, HIGH);
    } else {
        digitalWrite(red, LOW);
    }
    
    //  ----------------------------------
    //    If the light level is between
    //    30% and 60%, turn on the blue.
    //  ----------------------------------
    if (data >30 && data < 60) {
        digitalWrite(blue, HIGH);
    } else {
        digitalWrite(blue, LOW);
    } 

    //  -------------------------------
    //    If the light level is below
    //      33% or above 66%, blink
    //         the green light.
    //  -------------------------------
    if (data < 33) {
        if (millis() - lastFire > 350) {
            digitalWrite(green, HIGH);
            lastFire = millis();
        } else {
            digitalWrite(green, LOW);
        }

    } else if (data > 66) {
        if (millis() - lastFire > 150) {
            digitalWrite(green, HIGH);
            lastFire = millis();
        } else {
            digitalWrite(green, LOW);
        }
        
    } else {
        digitalWrite(green, LOW);
    }

}
