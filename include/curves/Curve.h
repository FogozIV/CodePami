//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_CURVE_H
#define CODEPAMI_CURVE_H
#include "Position.h"

class Curve {
protected:
    double min_value;
    double max_value;

public:
    Curve(double min_value, double max_value);

    virtual Position getPosition(double time) const = 0;
    virtual Position getDerivative(double time) const = 0;

    double getLength(double h=0.01f) const;

    double getTForLength(double ti=NAN, double length=100.0f, double h=0.01f) const;

    virtual ~Curve();
};


#endif //CODEPAMI_CURVE_H
