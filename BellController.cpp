#include "BellController.h"

BellController::BellController(int pinNumber, DoorHTTPClient &httpClient) : httpClient(httpClient) {
    this->pinNumber = pinNumber;
    pinMode(this->pinNumber, INPUT_PULLUP);
}
void BellController::sendNotification() {
    this->httpClient.executeNotify();
}

bool BellController::isBellPressed() {
    return !digitalRead(this->pinNumber);
}

bool BellController::shouldHandleBell() {
    return millis() > 3000 + this->lastPressed;
}

void BellController::loop() {

    if (this->isBellPressed() && this->shouldHandleBell()) {

        Serial.println("bell pressed");
        this->lastPressed = millis();
        this->sendNotification();
    }
}