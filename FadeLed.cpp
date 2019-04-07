#include "FadeLed.h"

FadeLed::FadeLed(int pinNumber) {
    this->pinNumber = pinNumber;
    this->fadeAmount = 5;
    this->ledBrightness = 255;
    this->lastFade = 0;
}

void FadeLed::setup() {
    pinMode(this->pinNumber, OUTPUT);
}

void FadeLed::loop() {
    if (millis() > 20 + this->lastFade){
        this->fade();
        this->lastFade = millis();
    }
}

void FadeLed::turnOff(){
    analogWrite(this->pinNumber, 0);
}

void FadeLed::fade(){

    if (this->ledBrightness <= 0 || this->ledBrightness >= 255) {
        this->fadeAmount = -(this->fadeAmount);
    }

    this->ledBrightness += this->fadeAmount;
    analogWrite(this->pinNumber, this->ledBrightness);
}
