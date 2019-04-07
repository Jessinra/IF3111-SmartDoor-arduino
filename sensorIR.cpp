#include "SensorIR.h"

SensorIR::SensorIR(int pinNumber) {
    this->pinNumber = pinNumber;
}

void SensorIR::setup() {
    pinMode(this->pinNumber, INPUT);
}

void SensorIR::loop() {

    Serial.print(digitalRead(this->pinNumber));

    if (this->isInfraredOn()) {
        Serial.println(" on");
    } else {
        Serial.println(" off");
    }

    delay(1000);
}

bool SensorIR::isInfraredOn() {
    return digitalRead(this->pinNumber) == 0;
}