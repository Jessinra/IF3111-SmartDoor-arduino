#ifndef SENSOR_IR_H
#define SENSOR_IR_H

#include <Arduino.h>
using namespace std;

class SensorIR {
   public:
    SensorIR(int);

    void setup();
    void loop();

    bool isInfraredOn();

   private:
    int pinNumber;
};

#endif
