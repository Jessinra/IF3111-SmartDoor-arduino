#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <Arduino.h>
#include <SoftwareSerial.h>
using namespace std;

class HTTPClient {
   public:
    HTTPClient(int pinNumberRX, int pinNumberTX);

    void setup();
    virtual int loop() = 0;

   protected:
    String input;
    bool inputReady = false;

    void parseEspInput();
    bool currentInputEqual(String text);
    void executeAction(String action);

   private:
    int pinNumberRX;
    int pinNumberTX;
    SoftwareSerial* ESPserial;
};
#endif
