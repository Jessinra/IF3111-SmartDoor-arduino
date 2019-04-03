
#include "sensorSound.h"
#include "sensorIR.h"
#include "DoorHTTPClient.h"

#define STATE_OFF 0
#define STATE_STANDBY 1
#define STATE_LISTENING 3

int systemState;

DoorHTTPClient doorHttpClient(2,3);
SensorIR sensorIR(5);
SensorSound sensorSound(7);

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
    // doorHttpClient.setup();

    systemState == STATE_OFF;
}

void loop() {
    
    /* Door Section */
    // doorHttpClient.loop();

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
