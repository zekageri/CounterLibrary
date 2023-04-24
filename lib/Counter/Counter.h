#pragma once

#include <Arduino.h>

#include <vector>

/*
  For this library to work, you need at least a gnu++17 to compile.
*/

/*
  Callback functions.
*/
using IntervalFunc = void (*)(void);
using TimeoutFunc = void (*)(uint32_t, uint32_t, bool);

/*
  Structure to hold the Interval variables.
*/
struct IntervalStruct {
    IntervalFunc cb;
    boolean isMicroseconds = false;
    uint64_t startTime = 0;
    uint64_t interval = 0;
    uint32_t id;
};

/*
  Structure to hold the Timeout variables.
*/

struct TimeoutStruct {
    TimeoutFunc cb;
    uint32_t startTime = 0;
    uint32_t timeout = 0;
    boolean isExpired = false;
    uint32_t id;
};

/*
  Base class
*/
class Counter {
   public:
    uint32_t setInterval(uint64_t _interval, IntervalFunc cb, boolean isMicroseconds = false);
    boolean setIntervalDelay(uint32_t id, uint32_t newInterval);
    boolean clearInterval(uint32_t id);

    uint32_t setTimeout(uint32_t _timeout, TimeoutFunc cb);
    boolean setTimeoutDelay(uint32_t id, uint32_t newTimeout);
    boolean clearTimeout(uint32_t id);
    void handle();

   private:
    int intervalsIndex = 0;
    int timeoutsIndex = 0;
    std::vector<IntervalStruct> intervals;
    std::vector<TimeoutStruct> timeouts;

    void handleIntervals();
    void handleTimeouts();
};
inline Counter counter;
