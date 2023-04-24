# CounterLibrary
 This library is intended to mimic the javascript `setInterval` and `setTimeout` methods.
 Written for the `Arduino` framework.


You need to have a c++17 compiler in order to compile it.
If you are using platformIO just add these lines to the `platformio.ini` file

If you don't have a gnu++17 compiler you must have to fork and modify this library.
You must remove the inline class definition and rewrite so it does not use vectors.

```
build_flags = 	-std=gnu++17
build_unflags = -std=gnu++11
```

This will set it to gnu++17.

# How to use:

**setInterval with lambda function**

```cpp
#include <Arduino.h> // Include Arduino.h if you are using platformIO.
#include <Counter.h>

void setup() {
  Serial.begin(115200);
  
  // Set an interval in milliseconds. This callback function will execute in every 1000 milliseconds.
  counter.setInterval(1000, []() {
    Serial.println("Executing!");
  });
  
  // Set an interval in microseconds. This callback function will execute in every 100000 microsecond.
  counter.setInterval(100000, []() {
    Serial.println("Executing!");
  },true);
  
}

void loop() {
  counter.handle();
}
```


**setInterval with normal function**

```cpp
#include <Arduino.h> // Include Arduino.h if you are using platformIO.
#include <Counter.h>

void myIntervalCallback() {
  Serial.println("Executing");
}

void myIntervalMicrosCallback() {
  Serial.println("Executing");
}

void setup() {
  Serial.begin(115200);
  
  // Set an interval in milliseconds. This callback function will execute in every 5000 milliseconds.
  counter.setInterval(5000, myIntervalCallback );
 
  // Set an interval in microseconds. This callback function will execute in every 500000 microseconds.
  counter.setInterval(500000, myIntervalMicrosCallback );
  
}

void loop() {
  counter.handle();
}
```


**setTimeout with lambda function**

```cpp
#include <Arduino.h> // Include Arduino.h if you are using platformIO.
#include <Counter.h>

void setup() {
  Serial.begin(115200);
  
  // Set a timeout for 2000 milliseconds. Starting from the time when it is registered.
  counter.setTimeout(2000, [](uint32_t deltaMillis, uint32_t deltaSec, boolean expired) {
    if ( expired ) {
      Serial.println("Timeout!");
    }
  });

}

void loop() {
  counter.handle();
}
```


**setTimeout with normal function**

```cpp
#include <Arduino.h> // Include Arduino.h if you are using platformIO.
#include <Counter.h>

void myTimeoutCallback(uint32_t remainingMillis, uint32_t remainingSeconds, boolean expired) {
  if ( expired ) {
      Serial.println("Timeout!");
   }
}

void setup() {
  Serial.begin(115200);
  
  // Set a timeout for 2000 milliseconds. Starting from the time when it is registered.
  counter.setTimeout(2000, myTimeoutCallback);
}

void loop() {
  counter.handle();
}
```


**clearTimeout and clearInterval**

```cpp
#include <Arduino.h> // Include Arduino.h if you are using platformIO.
#include <Counter.h>

uint32_t intervalID;
void setup() {
  Serial.begin(115200);
  
  // This lambda will excute every second.
  intervalID = counter.setInterval(1000, [](){
    Serial.printf("Szia %lu\n",millis());
  });
  
  // When this timer expires, it will clear the above interval.
  counter.setTimeout(2000, [](uint32_t deltaMillis, uint32_t deltaSec, boolean expired) {
    if ( expired ) {
      Serial.println("Timeout!");
      counter.clearInterval(intervalID);
    }
  });
  
}

void loop() {
  counter.handle();
}
```
