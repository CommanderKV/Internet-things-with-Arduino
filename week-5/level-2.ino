int blueLedPin = 13;
int redLedPin = 12;
int button1Pin = 2;
int button2Pin = 3;


void setup() {
    pinMode(blueLedPin, OUTPUT);
    pinMode(button1Pin, INPUT);
}

void loop() {
    if (digitalRead(button1Pin) == HIGH) {
        digitalWrite(blueLedPin, HIGH);
    } else {
		digitalWrite(blueLedPin, LOW);
	}

    if (digitalRead(button2Pin) == HIGH) {
        digitalWrite(redLedPin, HIGH);
    } else {
		digitalWrite(redLedPin, LOW);
	}
}
