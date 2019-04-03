#include "DoorHttpClient.h"

DoorHTTPClient::DoorHTTPClient(int pinNumberRX, int pinNumberTX) : HTTPClient(pinNumberRX, pinNumberTX){
    //
}

void DoorHTTPClient::setup() {
    HTTPClient::setup();
    Serial.println("DoorHTTPClient Ready");
};

void DoorHTTPClient::loop() {
    this->parseEspInput();

    if (this->inputReady) {
        Serial.println(this->input);

        if (currentInputEqual("locked")) {
            Serial.println("ok");
        }

        this->input = "";
        this->inputReady = false;
    }

    if (millis() > 8000 + checkStateTimer) {
        executeFetch();
        checkStateTimer = millis();
    }
    if (millis() > lockTimer + 16000) {
        executeLock();
        lockTimer = millis();
    }
    if (millis() > unlockTimer + 16000) {
        executeUnlock();
        unlockTimer = millis();
    }
};

void DoorHTTPClient::executeFetch(){
    this->executeAction("GET");
}
void DoorHTTPClient::executeLock(){
    this->executeAction("LOCK");
}
void DoorHTTPClient::executeUnlock(){
    this->executeAction("UNLOCK");
}