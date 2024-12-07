#include <Arduino.h>

#include "Position.h"
#include "Robot.h"
#include <Romi32U4.h>

#define TRACK_MM 142.0f
#define TICK_PER_MM 6.58f
#define Pin_PWM_Left 10 //PWM
#define Pin_Dir_Left 16
#define Pin_PWM_Right 9
#define Pin_Dir_Right 15
#include "Ramp.h"

double Kp = 1;
double Ki = 0.1; // 0.1
double Kd = 0.02; // 0.5

Robot* robot;
Motor* left_motor = new Motor(Pin_Dir_Left, Pin_PWM_Left);
Motor* right_motor = new Motor(Pin_Dir_Right, Pin_PWM_Right);
void setup() {
    Serial.begin(9600);
    delay(5000);
    robot = new Robot(left_motor,right_motor, TICK_PER_MM, TRACK_MM, 1.0f);
    robot->setPidDistance(new PID(3, 0.1, 0.02));
    robot->setPidAngle(new PID(4, 0.2, 0.01));
    //robot->addTarget(new AngleTarget(robot, 360));
    //robot->addTarget(new AngleTarget(robot, -170));
    Position pos(1000,1000,0);
    robot->addTarget(new RotateTowardPositionTarget(robot, pos));
    robot->addTarget(new PositionTarget(robot, pos, 300, 400, 300, 300));
    pos = pos+pos;
    robot->addTarget(new PositionTarget(robot, pos, 300, 600, 150));
// write your initialization code here
}

void loop() {
    delayMicroseconds(5000);
    robot->computePosition(Romi32U4Encoders::getCountsAndResetLeft(), Romi32U4Encoders::getCountsAndResetRight());
    robot->computeTarget();
    robot->control();
    Serial.println(*robot);
// write your code here
}