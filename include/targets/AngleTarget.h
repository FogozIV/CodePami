//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_ANGLETARGET_H
#define CODEPAMI_ANGLETARGET_H
#include "Target.h"

class AngleTarget : public Target{
    PRECISION_DATA_TYPE target;
    Ramp* ramp = nullptr;
    PRECISION_DATA_TYPE max_speed;
    PRECISION_DATA_TYPE acc;
    PRECISION_DATA_TYPE dec;
    bool done = false;
public:
    AngleTarget(Robot *robot, PRECISION_DATA_TYPE target, PRECISION_DATA_TYPE acc=90, PRECISION_DATA_TYPE dec=90, PRECISION_DATA_TYPE max_speed=90, bool optimized=true);

    ~AngleTarget() override;

    void init() override;

    bool is_done() override;

    void process() override;

    void on_done() override;

    bool optimized;
};
#endif //CODEPAMI_ANGLETARGET_H
