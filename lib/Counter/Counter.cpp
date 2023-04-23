#include "Counter.h"

void Counter::handle() {
    handleIntervals();
    handleTimeouts();
}