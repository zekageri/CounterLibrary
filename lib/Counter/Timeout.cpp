#include "Counter.h"

/*
    Adds a new timeout function to the vector.
    Timeout will be deleted if it is expired.
    Callback function will return the remaining
        milliseconds and seconds in every iteration along with the isExpired flag.
*/
void Counter::setTimeout(uint32_t _timeout, TimeoutFunc cb) {
    TimeoutStruct timeout;
    timeout.cb = cb;
    timeout.startTime = millis();
    timeout.timeout = _timeout;
    timeout.isExpired = false;
    timeouts.push_back(timeout);
}

void Counter::handleTimeouts() {
    if (timeouts.empty()) {
        return;
    }

    TimeoutStruct timeout = timeouts[timeoutsIndex];

    if (!timeout.isExpired) {
        uint32_t now = millis();
        uint32_t deltaTime = timeout.timeout - (now - timeout.startTime);
        if (deltaTime <= 0) {
            timeout.isExpired = true;
        }
        timeout.cb(deltaTime, deltaTime / 1000, timeout.isExpired);
        timeouts[timeoutsIndex] = timeout;
    }

    timeoutsIndex++;
    if (timeoutsIndex >= timeouts.size()) {
        timeoutsIndex = 0;
    }
}