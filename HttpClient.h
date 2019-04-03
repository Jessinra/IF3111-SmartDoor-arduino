#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <Arduino.h>
#include <SoftwareSerial.h>
using namespace std;

class HTTPClient {
   public:
    HTTPClient(int pinNumberRX, int pinNumberTX);

    void setup();
    int loop();

    void executeFetch();
    void executeLock();
    void executeUnlock();

   private:
    int pinNumberRX;
    int pinNumberTX;
    SoftwareSerial* ESPserial;

    String input;
    bool inputReady = false;

    void parseEspInput();
    bool currentInputEqual(String text);

    void executeAction(String action);

    unsigned long checkStateTimer = 0;
    unsigned long lockTimer = 4000;
    unsigned long unlockTimer = 12000;
};
#endif
