
#include "BellController.h"
#include "Display7Segment.h"
#include "DoorController.h"
#include "DoorHTTPClient.h"
#include "SensorIR.h"
#include "SensorSound.h"

#define STATE_SLEEP 0
#define STATE_STANDBY 1
#define STATE_LISTENING 3

int systemState;
int doorState;
unsigned long lastStandby = 0;

DoorHTTPClient doorHttpClient(2, 3);
Display7Segment display7(4, 5);
SensorIR sensorIR(6);
SensorSound sensorSound(7);

DoorController doorController(A2);
BellController bellController(A3, doorHttpClient);

void startListening() {
    systemState = STATE_LISTENING;
    sensorSound.resetListeningTimer();
    sensorSound.resetPattern();
}
void stopListening() {
    systemState = STATE_STANDBY;
}

void standby() {
    systemState = STATE_STANDBY;
    lastStandby = millis();
    display7.display7Hello();
    display7.display7Idle();
}

void checkIfShouldSleep() {
    if (millis() > 40000 + lastStandby) {
        systemState = STATE_SLEEP;

        doorHttpClient.executeLock();
        display7.display7Bye();
    }
}

void setup() {
    Serial.begin(9600);
    doorHttpClient.setup();
    doorController.setup();
    
    display7.setup();
    sensorSound.setup();
    sensorIR.setup();

    systemState == STATE_SLEEP;
}

void loop() {
    if (systemState == STATE_SLEEP) {
        if (sensorIR.isInfraredOn()) {
            standby();
            startListening();
        }
    } else {
        checkIfShouldSleep();
    }

    if (systemState == STATE_LISTENING) {
        /* Bell section */
        bellController.loop();

        /* Pattern matching section */
        int status = sensorSound.loop();
        if (status == 1) {
            display7.display7Opening();
            doorHttpClient.executeUnlock();
            stopListening();

        } else if (status == 0) {
            display7.display7PatternMissmatch();
            display7.display7Idle();
            startListening();
            // TODO : do nothing
        }

    } else {
        doorState = doorHttpClient.loop();
    }

    /* Door Section */
    doorController.setDoorState(doorState);
    doorController.syncDoorState();

    display7.displayOnChangeState(doorState);
}
