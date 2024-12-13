//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_CURVETARGET_H
#define CODEPAMI_CURVETARGET_H

#include "Target.h"
#include "curves/Curve.h"
class CurveTarget : public Target{
protected:
    bool done = false;
    double acc;
    double max_speed;
    double dec;
    Curve* curve = nullptr;
    Ramp* distanceRamp = nullptr;
    double t = 0.0f;
    Position target_pos ={0,0};
    Position end_pos;
public:
    CurveTarget(Robot* robot, double acc, double max_speed, double dec, Position end_pos);

    bool is_done() override;

    void process() override;

    ~CurveTarget() override;
};


#endif //CODEPAMI_CURVETARGET_H
