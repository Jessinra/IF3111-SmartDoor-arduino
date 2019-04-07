#ifndef FADELED_H
#define FADELED_H

#include <Arduino.h>

class FadeLed{

    public:
        FadeLed(int pinNumber);
        void setup();
        void loop();
        void turnOff();

    private:
        int pinNumber;
        int ledBrightness;
        int fadeAmount;

        unsigned long lastFade;

        void fade();
};
#endif;