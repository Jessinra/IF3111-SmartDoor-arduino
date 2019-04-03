#ifndef DOOR_HTTP_CLIENT_H
#define DOOR_HTTP_CLIENT_H

#include "HttpClient.h"

class DoorHTTPClient : HTTPClient{

    public:

        DoorHTTPClient(int pinNumberRX, int pinNumberTX);
        
        void setup();
        int loop();

        void executeFetch();
        void executeLock();
        void executeUnlock();

    private:

        unsigned long checkStateTimer = 0;
        unsigned long lockTimer = 4000;
        unsigned long unlockTimer = 12000;

        const int DOOR_LOCKED = 1;
        const int DOOR_UNLOCKED = 0;
};
#endif