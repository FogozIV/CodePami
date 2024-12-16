//
// Created by fogoz on 07/12/2024.
//
#include "./targets/RotateTowardPositionTarget.h"
#include "Robot.h"


void RotateTowardPositionTarget::init() {
    target = (pos-robot->getPosition()).getVectorAngle();
    Serial.println(target- robot->getTargetAngle());
    Serial.println(correctAngle(target- robot->getTargetAngle()));
    ramp = new Ramp(acc, max_speed, dec, correctAngle(target- robot->getTargetAngle()));
    ramp->start(robot->getTotalAngle());
    robot->setDoneAngle(false);
    robot->setDoneDistance(true);
}

bool RotateTowardPositionTarget::is_done() {
    return done;
}

void RotateTowardPositionTarget::process() {
    RampReturnData data = ramp->compute();
    robot->setRampSpeedAngle(data.speed);
    robot->setTargetAngle(robot->getTargetAngle() + data.distance_increment);
    done = data.end;
}

RotateTowardPositionTarget::~RotateTowardPositionTarget() {
    delete ramp;
}

RotateTowardPositionTarget::RotateTowardPositionTarget(Robot *robot, const Position &pos, double acc, double dec,
                                                       double max_speed): Target(robot), pos(pos), max_speed(max_speed), acc(acc), dec(dec) {

}

void RotateTowardPositionTarget::on_done() {
    robot->setTargetDistance(robot->getTotalDistance());
    Serial.println("Called rotate toward");
}