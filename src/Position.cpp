#include "Position.h"

Position::Position(double x, double y, double a) : x(x), y(y), a(a){
    
}

double Position::getX() const{
    return x;
}

double Position::getY() const{
    return y;
}

double Position::getAngle() const{
    return a;
}

void Position::add(double x, double y, double a){
  this->x += x;
  this->y += y;
  this->a += a;
}


double Position::getDistance() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

size_t Position::printTo(Print &p) const {
    size_t length = 0;
    length += p.print("x: ");
    length += p.print(x);
    length += p.print(", y: ");
    length += p.print(y);
    length += p.print(", angle: ");
    length += p.print(a);
    return length;
}

Position Position::operator+(const Position& pos){
  return Position(this->x + pos.x, this->y + pos.y, this->a+ pos.a);
}

Position Position::operator-(const Position& pos){
  return Position(this->x - pos.x, this->y - pos.y, this->a - pos.a);
}
