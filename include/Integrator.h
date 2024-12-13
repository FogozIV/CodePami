//
// Created by fogoz on 13/12/2024.
//

#ifndef CODEPAMI_INTEGRATOR_H
#define CODEPAMI_INTEGRATOR_H

template <typename Func>
// Implement the generalized RK4 method
void runge_kutta_4(double t0, double* y0, int n, double t_end, double h, Func f) {
    double t = t0; // Current time
    double* y = new double[n]; // Current state vector
    double* k1 = new double[n];
    double* k2 = new double[n];
    double* k3 = new double[n];
    double* k4 = new double[n];
    double* temp = new double[n]; // Temporary state vector

    // Initialize y with the initial condition y0
    for (int i = 0; i < n; ++i) {
        y[i] = y0[i];
    }

    // Main integration loop
    while (t < t_end) {
        // Compute k1
        f(t, y, k1, n);
        for (int i = 0; i < n; ++i) {
            k1[i] *= h;
            temp[i] = y[i] + k1[i] / 2.0;
        }

        // Compute k2
        f(t + h / 2.0, temp, k2, n);
        for (int i = 0; i < n; ++i) {
            k2[i] *= h;
            temp[i] = y[i] + k2[i] / 2.0;
        }

        // Compute k3
        f(t + h / 2.0, temp, k3, n);
        for (int i = 0; i < n; ++i) {
            k3[i] *= h;
            temp[i] = y[i] + k3[i];
        }

        // Compute k4
        f(t + h, temp, k4, n);
        for (int i = 0; i < n; ++i) {
            k4[i] *= h;
        }

        // Update y
        for (int i = 0; i < n; ++i) {
            y[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0;
        }

        // Update time
        t += h;
    }
    for (int i = 0; i < n; ++i) {
        y0[i] = y[i];
    }
    delete[] y;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete[] temp;
}


template <typename Func>
double runge_kutta_4_maximized(double t0, double* y0, int n, double t_end, double h, Func f, const double* lookup_length) {
    double t = t0; // Current time
    double* y = new double[n]; // Current state vector
    double* k1 = new double[n];
    double* k2 = new double[n];
    double* k3 = new double[n];
    double* k4 = new double[n];
    double* temp = new double[n]; // Temporary state vector

    for (int i = 0; i < n; ++i) {
        y[i] = y0[i];
    }

    // Main integration loop
    while (t < t_end) {
        int j = 0;
        for(int i = 0; i < n; i++){
            if(y[i] > lookup_length[i])
                j++;
        }
        if(j == n){
            for (int i = 0; i < n; ++i) {
                y0[i] = y[i];
            }
            delete[] y;
            delete[] k1;
            delete[] k2;
            delete[] k3;
            delete[] k4;
            delete[] temp;
            return t;
        }
        // Compute k1
        f(t, y, k1, n);
        for (int i = 0; i < n; ++i) {
            k1[i] *= h;
            temp[i] = y[i] + k1[i] / 2.0;
        }

        // Compute k2
        f(t + h / 2.0, temp, k2, n);
        for (int i = 0; i < n; ++i) {
            k2[i] *= h;
            temp[i] = y[i] + k2[i] / 2.0;
        }

        // Compute k3
        f(t + h / 2.0, temp, k3, n);
        for (int i = 0; i < n; ++i) {
            k3[i] *= h;
            temp[i] = y[i] + k3[i];
        }

        // Compute k4
        f(t + h, temp, k4, n);
        for (int i = 0; i < n; ++i) {
            k4[i] *= h;
        }

        // Update y
        for (int i = 0; i < n; ++i) {
            y[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0;
        }

        // Update time
        t += h;
    }
    for (int i = 0; i < n; ++i) {
        y0[i] = y[i];
    }
    delete[] y;
    delete[] k1;
    delete[] k2;
    delete[] k3;
    delete[] k4;
    delete[] temp;
    return t_end;
}

#endif //CODEPAMI_INTEGRATOR_H
