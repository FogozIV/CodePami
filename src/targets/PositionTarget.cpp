//
// Created by fogoz on 07/12/2024.
//
#include "./targets/PositionTarget.h"
#include "Robot.h"

PositionTarget::PositionTarget(Robot *robot, const Position &pos, double acc, double dec, double max_speed, double end_speed) : Target(robot), pos(pos), max_speed(max_speed), acc(acc), dec(dec), end_speed(end_speed) {}

void PositionTarget::init() {
    ramp = new Ramp(acc, max_speed, dec, (pos-robot->getPosition()).getDistance(), robot->getRampSpeed(), end_speed);
    ramp->start(robot->getTotalDistance());
    robot->setDoneAngle(false);
    robot->setDoneDistance(false);
}

bool PositionTarget::is_done() {
    return done;
}

void PositionTarget::process() {
    double distance = (pos-robot->getPosition()).getDistance();
    RampReturnData data = ramp->compute(distance, robot->getTotalDistance());
    robot->setRampSpeed(data.speed);
    robot->setTargetDistance(robot->getTargetDistance() + data.distance_increment);
    robot->setTargetAngle(robot->getAbsoluteAngle((pos-robot->getPosition()).getVectorAngle()));
    done = data.end;
    robot->setDoneDistance(data.stop);
    if(distance < 5) {
        robot->setTargetDistance(robot->getTotalDistance());
        robot->setDoneAngle(true);
    }else{
        robot->setDoneAngle(false);
    }
}

PositionTarget::~PositionTarget() {
    delete ramp;
}

void PositionTarget::on_done() {
    robot->setTargetDistance(robot->getTotalDistance());
    robot->setTargetAngle(robot->getTotalAngle());
}
