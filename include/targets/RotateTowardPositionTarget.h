//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_ROTATETOWARDPOSITIONTARGET_H
#define CODEPAMI_ROTATETOWARDPOSITIONTARGET_H
#include "Target.h"

class RotateTowardPositionTarget : public Target{
    Position pos;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
    double target;
public:
    RotateTowardPositionTarget(Robot *robot, const Position& pos, double acc=10, double dec=10, double max_speed=45);

    void init() override;

    bool is_done() override;

    void process() override;

    void on_done() override;

    ~RotateTowardPositionTarget() override;
};

#endif //CODEPAMI_ROTATETOWARDPOSITIONTARGET_H
