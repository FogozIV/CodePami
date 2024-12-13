//
// Created by fogoz on 07/12/2024.
//
#include "Target.h"
#include "Robot.h"


void RotateTowardPositionTarget::init() {
    target = (pos-robot->getPosition()).getVectorAngle();
    ramp = new Ramp(acc, max_speed, dec, robot->getAbsoluteAngle(target) - robot->getTargetAngle());
    ramp->start(robot->getTotalAngle());
    robot->setDoneAngle(false);
    robot->setDoneDistance(true);
}

bool RotateTowardPositionTarget::is_done() {
    return done;
}

void RotateTowardPositionTarget::process() {
    RampReturnData data = ramp->compute(robot->getAbsoluteAngle(target) - robot->getTotalAngle(), robot->getTotalAngle());
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