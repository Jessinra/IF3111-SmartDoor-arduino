#include "DoorHttpClient.h"

DoorHTTPClient::DoorHTTPClient(int pinNumberRX, int pinNumberTX) : HTTPClient(pinNumberRX, pinNumberTX) {
    //
}

void DoorHTTPClient::setup() {
    HTTPClient::setup();
    Serial.println("Setup: DoorHTTPClient Ready");
};

int DoorHTTPClient::loop() {
    int doorState = -1;

    if (millis() > 8000 + checkStateTimer) {
        executeFetch();
    }

    this->parseEspInput();

    if (this->inputReady) {
        Serial.println(this->input);

        if (currentInputEqual("locked")) {
            doorState = DOOR_LOCKED;
        } else if (currentInputEqual("unlocked")) {
            doorState = DOOR_UNLOCKED;
        } else {
            doorState = -1;
        }

        this->input = "";
        this->inputReady = false;
    }

    return doorState;
};

void DoorHTTPClient::executeFetch() {
    this->executeAction("GET");
    checkStateTimer = millis();
}
void DoorHTTPClient::executeLock() {
    this->executeAction("LOCK");
    checkStateTimer = millis() - 5000;  // reduce the delay before next fetch
}
void DoorHTTPClient::executeUnlock() {
    this->executeAction("UNLOCK");
    checkStateTimer = millis() - 5000;  // reduce the delay before next fetch
}
void DoorHTTPClient::executeNotify() {
    this->executeAction("NOTIFY");
}