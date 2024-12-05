#include "Arduino.h"

#ifndef ANTI_WINDUP_VALUE
    #define ANTI_WINDUP_VALUE 100
#endif
#ifndef PID_H
#define PID_H
class PID{
   double kp;
   double ki;
   double kd;

   double old_error;
   double iTerm;
   double (*anti_windup)(double);

   uint64_t previous_time;
  public:
   PID(double kp, double ki, double kd, double (*anti_windup)(double)= [](double a){return max(min(a, ANTI_WINDUP_VALUE), -ANTI_WINDUP_VALUE);});

   double evaluate(double error);
};

#endif