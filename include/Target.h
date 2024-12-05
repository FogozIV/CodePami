#include "Arduino.h"
#include "Position.h"

#ifndef TARGET_H
#define TARGET_H
class Target{

};

class AngleTarget : public Target{

};

class PositionTarget : public Target{
    Position pos;
};



#endif