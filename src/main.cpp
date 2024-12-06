#include <Arduino.h>
#include <new>

#include "Position.h"
#include <Romi32U4.h>
Romi32U4Encoders encoders;

#define TRACK_MM 142.0f
#define TICK_PER_MM 6.58f


void setup() {
    Serial.begin(9600);
    delay(1000);
// write your initialization code here
}

void loop() {
// write your code here
}