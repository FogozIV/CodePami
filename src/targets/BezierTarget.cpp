//
// Created by fogoz on 11/12/2024.
//
#include "./targets/BezierTarget.h"
#include "Robot.h"
#include "curves/BezierCurve.h"

BezierTarget::BezierTarget(Robot *robot, double acc, double max_speed, double dec, Position end_pos, double multiplier): CurveTarget(robot, acc, max_speed, dec, (Position&&)end_pos), multiplier(multiplier){

}

void BezierTarget::init(){
#ifdef DEBUG_TXT
    Serial.print("Init target toward : ");
    Serial.println(end_pos);
#endif
    this->curve = new BezierCurve(robot->getPosition(), end_pos, multiplier);
    this->distanceRamp = new Ramp(acc, max_speed, dec, this->curve->getLength(), 0.0f, 0.0f);
    this->distanceRamp->start(robot->getTotalDistance());
    robot->setDoneAngle(false);
    robot->setDoneDistance(false);
    this->t = this->curve->getTForLength(NAN, 30.0f);
    this->target_pos = this->curve->getPosition(this->t);
}

void BezierTarget::on_done() {

}


