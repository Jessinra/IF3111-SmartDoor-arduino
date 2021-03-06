#include "DoorController.h"

DoorController::DoorController(int pinNumber) {
    this->pinNumber = pinNumber;
}

void DoorController::setup() {
    pinMode(this->pinNumber, OUTPUT);
    this->doorServo.attach(this->pinNumber);
    this->doorState = DOOR_UNLOCKED;
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