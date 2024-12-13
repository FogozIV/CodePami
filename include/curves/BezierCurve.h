//
// Created by fogoz on 11/12/2024.
//

#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "Position.h"
#include "Curve.h"

class BezierCurve: public Curve {
    Position pos1;
    Position pos2;
    Position pos3;
    Position pos4;
    public:
    explicit BezierCurve(Position start, Position end, double multiplier=100.0f);

    Position getPosition(double time) const;

    Position getDerivative(double time) const;

};



#endif //COURBEBEZIER_H
