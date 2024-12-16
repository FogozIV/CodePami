#ifdef REAL_BOARD
#include "Arduino.h"
#include "config.h"

#else

#endif
#ifndef POSITION_H
#define POSITION_H

#ifdef REAL_BOARD
class Position : public Printable {
#else
class Position{
#endif
private:
    PRECISION_DATA_TYPE x;
    PRECISION_DATA_TYPE y;
    PRECISION_DATA_TYPE a;

    public:
    Position(PRECISION_DATA_TYPE x=0.0f, PRECISION_DATA_TYPE y=0.0f, PRECISION_DATA_TYPE a=0.0f);

    PRECISION_DATA_TYPE getX() const;

    PRECISION_DATA_TYPE getY() const;

    PRECISION_DATA_TYPE getAngle() const;

    PRECISION_DATA_TYPE getDistance() const;

    PRECISION_DATA_TYPE getVectorAngle() const;

    void add(PRECISION_DATA_TYPE x, PRECISION_DATA_TYPE y, PRECISION_DATA_TYPE a=0.0f);

    Position operator+(const Position& rhs) const;

    Position operator-(const Position& rhs) const;

    Position operator+=(const Position& rhs);

    Position operator*(PRECISION_DATA_TYPE rhs) const;

    Position operator/(PRECISION_DATA_TYPE rhs) const;

#ifdef REAL_BOARD
    size_t printTo(Print& p) const override;
#endif
    PRECISION_DATA_TYPE getAngleRad() const;

    PRECISION_DATA_TYPE getVectorAngleRad() const;

    Position getSinCosAngle() const;


};



#endif
