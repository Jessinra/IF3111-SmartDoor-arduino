
#include "BellController.h"
#include "Display7Segment.h"
#include "DisplayLCD.h"
#include "DoorController.h"
#include "DoorHTTPClient.h"
#include "FadeLed.h"
#include "SensorIR.h"
#include "SensorSound.h"

#define STATE_SLEEP 0
#define STATE_STANDBY 1
#define STATE_LISTENING 3

int systemState;
int doorState;
unsigned long lastStandby = 0;

DoorHTTPClient doorHttpClient(2, 3);
SensorIR sensorIR(6);
SensorSound sensorSound(7);
Display7Segment display7(4, 5);
DisplayLCD displayLCD(10, 13, 9);
FadeLed led(11);

DoorController doorController(A2);
BellController bellController(A3, doorHttpClient);

void startListening() {
    systemState = STATE_LISTENING;
    sensorSound.resetListeningTimer();
    sensorSound.resetPattern();
}

void stopListening() {
    systemState = STATE_STANDBY;
    led.turnOff();
}

void standby() {
    systemState = STATE_STANDBY;
    lastStandby = millis();
    displayLCD.turnOn();
    display7.display7Hello();
    display7.display7Idle();
}

void checkIfShouldSleep() {
    if (millis() > 40000 + lastStandby) {
        systemState = STATE_SLEEP;

        doorHttpClient.executeLock();
        display7.display7Bye();
        // displayLCD.turnOff();
    }
}

void initializePattern() {
    /* Record Pattern */
    Serial.println("====== Recording Pattern =========");
    displayLCD.print("================", "   Set pattern  ");
    delay(1000);

    Serial.println("Recording in : 3");
    displayLCD.print("Recording in : 3", "");
    delay(1000);

    Serial.println("Recording in : 2");
    displayLCD.print("Recording in : 2", "");
    delay(1000);

    Serial.println("Recording in : 1");
    displayLCD.print("Recording in : 1", "");
    delay(1000);

    Serial.println("Recording...");
    displayLCD.print("Recording...", "");
    sensorSound.recordPattern();

    Serial.print("Recorded hash pattern : ");
    Serial.println(sensorSound.getPattern());

    displayLCD.print("Hash pattern : ", String(sensorSound.getPattern()));
    delay(3000);
}

void setup() {
    Serial.begin(9600);

    displayLCD.setup();
    Serial.println("Setup : displayLCD done");
    displayLCD.print("Display LCD", "Setup : done");
    delay(1000);

    display7.setup();
    Serial.println("Setup : display7 done");
    displayLCD.print("Display 7Segment", "Setup : done");
    delay(1000);

    led.setup();
    Serial.println("Setup : led done");
    displayLCD.print("Led", "Setup : done");
    delay(1000);

    bellController.setup();
    Serial.println("Setup : bellController done");
    displayLCD.print("Bell Controller", "Setup : done");
    delay(1000);

    doorHttpClient.setup();
    Serial.println("Setup : doorHttpClient done");
    displayLCD.print("Door HTTPClient", "Setup : done");
    delay(1000);

    doorController.setup();
    Serial.println("Setup : doorController done");
    displayLCD.print("Door Controller", "Setup : done");
    delay(1000);

    sensorIR.setup();
    Serial.println("Setup : sensorIR done");
    displayLCD.print("Sensor IR", "Setup : done");
    delay(1000);

    sensorSound.setup();
    Serial.println("Setup : sensorSound done");
    displayLCD.print("Sensor Sound", "Setup : done");
    delay(1000);

    initializePattern();

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
        led.loop();

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
        }

    } else {
        doorState = doorHttpClient.loop();
    }

    /* Door Section */
    doorController.setDoorState(doorState);
    doorController.syncDoorState();

    displayLCD.displayOnChangeState(doorState);
    display7.displayOnChangeState(doorState);
}
