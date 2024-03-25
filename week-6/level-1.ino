/*
Title:Experiment #006 - RGB Fade
Description: This program will fade the Red, Green, Blue(RGB) LED Instructions: The
RGB LED is connected to a Pulse Width Modulation(PWM) pin.
You can use analogWrite to control brightness.
*/
int RGBRedPin = 9;    // The red RGB LED is connected pin 9 of the Arduino.
int RGBGreenPin = 10; // The green RGB LED is connected pin 10 of the Arduino.
int RGBBluePin = 11;  // The blue RGB LED is connected pin 11 of the Arduino.
int fadeDelay = 5;    // This is the number of milliseconds that it will take between steps
void setup()
{                                 // The Setup function runs once.
    pinMode(RGBRedPin, OUTPUT);   // Setup red RGB LED pin as an output pin.
    pinMode(RGBGreenPin, OUTPUT); // Setup green RGB LED pin as an output pin.
    pinMode(RGBBluePin, OUTPUT);  // Setup blue RGB LED pin as an output pin.
}
void loop()
{ // The loop function runs forever.
    for (int x = 0; x <= 255; x++)
    { // Fade in red.
        analogWrite(RGBRedPin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out red.
        analogWrite(RGBRedPin, x);
        delay(fadeDelay);
    }
    for (int x = 0; x <= 255; x++)
    { // Fade in green.
        analogWrite(RGBGreenPin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out green.
        analogWrite(RGBGreenPin, x);
        delay(fadeDelay);
    }
    for (int x = 0; x <= 255; x++)
    { // Fade in blue.
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out blue.
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 0; x <= 255; x++)
    { // Fade in red and blue.
        analogWrite(RGBRedPin, x);
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out red and blue.
        analogWrite(RGBRedPin, x);
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 0; x <= 255; x++)
    { // Fade in red and green.
        analogWrite(RGBRedPin, x);
        analogWrite(RGBGreenPin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out red and green.
        analogWrite(RGBRedPin, x);
        analogWrite(RGBGreenPin, x);
        delay(fadeDelay);
    }
    for (int x = 0; x <= 255; x++)
    { // Fade in green and blue.
        analogWrite(RGBGreenPin, x);
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out green and blue.
        analogWrite(RGBGreenPin, x);
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 0; x <= 255; x++)
    { // Fade in red, green and blue.
        analogWrite(RGBRedPin, x);
        analogWrite(RGBGreenPin, x);
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
    for (int x = 255; x >= 0; x--)
    { // Fade out red, green and blue.
        analogWrite(RGBRedPin, x);
        analogWrite(RGBGreenPin, x);
        analogWrite(RGBBluePin, x);
        delay(fadeDelay);
    }
}