#include <Arduino.h>
#include <Counter.h>

void setup() {
  Serial.begin(115200);

  counter.setInterval(1000, []() {
    Serial.println("Szia");
  });

  counter.setTimeout(2000, [](uint32_t deltaMillis, uint32_t deltaSec, boolean expired) {
    if ( expired ) {
      Serial.println("Timeout!");
    }
  });
}

void loop() {
  counter.handle();
}