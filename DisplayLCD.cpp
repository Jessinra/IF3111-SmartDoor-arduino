#include "DisplayLCD.h"

String DisplayLCD::textToShow = "";

DisplayLCD::DisplayLCD(int pinData, int pinClock, int pinEnable) {
    this->pinData = pinData;
    this->pinClock = pinClock;
    this->pinEnable = pinEnable;
}

void DisplayLCD::setup() {
    this->display = new LiquidCrystal_SR(this->pinData, this->pinClock, this->pinEnable);
    this->display->begin(16, 2);  // initialize the lcd
    this->doorState = DOOR_UNDF;

    DisplayLCD::textToShow = "System's up...";
}

void DisplayLCD::print(String text1 = "", String text2 = "") {
    this->clear();
    this->display->print(text1);

    this->display->setCursor(0, 1);  // second line
    this->display->print(text2);
}

void DisplayLCD::clear() {
    this->display->clear();
}

void DisplayLCD::setCurrentText(String text) {
    this->currentText = text;
}

bool DisplayLCD::isNewTextAvailable() {
    return DisplayLCD::textToShow != this->currentText;
}

void DisplayLCD::loop() {
    if (this->isNewTextAvailable()) {
        this->print(DisplayLCD::textToShow);
        this->setCurrentText(DisplayLCD::textToShow);
    }
}

void DisplayLCD::turnOff() {
    this->display->noDisplay();
}

void DisplayLCD::turnOn() {
    this->display->display();
}

void DisplayLCD::displayOnChangeState(int doorState) {
    if (this->doorState == DOOR_LOCKED && doorState == DOOR_UNLOCKED) {
        this->doorState = doorState;
        this->print("System's up", "Door Unlocked");

    } else if (this->doorState == DOOR_UNLOCKED && doorState == DOOR_LOCKED) {
        this->doorState = doorState;
        this->print("System's up", "Door Locked");
    }

    // First time
    else if (this->doorState == DOOR_UNDF) {
        if (doorState == DOOR_UNLOCKED) {
            this->doorState = doorState;
            this->print("System's up", "Door Unlocked");
        } else if (doorState == DOOR_LOCKED) {
            this->doorState = doorState;
            this->print("System's up", "Door Locked");
        }
    }
}
