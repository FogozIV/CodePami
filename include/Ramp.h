//
// Created by fogoz on 07/12/2024.
//
#include "Arduino.h"

#ifndef CODEPAMI_RAMP_H
#define CODEPAMI_RAMP_H



struct RampReturnData{
    bool end;
    double distance_increment;
    double speed;
    bool stop;
    bool started;
};

class Ramp {
    double acc;
    double dec;
    double sign;
    double ste_speed;

    struct Private{
        bool done;
        double speed;
        double distance;
    };

    double dec_time;
    double acc_time;
    double ste_time;

    double init_ste_time;

    uint64_t init_time = 0;

    Ramp::Private previous_computation = {false, NAN, NAN};

    struct{
        double initial_speed;
        double current_speed;
        double end_speed;
        double acc_distance;
        double dec_distance;

        double point_distance = 0;
        double wheel_distance = 0;
    }sign_corrected;
    const Private compute_at_time(double time) const;
    void update_ste_time(double time, double distance, double wheel_distance);
public:
    Ramp(double acc, double max_speed, double dec, double distance, double initial_speed=0.0f, double end_speed=0.0f);

    void start(double wheel_distance);

    const RampReturnData compute(double distance_to_point, double wheel_distance);

};


#endif //CODEPAMI_RAMP_H
