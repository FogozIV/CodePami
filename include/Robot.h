#include "Arduino.h"
#include "Target.h"
#include "PID.h"

#ifndef ROBOT_H
#define ROBOT_H

double correctAngle(double angle);
class Motor{
    uint8_t dir_pin;
    uint8_t pwm_pin;
    int16_t current_pwm = 0;
    bool inverse;
public:
    Motor(uint8_t dir_pin, uint8_t pwm_pin, bool inverse=false);

    void setPWM(int16_t pwm);

};


class Robot : public Printable{
    Position pos;
    double pulse_per_mm;
    double track_mm;
    double corr_right_wheel;
    Motor* left_motor = nullptr;
    Motor* right_motor = nullptr;
    uint16_t target_count = 0;
    Target** targets = nullptr;
    uint16_t max_targets = 10;
    uint16_t target_index = 0;
    double total_distance;
    double target_distance;
    double total_angle;
    double target_angle;
    PID* pid_distance = nullptr;
    PID* pid_angle = nullptr;
    bool done_distance = false;
    bool done_angle = false;

    double ramp_speed = 0.0f;
    double ramp_speed_angle = 0.0f;

    friend Target;

    public:
    Robot(Motor* left_motor, Motor* right_motor, double pulse_per_mm, double track_mm, double corr_right_wheel, double x=0.0f, double y=0.0f, double a=0.0f);

    ~Robot();

    void computePosition(int16_t delta_left_tick, int16_t delta_right_tick);

    [[nodiscard]] Position getPosition() const;

    void control();

    void setPidDistance(PID *pidDistance);

    void setPidAngle(PID *pidAngle);

    void computeTarget();

    bool addTarget(Target* target);

    size_t printTo(Print &p) const override;

    double getTargetDistance() const;

    double getTargetAngle() const;

    double getTotalDistance() const;

    double getTotalAngle() const;

    bool isDoneDistance() const;

    bool isDoneAngle() const;

    void setTargetDistance(double targetDistance);

    void setTargetAngle(double targetAngle);

    void setDoneDistance(bool doneDistance);

    void setDoneAngle(bool doneAngle);

    double getRampSpeed() const;

    void setRampSpeed(double rampSpeed);

    double getRampSpeedAngle() const;

    void setRampSpeedAngle(double rampSpeedAngle);

    double getRelativeAngle(double a) const;

    double getAbsoluteAngle(double a) const;

    void setTotalDistance(double totalDistance);

    void setTotalAngle(double totalAngle);


};
#endif