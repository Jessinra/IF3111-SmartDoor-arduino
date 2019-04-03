
#include "sensorSound.h"
#include "sensorIR.h"

#define STATE_OFF 0
#define STATE_STANDBY 1
#define STATE_LISTENING 3

int systemState;
SensorIR sensorIR(5);
SensorSound sonsorSound(7);

void startListening() {
    systemState = STATE_LISTENING;
    sonsorSound.resetListeningTimer();
    sonsorSound.resetPattern();
}
void stopListening() {
    systemState = STATE_STANDBY;
}

void setup() {
    Serial.begin(9600);
    sonsorSound.setup();

    systemState == STATE_OFF;
}

void loop() {
    // Turn on listening state
    if (systemState == STATE_OFF) {
        startListening();
    }

    if (systemState == STATE_LISTENING) {
        int status = sonsorSound.loop();

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
