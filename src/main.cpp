#include <Arduino.h>
#include <new>

#include "Position.h"
#include <Romi32U4.h>
Romi32U4Encoders encoders;

#define TRACK_MM 142.0f
#define TICK_PER_MM 6.58f


void setup() {
    Position position(12,4,5);
    Position position2(13,10,6);
    Position pos = position + position2;
    Position arg = static_cast<Position&&>(pos);
    std::nothrow
    Serial.print("Position: ");
    Serial.println(pos);
    Serial.println(arg);
// write your initialization code here
}

void loop() {
// write your code here
}