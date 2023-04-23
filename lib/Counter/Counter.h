#pragma once

#include <Arduino.h>
#include <vector>

using IntervalFunc = void (*)(void);
using TimeoutFunc = void (*)(uint32_t, uint32_t, bool);

struct IntervalStruct {
  IntervalFunc cb;
  boolean isMicroseconds = false;
  uint64_t startTime = 0;
  uint64_t interval = 0;
};

struct TimeoutStruct {
  TimeoutFunc cb;
  uint32_t startTime = 0;
  uint32_t timeout = 0;
  boolean expired = false;
};

class Counter {
  public:
    
    void setInterval(uint64_t _interval, IntervalFunc cb, boolean isMicroseconds = false);
    void setTimeout(uint32_t _timeout, TimeoutFunc cb);
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
