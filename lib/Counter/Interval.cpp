#include "Counter.h"

/*
    Adds a new interval function to the vector.
    If isMicroseconds is not specified, the system will count with milliseconds.
*/
uint32_t Counter::setInterval(uint64_t _interval, IntervalFunc cb, boolean isMicroseconds) {
    IntervalStruct interval;
    interval.cb = cb;
    interval.interval = _interval;
    interval.isMicroseconds = isMicroseconds;
    interval.startTime = isMicroseconds ? micros() : millis();
    interval.id = esp_random();
    intervals.push_back(interval);
    return interval.id;
}

boolean Counter::setIntervalDelay(uint32_t id, uint32_t newInterval) {
  for (int i = 0; i < intervals.size(); i++) {
    if (intervals[i].id == id) {
      intervals[i].interval = newInterval;
      return true;
    }
  }
  return false;
}

/*
    Returns true if the callback was erased, false if not found.
*/
boolean Counter::clearInterval(uint32_t id) {
    for (int i = 0; i < intervals.size(); i++) {
        if (intervals[i].id == id) {
            intervals.erase(intervals.begin() + i);
            return true;
        }
    }
    return false;
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
