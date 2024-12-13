//
// Created by fogoz on 11/12/2024.
//
#include "Target.h"
#include "Robot.h"
#include "CourbeBezier.h"

BezierTarget::BezierTarget(Robot *robot, Position end_pos): Target(robot), end_pos(end_pos) {

}

void BezierTarget::init(){
    this->curve = new CourbeBezier(robot->getPosition(), end_pos);
}

bool BezierTarget::is_done(){
    return done;
}

void BezierTarget::process(){

}

void BezierTarget::on_done(){

}