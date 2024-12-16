//
// Created by fogoz on 13/12/2024.
//

#include "targets/CurveTarget.h"
#include "Robot.h"

CurveTarget::CurveTarget(Robot *robot, PRECISION_DATA_TYPE acc, PRECISION_DATA_TYPE max_speed, PRECISION_DATA_TYPE dec, Position end_pos) : Target(robot), acc(acc), max_speed(max_speed), dec(dec), end_pos(end_pos) {
}

bool CurveTarget::is_done(){
    return done;
}

void CurveTarget::process(){
    PRECISION_DATA_TYPE distance = (end_pos-robot->getPosition()).getDistance();
    RampReturnData data = this->distanceRamp->compute();
    robot->setRampSpeed(data.speed);
    robot->setTargetDistance(robot->getTargetDistance() + data.distance_increment);
    if((target_pos-robot->getPosition()).getDistance() < 15 && t != 1.0f) {
        this->t = this->curve->getTForLength(this->t, 40.0f);
        target_pos = this->curve->getPosition(this->t);
    }
    robot->setRampSpeed(data.speed);
    robot->setTargetAngle(robot->getAbsoluteAngle((target_pos-robot->getPosition()).getVectorAngle()));
    if(t>=1.0f && distance < 10){
        robot->setTargetDistance(robot->getTotalDistance());
        robot->setDoneDistance(true);
        done = true;
    }
    if(distance < 10) {
        robot->setDoneAngle(true);
    }else{
        robot->setDoneAngle(false);
    }
}


CurveTarget::~CurveTarget() {
    delete curve;
    delete distanceRamp;
}

