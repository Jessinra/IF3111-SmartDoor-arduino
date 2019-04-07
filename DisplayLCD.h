#ifndef DISPLAY_LCD_H
#define DISPLAY_LCD_H

#include <Arduino.h>
#include <LCD.h>
#include <LiquidCrystal_SR.h>
using namespace std;


class DisplayLCD {
   public:
    DisplayLCD(int pinData, int pinClock, int pinEnable);
    void setup();
    void loop();

    void print(String text1, String text2);
    void clear();

    void turnOff();
    void turnOn();
    void displayOnChangeState(int doorState);

    static String textToShow;

   private:
    int pinData;    // pin 14 shift register
    int pinClock;   // pin 11 shift register
    int pinEnable;  // pin 12 shift register

    LiquidCrystal_SR* display;
    String currentText;
    int doorState;

    int const DOOR_LOCKED = 1;
    int const DOOR_UNLOCKED = 0;
    int const DOOR_UNDF = -1;

    void setCurrentText(String text);
    bool isNewTextAvailable();
};
#endif