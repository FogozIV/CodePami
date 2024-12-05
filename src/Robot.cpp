#include "Robot.h"

Robot::Robot(Motor* left_motor, Motor* right_motor, double pulse_per_mm, double entraxe, double corr_right_wheel, double x, double y, double a) : x(x), y(y), a(a), pulse_per_mm(pulse_per_mm), entraxe(entraxe), corr_right_wheel(corr_right_wheel){
  this->left_motor = left_motor;
  this->right_motor = right_motor;
}

void Robot::computePosition(int16_t delta_left_tick, int16_t delta_right_tick){
    double distance = ((double)(delta_left_tick + delta_right_tick * corr_right_wheel))/(2.0f * pulse_per_mm);
    double dtheta = (delta_right_tick * corr_right_wheel - delta_left_tick)/(2.0f*pulse_per_mm);
    Serial.println(dtheta);
    double dx;
    double dy;
    if(dtheta == 0){
        dx = cos(this->a) * distance;
        dy = sin(this->a) * distance;
    }else{
        double r = distance * entraxe/ (dtheta * 2.0f);
        double arc_angle = 2* dtheta /entraxe;
        dx = r * (-sin(this->a) + sin(this->a + arc_angle));
        dy = r * (cos(this->a) - cos(this->a + arc_angle));
        this->a += arc_angle;
    }
    x += dx;
    y += dy;
    while(a > M_PI)
        a -= 2*M_PI;
    while(a < -M_PI)
        a += 2*M_PI;

}

double Robot::getX(){
    return x;
}

double Robot::getY(){
    return y;
}

double Robot::getAngle(){
    return a/M_PI * 180.0f;
}

void Robot::control(){

}