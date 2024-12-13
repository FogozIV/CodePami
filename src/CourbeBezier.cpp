//
// Created by fogoz on 11/12/2024.
//

#include "CourbeBezier.h"
#include "Position.h"

CourbeBezier::CourbeBezier(Position start, Position end){
      pos1 = start;
      pos2 = start.getSinCosAngle()/3 + start;
      pos3 = end - end.getSinCosAngle()/3;
      pos4 = end;
}

Position CourbeBezier::getPosition(double time) const{
  return pos1 * pow(1-time, 3) + pos2 * (3*pow(1-time, 2)*time) + pos3 * (3*(1-time)*pow(time, 2)) + pos4 * pow(time, 3);
}