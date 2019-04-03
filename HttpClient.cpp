#include "HttpClient.h"

HTTPClient::HTTPClient(int pinNumberRX, int pinNumberTX) {
    this->ESPserial = new SoftwareSerial(pinNumberRX, pinNumberTX);
}

void HTTPClient::setup() {
    ESPserial->begin(9600);  //  communication with the ESP8266
    Serial.println("HTTPClient Ready");
};

int HTTPClient::loop() {
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

void HTTPClient::parseEspInput() {
    while (ESPserial->available()) {
        char c = this->ESPserial->read();
        if (c == '\n') {
            this->inputReady = true;
        } else {
            this->input += c;
        }
    }
}

bool HTTPClient::currentInputEqual(String text) {
    return (this->input.equals(text) ||
            this->input.equals(text + "\n") ||
            this->input.equals(text + "\r") ||
            this->input.equals(text + "\0"));
}

void HTTPClient::executeAction(String action){
    ESPserial->println(action);
}

void HTTPClient::executeFetch(){
    this->executeAction("GET");
}
void HTTPClient::executeLock(){
    this->executeAction("LOCK");
}
void HTTPClient::executeUnlock(){
    this->executeAction("UNLOCK");
}