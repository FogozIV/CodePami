#include "PID.h"

PID::PID(double kp, double ki, double kd, double (*anti_windup)(double)){
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;

    this->anti_windup = anti_windup;
    this->old_error = 0;
    this->iTerm = 0;
    this->previous_time = micros();
}

double PID::evaluate(double error){
    double result = 0;
    double dt = ((double)(micros() - this->previous_time))/(1.0e6);
    this->previous_time = micros();

    iTerm += this->ki * error * dt;
    iTerm = anti_windup(iTerm);

    result += this->kp * error + kd * (error - this->old_error)/dt + iTerm;

    this->old_error = error;
    return result;
}