//
// Created by fogoz on 07/12/2024.
//
#include "Target.h"
#include "Robot.h"


bool AngleTarget::is_done() {
    return done;
}

void AngleTarget::process() {
    RampReturnData data = ramp->compute(robot->getAbsoluteAngle(target) - robot->getTotalAngle(), robot->getTotalAngle());
    robot->setRampSpeedAngle(data.speed);
    robot->setTargetAngle(robot->getTargetAngle() + data.distance_increment);
    done = data.end;
}

void AngleTarget::init() {
    Serial.println(robot->getAbsoluteAngle(target));
    ramp = new Ramp(acc, max_speed, dec, robot->getAbsoluteAngle(target) - robot->getTargetAngle());
    ramp->start(robot->getTotalAngle());
    robot->setDoneAngle(false);
    robot->setDoneDistance(true);
}

AngleTarget::~AngleTarget() {
    delete ramp;
}

AngleTarget::AngleTarget(Robot *robot, double target, double acc, double dec, double max_speed) : Target(robot) {
    this->target = target;
    this->acc = acc;
    this->dec = dec;
    this->max_speed = max_speed;
}

void AngleTarget::on_done() {
    Serial.println("Called");
    robot->setTargetDistance(robot->getTotalDistance());
}
