#include <SmartMatrix_32x32.h>
#include <MatrixFontCommon.h>
#include <SimpleTimer.h>
#include "Animations.h"

#include "bitmaps/colorwheel.c"

SimpleTimer timer(1);
Animations controller(&timer);


const int ledPin = 13;
const int buttonPin = 18;
const int potPin = 17;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
char buffer[20];

void checkButtonPress(int timerId) {
    // read the pushbutton input pin:
    buttonState = digitalRead(buttonPin);

    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
        // if the state has changed, increment the counter
        if (buttonState == LOW) {
            // if the current state is HIGH then the button
            // wend from off to on:
            buttonPushCounter++;
            controller.nextAnimation();
        }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
}

void showAnimation(int timerId) {
    controller.showCurrentAnimation();
}
void nextAnimation(int timerId) {
    controller.nextAnimation();
}
void checkBrightness(int timerId) {
    controller.currentBrightness = analogRead(potPin) / 4;
    controller.matrix.setBrightness(controller.currentBrightness);
}




// the setup() method runs once, when the sketch starts
void setup() {
    // initialize the digital pin as an output.
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(potPin, INPUT);
    srand(micros());

    Serial.begin(38400);
    controller.matrix.begin();
    controller.matrix.setBrightness(controller.currentBrightness);
    controller.matrix.setColorCorrection(cc24);

    timer.setInterval(50, checkButtonPress);
    timer.setInterval(200, checkBrightness);
    timer.setInterval(8000, showAnimation);
    timer.setInterval(15000, nextAnimation);
}

// the loop() method runs over and over again,
// as long as the board has power
void loop() {
    timer.run();
    delay(10);
}

