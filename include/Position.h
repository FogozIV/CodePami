#include "Arduino.h"

#ifndef POSITION_H
#define POSITION_H

class Position : public Printable {

private:
    double x;
    double y;
    double a;

    public:
    Position(double x, double y, double a);
    
    double getX() const;
    
    double getY() const;

    double getAngle() const;

    double getDistance() const;

    void add(double x, double y, double a);

    Position operator+(const Position& rhs);

    Position operator-(const Position& rhs);

    size_t printTo(Print& p) const override;
};



#endif
