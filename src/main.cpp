#include <Arduino.h>
#include <Counter.h> // Counter.h is inside the lib folder

uint32_t intervalID;
uint32_t lastSec, lastAgainSec;

void setup() {
    Serial.begin(115200);

    intervalID = counter.setInterval(1000, []() {
        Serial.printf("Interval %lu\n", millis());
    });

    counter.setTimeout(1000, [](uint32_t remainingMillis, uint32_t remainingSec, boolean expired) {
        if (expired) {
            boolean success = counter.setIntervalDelay(intervalID, 500);
            Serial.printf("Interval delay %s\n", success ? "modified" : "failed to modify.");
        }
        if (lastAgainSec != remainingSec) {
            lastAgainSec = remainingSec;
            Serial.printf("%d seconds before setting the interval.\n", lastAgainSec);
        }
    });

    counter.setTimeout(20000, [](uint32_t remainingMillis, uint32_t remainingSec, boolean expired) {
        if (expired) {
            if (counter.clearInterval(intervalID)) {
                Serial.println("Interval successfully deleted");
            }
            return;
        }
        if (lastSec != remainingSec) {
            lastSec = remainingSec;
            Serial.printf("%d seconds before clearing the interval.\n", lastSec);
        }
    });

    counter.setInterval(2000, []() {
        Serial.println("I'm running every 2 secs!");
    });
}

void loop() {
    counter.handle();
}