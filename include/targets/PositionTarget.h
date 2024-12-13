//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_POSITIONTARGET_H
#define CODEPAMI_POSITIONTARGET_H
#include "Target.h"

class PositionTarget : public Target{
    Position pos;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
    double end_speed;
    bool backward = false;
public:
    PositionTarget(Robot *robot, const Position &pos, double acc=100, double dec=100, double max_speed=200, double end_speed=0.0);

    void init() override;

    bool is_done() override;

    void process() override;

    ~PositionTarget() override;

    void on_done() override;
};
#endif //CODEPAMI_POSITIONTARGET_H
