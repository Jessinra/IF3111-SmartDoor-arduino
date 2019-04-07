#ifndef BELL_CONTROLLER_H
#define BELL_CONTROLLER_H

#include <Arduino.h>
#include "DoorHttpClient.h"

using namespace std;

class BellController {
    public:
        BellController(int pinNumber, DoorHTTPClient &httpClient);
        void sendNotification();
        void setup();
        void loop();

    private:

        int pinNumber;
        unsigned long lastPressed;

        DoorHTTPClient &httpClient;
        bool isBellPressed();
        bool shouldHandleBell();

};

#endif