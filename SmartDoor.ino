
#include "sensorSound.h"

#define STATE_OFF 0
#define STATE_STANDBY 1
#define STATE_LISTENING 3

int systemState;
SoundSensor soundSensor(7);

void startListening() {
    systemState = STATE_LISTENING;
    soundSensor.resetListeningTimer();
    soundSensor.resetPattern();
}
void stopListening() {
    systemState = STATE_STANDBY;
}

void setup() {
    Serial.begin(9600);
    soundSensor.setup();
    systemState == STATE_OFF;
}

void loop() {
    // Turn on listening state
    if (systemState == STATE_OFF) {
        startListening();
    }

    if (systemState == STATE_LISTENING) {
        int status = soundSensor.loop();

        if (status == 1) {
            Serial.println("============= match ");
            stopListening();
            // TODO : open door + send HTTP request

        } else if (status == 0) {
            Serial.println("============= unmatch ");
            startListening();
            // TODO : do nothing
        }
    }
}
