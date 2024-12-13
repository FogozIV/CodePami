//
// Created by fogoz on 11/12/2024.
//

#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H

#include "Position.h"

class CourbeBezier {
    Position pos1;
    Position pos2;
    Position pos3;
    Position pos4;
    public:
    explicit CourbeBezier(Position start, Position end);

    Position getPosition(double time) const;
};



#endif //COURBEBEZIER_H
