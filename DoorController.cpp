#include "DoorController.h"

DoorController::DoorController(int pinNumber) {
    this->pinNumber = pinNumber;
    pinMode(this->pinNumber, OUTPUT);
}

void DoorController::setup() {
    this->doorServo.attach(this->pinNumber);
    this->doorState = DOOR_UNLOCKED;

    Serial.println("Setup: Door controller ready");
}

void DoorController::setDoorState(int doorState) {
    if (doorState == DOOR_LOCKED || doorState == DOOR_UNLOCKED) {
        this->doorState = doorState;
    }   
}

void DoorController::syncDoorState() {
    if (this->doorState == DOOR_LOCKED) {
        this->lock();
    } else if (this->doorState == DOOR_UNLOCKED) {
        this->unlock();
    }
}

void DoorController::lock() {
    this->doorServo.write(30);
}

void DoorController::unlock() {
    this->doorServo.write(115);
}