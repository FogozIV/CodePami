//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_MATRIX22_H
#define CODEPAMI_MATRIX22_H
#include "Position.h"


class Matrix22 {
    double* a = nullptr;
public:
    Matrix22(double a11, double a12, double a21, double a22);
    //Copy constructor
    Matrix22(const Matrix22& matrix);
    //Move constructor
    Matrix22(Matrix22&& matrix);

    Position operator*(const Position& position) const;

    static const Matrix22 getRotationMatrix(double theta);

    bool operator==(const Matrix22 &rhs) const;

    bool operator!=(const Matrix22 &rhs) const;


};


#endif //CODEPAMI_MATRIX22_H
