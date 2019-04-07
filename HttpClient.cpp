#include "HttpClient.h"

HTTPClient::HTTPClient(int pinNumberRX, int pinNumberTX) {
    this->ESPserial = new SoftwareSerial(pinNumberRX, pinNumberTX);
}

void HTTPClient::setup() {
    ESPserial->begin(9600);  //  communication with the ESP8266
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