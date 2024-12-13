//
// Created by fogoz on 13/12/2024.
//

#include "curves/Curve.h"
#include "Integrator.h"

Curve::Curve(double min_value, double max_value) : min_value(min_value), max_value(max_value){}

double Curve::getLength(double h) const {
    double y0 = 0;
    runge_kutta_4(0, &y0, 1, 1.0, h, [this](double t, const double* y, double* dydt, int n) {
        dydt[0] = 0 + this->getDerivative(t).getDistance();
    });
    return y0;
}

double Curve::getTForLength(double ti, double length, double h) const {
    if(isnan(ti))
        ti = min_value;
    double y0 = 0;
    auto lambda = [this](double t, const double* y, double* dydt, int n) {
        dydt[0] = 0 + this->getDerivative(t).getDistance();
    };
    return runge_kutta_4_maximized(ti, &y0, 1, 1.0, h, lambda, &length);
}

Curve::~Curve() {

}
