#include "Counter.h"

void Counter::setTimeout(uint32_t _timeout, TimeoutFunc cb) {
    TimeoutStruct timeout;
    timeout.cb = cb;
    timeout.startTime = millis();
    timeout.timeout = _timeout;
    timeout.expired = false;
    timeouts.push_back(timeout);
}

void Counter::handleTimeouts() {
    if (timeouts.empty()) {
        return;
    }

    TimeoutStruct timeout = timeouts[timeoutsIndex];

    if (!timeout.expired) {
        uint32_t now = millis();
        uint32_t deltaTime = timeout.timeout - (now - timeout.startTime);
        if (deltaTime <= 0) {
            timeout.expired = true;
        }
        timeout.cb(deltaTime, deltaTime / 1000, timeout.expired);
        timeouts[timeoutsIndex] = timeout;
    }

    timeoutsIndex++;
    if (timeoutsIndex >= timeouts.size()) {
        timeoutsIndex = 0;
    }
}