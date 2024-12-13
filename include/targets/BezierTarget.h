//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_ANGLETARGET_H
#define CODEPAMI_ANGLETARGET_H
#include "CurveTarget.h"

class BezierTarget : public CurveTarget {
protected:
    double multiplier;
public:
    BezierTarget(Robot *robot, double acc, double max_speed, double dec, Position end_pos, double multiplier=100.0f);

    void init() override;

    void on_done() override;

};

#endif //CODEPAMI_ANGLETARGET_H
