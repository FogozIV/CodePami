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
    PRECISION_DATA_TYPE acc;
    PRECISION_DATA_TYPE max_speed;
    PRECISION_DATA_TYPE dec;
    Curve* curve = nullptr;
    Ramp* distanceRamp = nullptr;
    PRECISION_DATA_TYPE t = 0.0f;
    Position target_pos ={0,0};
    Position end_pos;
public:
    CurveTarget(Robot* robot, PRECISION_DATA_TYPE acc, PRECISION_DATA_TYPE max_speed, PRECISION_DATA_TYPE dec, Position end_pos);

    bool is_done() override;

    void process() override;

    ~CurveTarget() override;
};


#endif //CODEPAMI_CURVETARGET_H
