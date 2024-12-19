#include "Position.h"

PRECISION_DATA_TYPE correctAngle(PRECISION_DATA_TYPE);

Position::Position(PRECISION_DATA_TYPE x, PRECISION_DATA_TYPE y, PRECISION_DATA_TYPE a) : x(x), y(y), a(a){
    this->a = correctAngle(a)*DEG_TO_RAD;
}

PRECISION_DATA_TYPE Position::getX() const{
    return x;
}

PRECISION_DATA_TYPE Position::getY() const{
    return y;
}

PRECISION_DATA_TYPE Position::getAngle() const{
    return a * RAD_TO_DEG;
}

PRECISION_DATA_TYPE Position::getAngleRad() const {
    return a;
}

void Position::add(PRECISION_DATA_TYPE x, PRECISION_DATA_TYPE y, PRECISION_DATA_TYPE a){
  this->x += x;
  this->y += y;
  this->a += a;
  while(this->a > M_PI)
    this->a -= 2*M_PI;
  while(this->a < -M_PI)
    this->a += 2*M_PI;
}


PRECISION_DATA_TYPE Position::getDistance() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
#ifdef REAL_BOARD
size_t Position::printTo(Print &p) const {
    size_t length = 0;
#ifdef DEBUG_TXT
    length += p.print("x: ");
    length += p.print(x);
    length += p.print(", y: ");
    length += p.print(y);
    length += p.print(", angle: ");
    length += p.print(a*180/M_PI);
#endif
    return length;
}
#endif

Position Position::operator+(const Position& pos) const{
  return {this->x + pos.x, this->y + pos.y, this->a+ pos.a};
}

Position Position::operator-(const Position& pos) const{
  return {this->x - pos.x, this->y - pos.y, this->a - pos.a};
}

Position Position::operator+=(const Position &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->a += rhs.a;
    while(this->a > M_PI)
        this->a -= 2*M_PI;
    while(this->a < -M_PI)
        this->a += 2*M_PI;
    return *this;
}

Position Position::operator*(const PRECISION_DATA_TYPE rhs) const {
    return {this->x * rhs, this->y * rhs, this->a * rhs};
}

Position Position::operator/(const PRECISION_DATA_TYPE rhs) const{
    return {this->x / rhs, this->y / rhs, this->a / rhs};
}

PRECISION_DATA_TYPE Position::getVectorAngle() const {
    return atan2(this->y, this->x) / M_PI * 180;
}

PRECISION_DATA_TYPE Position::getVectorAngleRad() const {
    return atan2(this->y, this->x) ;
}

Position Position::getSinCosAngle() const {
    return {cos(this->a), sin(this->a)};
}