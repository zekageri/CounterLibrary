#include "Counter.h"

/*
    Adds a new interval function to the vector.
    If isMicroseconds is not specified, the system will count with milliseconds.
*/
void Counter::setInterval(uint64_t _interval, IntervalFunc cb, boolean isMicroseconds) {
    IntervalStruct interval;
    interval.cb = cb;
    interval.interval = _interval;
    interval.isMicroseconds = isMicroseconds;
    interval.startTime = isMicroseconds ? micros() : millis();
    intervals.push_back(interval);
}

void Counter::handleIntervals() {
    if (intervals.empty()) {
        return;
    }
    IntervalStruct interval = intervals[intervalsIndex];

    uint64_t now = interval.isMicroseconds ? micros() : millis();
    if (now - interval.startTime >= interval.interval) {
        interval.startTime = now;
        interval.cb();
        intervals[intervalsIndex] = interval;
    }
    intervalsIndex++;
    if (intervalsIndex >= intervals.size()) {
        intervalsIndex = 0;
    }
}