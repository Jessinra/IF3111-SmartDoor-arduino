#include "Display7Segment.h"

Display7Segment::Display7Segment(int pinCLK, int pinDIO) {
    this->pinCLK = pinCLK;
    this->pinDIO = pinDIO;
}

void Display7Segment::setup() {
    this->display = new TM1637Display(this->pinCLK, this->pinDIO);
    this->display->setBrightness(this->brightness);
    this->doorState = DOOR_UNLOCKED;

    this->display7Idle();
    delay(500);
    display->clear();
}

void Display7Segment::loop() {
}

void Display7Segment::displayOnChangeState(int doorState) {
    if (this->doorState == DOOR_LOCKED && doorState == DOOR_UNLOCKED) {
        this->doorState = doorState;
        this->display7Open();

    } else if (this->doorState == DOOR_UNLOCKED && doorState == DOOR_LOCKED) {
        this->doorState = doorState;
        this->display7Close();
    }
}

void Display7Segment::display7Hello() {
    const uint8_t SEG_HELLO[] = {
        0x00,
        0x00,
        0x00,
        SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,          // H
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
        SEG_D | SEG_E | SEG_F,                          // L
        SEG_D | SEG_E | SEG_F,                          // L
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
        0x00,
        0x00,
        0x00,
        0x00,
    };

    for (int i = 0; i < 9; i++) {
        display->setSegments(SEG_HELLO + i);
        delay(500);
    }
}

void Display7Segment::display7Bye() {
    const uint8_t SEG_BYE[] = {
        0x00,
        SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,  // b
        SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,  // y
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,  // E
    };

    for (int i = 0; i < 10; i++) {
        display->setSegments(SEG_BYE);
        delay(500);
    }

    display->clear();
}

void Display7Segment::display7Close() {
    const uint8_t SEG_CLOSE[] = {
        0x00,
        0x00,
        0x00,
        SEG_A | SEG_D | SEG_E | SEG_F,                  // C
        SEG_D | SEG_E | SEG_F,                          // L
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
        SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,          // S
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
        SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
        0x00,
        0x00,
        0x00,
        0x00,
    };

    for (int i = 0; i < 10; i++) {
        display->setSegments(SEG_CLOSE + i);
        delay(500);
    }
}

void Display7Segment::display7Open() {
    const uint8_t SEG_OPEN[] = {
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
        SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,          // P
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
        SEG_C | SEG_E | SEG_G,                          // n
    };
    for (int i = 0; i < 5; i++) {
        display->setSegments(SEG_OPEN);
        delay(500);
        delay(500);
        display->clear();
        delay(500);
    }
}

void Display7Segment::display7Send() {
    const uint8_t SEG_CLOSE[] = {
        0x00,
        0x00,
        0x00,
        SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
        SEG_C | SEG_E | SEG_G,
        SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
        0X00,
        SEG_C | SEG_E | SEG_G,
        SEG_C | SEG_D | SEG_E,
        SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
        SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
        0x00,
        0x00,
        0x00,
        0x00,
    };

    for (int i = 0; i < 14; i++) {
        display->setSegments(SEG_CLOSE + i);
        delay(500);
    }
}

void Display7Segment::display7Idle() {
    const uint8_t SEG_IDLE[] = {
        SEG_G,
        SEG_G,
        SEG_G,
        SEG_G,
    };
    display->setSegments(SEG_IDLE);
}

void Display7Segment::display7PatternMissmatch() {
    const uint8_t SEG_IDLE[] = {
        SEG_G,
        SEG_G,
        SEG_G,
        SEG_G,
    };

    for (int i = 0; i < 6; i++) {
        display->setSegments(SEG_IDLE);
        delay(150);
        display->clear();
        delay(150);
    }
}

void Display7Segment::display7Opening() {
    const uint8_t SEG_OPENING[] = {
        SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
        SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,          // P
        SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,          // E
        SEG_C | SEG_E | SEG_G,                          // n
        SEG_C,                                          // i
        SEG_C | SEG_E | SEG_G,                          // n
        SEG_A | SEG_G | SEG_C | SEG_D | SEG_E | SEG_F,  // G
        SEG_D,
        SEG_D,
        SEG_D,
        SEG_D,
    };

    display->setSegments(SEG_OPENING);
    delay(500);

    for (int i = 0; i < 8; i++) {
        display->setSegments(SEG_OPENING + i);
        delay(300);
    }
}

