#ifndef DOOR_CONTROLLER_H
#define DOOR_CONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

using namespace std;

class DoorController {
   public:
    DoorController(int pinNumber);

    void setup();
    void setDoorState(int doorState);
    void syncDoorState();
    void lock();
    void unlock();

   private:
    int pinNumber;
    Servo doorServo;
    int doorState;

    int const DOOR_LOCKED = 1;
    int const DOOR_UNLOCKED = 0;
};

#endif