#include "Arduino.h"
#include "Position.h"
#include "Ramp.h"

#ifndef TARGET_H
#define TARGET_H
class Robot;
class Target{
protected:
    Robot* robot;
    bool is_init = false;
public:
    Target(Robot* robot);
    virtual void init() = 0;
    void call_init(){
        if(!is_init){
            init();
            is_init = true;
        }
    }
    virtual bool is_done() = 0;
    virtual void process() = 0;

    virtual void on_done() = 0;

    virtual ~Target() = default;

};

class AngleTarget : public Target{
    double target;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
public:
    AngleTarget(Robot *robot, double target, double acc=10, double dec=10, double max_speed=45);

    ~AngleTarget() override;

    void init() override;

    bool is_done() override;

    void process() override;

    void on_done() override;

};

class PositionTarget : public Target{
    Position pos;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
    double end_speed;
public:
    PositionTarget(Robot *robot, const Position &pos, double acc=100, double dec=100, double max_speed=200, double end_speed=0.0);

    void init() override;

    bool is_done() override;

    void process() override;

    ~PositionTarget() override;

    void on_done() override;
};

class RotateTowardPositionTarget : public Target{
    Position pos;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
    double target;
public:
    RotateTowardPositionTarget(Robot *robot, const Position& pos, double acc=10, double dec=10, double max_speed=45);

    void init() override;

    bool is_done() override;

    void process() override;

    void on_done() override;

    ~RotateTowardPositionTarget() override;
};

class ArcTarget: public Target{
    Position pos;
    Ramp* ramp = nullptr;
    double max_speed;
    double acc;
    double dec;
    bool done = false;
    double radius;
public:

};

#endif