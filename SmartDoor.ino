
#include "DoorController.h"
#include "DoorHTTPClient.h"
#include "BellController.h"
#include "SensorIR.h"
#include "SensorSound.h"
#include "Display7Segment.h"

#define STATE_OFF 0
#define STATE_STANDBY 1
#define STATE_LISTENING 3

int systemState;
int doorState;

DoorHTTPClient doorHttpClient(2, 3);
SensorIR sensorIR(6);
SensorSound sensorSound(7);
Display7Segment display7(4, 5);

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

void setup() {
    Serial.begin(9600);
    // sensorSound.setup();
    doorHttpClient.setup();
    doorController.setup();
    display7.setup();

    systemState == STATE_OFF;
}

void loop() {
    /* Door Section */

    bellController.loop();

    doorState = doorHttpClient.loop();
    doorController.setDoorState(doorState);
    doorController.syncDoorState();

    display7.displayOnChangeState(doorState);

    /* Sound sensor Section */
    // if (systemState == STATE_OFF) {
    //     startListening();
    // }

    // if (systemState == STATE_LISTENING) {
    //     int status = sensorSound.loop();

    //     if (status == 1) {
    //         Serial.println("============= match ");
    //         stopListening();
    //         // TODO : open door + send HTTP request

    //     } else if (status == 0) {
    //         Serial.println("============= unmatch ");
    //         startListening();
    //         // TODO : do nothing
    //     }
    // }
}
