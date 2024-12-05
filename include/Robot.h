#include "Arduino.h"
#include "Target.h"
#ifndef ROBOT_H
#define ROBOT_H
class Motor{
    uint8_t dir_pin;
    uint8_t pwm_pin;


};


class Robot{
    double x;
    double y;
    double a;
    double pulse_per_mm;
    double entraxe;
    double corr_right_wheel;
    Motor* left_motor;
    Motor* right_motor; 
    uint8_t target_count = 0;
    Target* targets;
    uint8_t target_index = 0;

    public:
    Robot(Motor* left_motor, Motor* right_motor, double pulse_per_mm, double entraxe, double corr_right_wheel, double x=0.0f, double y=0.0f, double a=0.0f);

    void computePosition(int16_t delta_left_tick, int16_t delte_right_tick);

    double getAngle();

    double getX();

    double getY();

    void control();



};
#endif