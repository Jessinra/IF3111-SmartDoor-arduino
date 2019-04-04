#ifndef DISPLAY_7_SEGMENT
#define DISPLAY_7_SEGMENT

#include <Arduino.h>
#include <TM1637Display.h>
using namespace std;

class Display7Segment {
   public:
    Display7Segment(int pinCLK, int pinDIO);

    void displayOnChangeState(int doorState);

    void display7Hello();
    void display7Bye();
    void display7Close();
    void display7Open();
    void display7Send();

    void setup();
    void loop();

   private:
    int pinCLK;
    int pinDIO;
    TM1637Display* display;
    int brightness = 3;
    int doorState;

    int const DOOR_LOCKED = 1;
    int const DOOR_UNLOCKED = 0;
};
#endif