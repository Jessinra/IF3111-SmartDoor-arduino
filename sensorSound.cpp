#include "SensorSound.h"

SensorSound::SensorSound(int pinNumber) {
    this->pinNumber = pinNumber;
    pinMode(this->pinNumber, INPUT);
}; 

void SensorSound::setup() {

    for(int i = 3; i > 0; i--){
        Serial.print("Recording in : ");
        Serial.println(i);
        delay(1000);
    }
    this->recordPattern();

    Serial.println("Setup: Sound sensor ready");
}

int SensorSound::loop() {
    /* 
    Return code :
    -1 if not ready (time's not up)
    0 if pattern unmatch
    1 if pattern match    
    */

    if (!this->isListeningTimeUp()) {
        this->listenToPattern();
        return -1;
    }

    return this->isPatternMatch();
}

void SensorSound::recordPattern() {
    Serial.println("========== recording pattern ============");

    this->pattern = 0;
    this->resetListeningTimer();

    while (!(this->isListeningTimeUp())) {
        if (this->isSoundOn()) {
            this->pattern++;
            Serial.println(this->pattern);
        }
    }
    setPattern(this->pattern);
}

bool SensorSound::isListeningTimeUp() {
    return (millis() - this->listeningTimer) >= this->listeningDuration;
}

bool SensorSound::isSoundOn() {
    return digitalRead(this->pinNumber) == 1;
}

bool SensorSound::isPatternMatch() {
    return (this->pattern > -this->patternTolerance) && (this->pattern < this->patternTolerance);
}

void SensorSound::resetListeningTimer() {
    this->listeningTimer = millis();
}

void SensorSound::resetPattern() {
    this->pattern = this->recordedPattern;
}

void SensorSound::listenToPattern() {
    if (this->isSoundOn()) {
        this->pattern--;
        Serial.println(this->pattern);
    }
}

void SensorSound::setPattern(int input) {
    this->recordedPattern = input;

    Serial.print("recorded pattern : ");
    Serial.println(input);
}