#ifndef SENSOR_SOUND_H
#define SENSOR_SOUND_H

#include <Arduino.h>
using namespace std;

class SensorSound {
   public:
    SensorSound(int pinNumber);

    void setup();
    int loop();

    void recordPattern();
    void resetListeningTimer();
    void resetPattern();

    int getPattern();

   private:
    int pinNumber;

    int recordedPattern;
    int pattern;
    unsigned long listeningTimer;

    /* Config */
    int listeningDuration = 7000;
    int patternTolerance = 10;

    void setPattern(int input);
    void listenToPattern();
    bool isListeningTimeUp();
    bool isSoundOn();
    bool isPatternMatch();
};

#endif