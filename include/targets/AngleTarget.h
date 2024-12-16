//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_ANGLETARGET_H
#define CODEPAMI_ANGLETARGET_H
#include "Target.h"

class AngleTarget : public Target{
    double target;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
public:
    AngleTarget(Robot *robot, double target, double acc=90, double dec=90, double max_speed=90);

    ~AngleTarget() override;

    void init() override;

    bool is_done() override;

    void process() override;

    void on_done() override;

};
#endif //CODEPAMI_ANGLETARGET_H
